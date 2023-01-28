#include "pch.h"
#include <llapi/LLAPI.h>

#include <llapi/mc/Level.hpp>
#include <llapi/mc/BlockInstance.hpp>
#include <llapi/mc/Block.hpp>
#include <llapi/mc/BlockSource.hpp>
#include <llapi/mc/Material.hpp>
#include <llapi/mc/Actor.hpp>
#include <llapi/mc/Item.hpp>
#include <llapi/mc/Player.hpp>
#include <llapi/mc/SimulatedPlayer.hpp>
#include <llapi/mc/ItemStack.hpp>
#include <llapi/mc/ItemInstance.hpp>
#include <llapi/mc/ListTag.hpp>
#include <llapi/mc/HashedString.hpp>
#include <llapi/EventAPI.h>

#include "Utils.hpp"
#include "Plugin.h"
#include "Global.h"
#include "Config.h"
#include "Economic.h"
#include "Version.h"

#include <unordered_map>
#include <queue>
#include <random>
#include <utility>

using std::unordered_map;
using std::unordered_set;
using std::queue;
using std::pair;
using std::unique_ptr;
using std::to_string;

Logger logger("ChainMiner");

std::random_device rd;//使用硬件熵源的非确定随机数生成器(类)
std::default_random_engine re(rd());//设置随机数分布类型
std::uniform_int_distribution<int> ud(0, 99);//设置随机数返回
//std::bernoulli_distribution rand_dist(0.5);//50%生成true

typedef struct minerinfo {
    string name;//方块名称
    int dimId;//维度id
    int limit;//最大挖掘数量
    int cnt;//已挖掘数量
    int cntD;//需要扣除的耐久
    ItemStack *tool;//工具
    short enchU;//耐久附魔等级(没有为0)
    Player* pl;
} MinerInfo;

unordered_map<int, MinerInfo> task_list;//id,cnt
unordered_set<string> chaining_blocks;//避免在call事件的时候进入死循环

extern unordered_map<string, BlockInfo> block_list;//方块列表
extern nlohmann::json config_j;

void PluginInit() {
    logger.info("初始化... v{}.{}.{}.{}", PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR, PLUGIN_VERSION_REVISION, PLUGIN_VERSION_BUILD);
    initConfig();
    initEventOnPlayerDestroy();
    // initEventOnBlockChange();
    registerCommand();
}

void initEventOnPlayerDestroy() {
    Event::PlayerDestroyBlockEvent::subscribe([](const Event::PlayerDestroyBlockEvent& e) {
        BlockInstance bli = e.mBlockInstance;
        BlockPos blp = bli.getPosition();
        
        if (chaining_blocks.count(getBlockDimAndPos(bli)) > 0) {
        	return true;//如果是连锁采集的就不处理(pl->playerDestroy()不会触发此事件)
        }
        if (e.mPlayer->getPlayerGameType() != GameType::GameTypeSurvival) return true;
        if (!playerSetting.getSwitch(e.mPlayer->getXuid())) return true;
        if (playerSetting.getSwitch(e.mPlayer->getXuid(), "chain_while_sneaking_only") && !e.mPlayer->isSneaking()) return true;
        Block *bl = bli.getBlock();
        string bn = bl->getTypeName();
        //logger.info("{} {} {} {}", bl->getName().getString(), bl->getId(), bl->getDescriptionId(), bl->getVariant());
        //logger.debug("{} BREAK {} AT {},{},{}", e.mPlayer->getRealName(), bl->getTypeName(), blp.x, blp.y, blp.z);
        auto r = block_list.find(bn);
        if (r != block_list.end()) {//如果是可以连锁挖掘的方块
            if (!r->second.enabled) return true;//全局关闭
            if (!playerSetting.getSwitch(e.mPlayer->getXuid(),bn)) return true;//方块被关闭

            ItemStack *tool = (ItemStack *) &e.mPlayer->getCarriedItem();
            string toolType = tool->getTypeName();
            //logger.info("{}", toolType);
            auto &material = bl->getMaterial();

            //判断是否含有精准采集bl->getName();
            auto nbt = tool->getNbt();
            //logger.debug("{}", nbt->toSNBT());
            bool hasSilkTouch = getEnchantLevel(nbt, 16);

            //如果该工具无法挖掘就结束
            bool canThisToolChain = (
                r->second.tools.empty() //没有设置指定工具
                || v_contains(r->second.tools, toolType) //使用了指定工具
                || v_contains(r->second.tools, string("")) //允许使用手挖掘
                )
                && (material.isAlwaysDestroyable() || tool->canDestroySpecial(*bl)) //可挖掘
                && ((r->second.enchSilkTouch == 1 && hasSilkTouch) //仅精准采集工具
                    || (r->second.enchSilkTouch == 0 && !hasSilkTouch) //禁止精准采集工具
                    || r->second.enchSilkTouch == 2); //不论是否精准采集
                //&& getDamageFromNbt(nbt) > 0; //无损坏的工具不能触发
            if (!canThisToolChain) return true;

            //logger.debug("{} is chainable using {}", bn, tool->getTypeName());
            int limit = block_list[bn].limit;
            if (tool->isDamageableItem()) {
                limit = std::min(limit, int((tool->getMaxDamage() - getDamageFromNbt(nbt) - 1) / (ConfigManager::multiply_damage_switch ? ConfigManager::multiply_damage_max : 1)));//留一点耐久,防止炸掉
            }
            if (economic.mode > 0 && block_list[bn].cost > 0)
                limit = std::min(limit, int(economic.getMoney(e.mPlayer) / block_list[bn].cost));

            //仅当多个时
            if (limit > 1) {
                //add task
                int id = (int) task_list.size() + 1;
                task_list.insert(pair<int, MinerInfo>{
                        id,
                        {bn,
                         bli.getDimensionId(),
                         limit,
                         0,
                         0,
                         tool,
                         getEnchantLevel(nbt, 17),
                         e.mPlayer
                        }
                });
                //add pos2id
                string pos = getBlockDimAndPos(bli);
                //logger.debug("start mine task id:{} for block:{} max:{}", id, task_list[id].name, task_list[id].limit);

                //miner1(id, &blp, false);
                miner2(id, &blp);
            }
        }
        return true;
    });
}

//get a string like "dim,x,y,z"
string getBlockDimAndPos(BlockInstance& bli) {
    string pos = to_string(bli.getDimensionId()) + ','
        + bli.getPosition().toString();
    return pos;
}

//get enchant level with nbt && enchid
//return level (0 when non-exist)
short getEnchantLevel(unique_ptr<CompoundTag> &nbt, short id) {
    if (nbt->contains("tag")) {//必须判断否则会报错
        auto tag = nbt->getCompound("tag");
        if (tag->contains("ench")) {
            ListTag *ench = tag->getList("ench");
            for (auto it = ench->begin(); it != ench->end(); ++it) {
                CompoundTag *ec = (*it)->asCompoundTag();
                if (ec->getShort("id") == id) {
                    return ec->getShort("lvl");
                }
            }
        }
    }
    return 0;
}

int getDamageFromNbt(unique_ptr<CompoundTag> &nbt) {
    if (nbt->contains("tag")) {//必须判断否则会报错
        auto tag = nbt->getCompound("tag");
        if (tag->contains("Damage")) {
            return tag->getInt("Damage");
        }
    }
    /*else {
        logger.debug("no tag:{}", nbt->toSNBT());
    }*/
    return 0;
}

int toolDamage(ItemStack &tool, int count) {
    int damage = count;
    auto nbt = tool.getNbt();
    //logger.debug("before:{} {}", nbt->toSNBT(), tool.getMaxDamage());
    if (ConfigManager::multiply_damage_switch) {
        double rate = ConfigManager::multiply_damage_min + (ConfigManager::multiply_damage_max - ConfigManager::multiply_damage_min) * ud(re) / 100;
        //logger.debug("rate:{}", rate);
        damage = count * rate;
    }
    if (nbt->contains("tag")) {//必须判断否则会报错
        auto tag = nbt->getCompound("tag");
        if (tag->contains("Damage")) {
            if (tag->getInt("Damage") + damage < tool.getMaxDamage()) {
                tag->putInt("Damage", tag->getInt("Damage") + damage);
                //logger.debug("{}", tag->getInt("Damage"));

                tool.setNbt(nbt.get());
                //logger.debug("after:{}", tool.getNbt()->toSNBT());
            }
            else damage = 0;
        }
        else { //没有Damage
            tag->putInt("Damage", damage);
            tool.setNbt(nbt.get());
        }
    }
    else { //没有tag
        auto compoundTag = CompoundTag::create();
        compoundTag->putInt("Damage", damage);
        nbt->putCompound("tag", unique_ptr<CompoundTag>(compoundTag.release()));
        tool.setNbt(nbt.get());
        //logger.debug("new damage:{}", nbt->toSNBT());
    }
    return damage;
}

int countTaskList() {
    return (int)task_list.size();
}

int countChainingBlocks() {
    return (int)chaining_blocks.size();
}

//使用递归进行连锁采集
void miner1(int id, BlockPos *pos, bool sub) {
    if (task_list[id].cnt < task_list[id].limit) {
        int i, j;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 2; j++) {
                if (task_list[id].cnt >= task_list[id].limit) goto end;
                BlockPos newpos = pos->add(
                        (i == 0 ? (j == 0 ? -1 : 1) : 0),
                        (i == 1 ? (j == 0 ? -1 : 1) : 0),
                        (i == 2 ? (j == 0 ? -1 : 1) : 0)
                );//Gen 6 possibilities
                Block *bl = Level::getBlock(newpos, task_list[id].dimId);
                auto r = block_list.find(task_list[id].name);
                //The same type of block or a similar block
                if (bl->getTypeName() == task_list[id].name || v_contains(r->second.similar, bl->getTypeName())) {
                    //logger.debug("{} can be mine", newpos.toString());

                    //累计耐久损失
                    if (task_list[id].enchU == 0 ||
                        (task_list[id].enchU > 0 && ud(re) < (100 / (task_list[id].enchU + 1))))
                        task_list[id].cntD++;

                    /* break a block */
                    auto ev = new Event::PlayerDestroyBlockEvent();
                    ev->mBlockInstance = Level::getBlockInstance(newpos, task_list[id].dimId);
                    ev->mPlayer = task_list[id].pl;

                    string dp = getBlockDimAndPos(ev->mBlockInstance);
                    chaining_blocks.insert(dp);

                    bool res = ev->call();
                    //logger.debug("pos:{} res:{}", dp, res);
                    chaining_blocks.erase(dp);
                    if (!res) {
                        continue;
                    }
                    else {
                        bl->playerDestroy(*task_list[id].pl, newpos);//playerDestroy here can only get drops
                        //下面这行不行
                        //bl->destroy(*Level::getBlockSource(task_list[id].dimId), newpos, task_list[id].pl);
                        //下面这个方法被注释掉了
                        //Level::destroyBlock(*Level::getBlockSource(task_list[id].dimId), newpos, false);//remove the block
                        Level::setBlock(newpos, task_list[id].dimId, "minecraft:air", 0);
                        task_list[id].cnt++;

                        miner1(id, &newpos, true);
                    }
                }
            }
        }
    }
    ////超过限制数量/挖完了/没有相同方块
    end:
    if (!sub) {//是入口miner
        MinerInfo mi = task_list[id];
        if(mi.cnt > 0) {
            //减少耐久
            ItemStack tool = mi.pl->getCarriedItem();
            toolDamage(tool, mi.cntD);
            //手动给玩家替换工具
            //mi.pl->refreshInventory();
            mi.pl->setCarriedItem(tool);
            mi.pl->refreshInventory();
            string msg = config_j["msg"]["mine.success"];
            msg = s_replace(msg,"%Count%",std::to_string(mi.cnt));
            if (economic.mode > 0) {
                long long cost = block_list[mi.name].cost * (mi.cnt - 1);//有一个是自己挖的
                if (cost > 0) {
                    economic.reduceMoney(mi.pl, cost);
                    msg += config_j["msg"]["money.use"];
                    msg = s_replace(msg, "%Cost%", std::to_string(cost));
                    msg = s_replace(msg, "%Remain%", std::to_string(economic.getMoney(mi.pl)));
                    msg = s_replace(msg, "%Name%", config_j["money.name"]);
                }
            }
            if (config_j["switch"]["mine.success"])
                mi.pl->sendTextPacket(msg);
        }
        //logger.debug("id:{} cnt:{} cntD:{} enchU:{} limit:{}", id, mi.cnt, mi.cntD, mi.enchU, mi.limit);
        task_list.erase(id);
    }
    //logger.debug("task {} end.", id);
}

//使用队列进行连锁采集
#include <tuple>
using std::tuple;
using std::get;
void miner2(int task_id, BlockPos* start_pos) {
    queue<BlockPos> block_q;
    block_q.push(*start_pos);
    constexpr tuple<int, int, int> dirs[6] = {{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};
    while (task_list[task_id].cnt < task_list[task_id].limit && !block_q.empty()) {
        BlockPos curpos = block_q.front();
        for (int i = 0; i < 6; i++) {
            BlockPos newpos = curpos.add(get<0>(dirs[i]), get<1>(dirs[i]), get<2>(dirs[i]));
            Block* bl = Level::getBlock(newpos, task_list[task_id].dimId);
            auto r = block_list.find(task_list[task_id].name);
            if (bl->getTypeName() == task_list[task_id].name || v_contains(r->second.similar, bl->getTypeName())) {
                block_q.push(newpos);
            }
        }
        
        Block* bl = Level::getBlock(curpos, task_list[task_id].dimId);
        if (bl->getId() != 0) {
            //累计耐久损失
            if (task_list[task_id].enchU == 0 ||
                (task_list[task_id].enchU > 0 && ud(re) < (100 / (task_list[task_id].enchU + 1))))
                task_list[task_id].cntD++;

            //破坏方块
            auto ev = new Event::PlayerDestroyBlockEvent();
            ev->mBlockInstance = Level::getBlockInstance(curpos, task_list[task_id].dimId);
            ev->mPlayer = task_list[task_id].pl;
            string dp = getBlockDimAndPos(ev->mBlockInstance);
            chaining_blocks.insert(dp);
            bool res = ev->call();
            chaining_blocks.erase(dp);
            if (!res) {
                continue;
            }
            else {
                bl->playerDestroy(*task_list[task_id].pl, curpos);//playerDestroy here can only get drops
                Level::setBlock(curpos, task_list[task_id].dimId, "minecraft:air", 0);
                task_list[task_id].cnt++;
            }
        }
        block_q.pop();
    }

    //结果计算
    MinerInfo mi = task_list[task_id];
    if (mi.cnt > 0) {
        //减少耐久
        ItemStack tool = mi.pl->getCarriedItem();
        int dmg = toolDamage(tool, mi.cntD);
        //手动给玩家替换工具
        mi.pl->setCarriedItem(tool);
        mi.pl->refreshInventory();
        string msg = config_j["msg"]["mine.success"];
        msg = s_replace(msg, "%Count%", std::to_string(mi.cnt));//有一个是自己挖的
        if (config_j["switch"]["mine.damage"])
            msg += s_replace(config_j["msg"]["mine.damage"], "%Damage%", std::to_string(dmg));
        if (economic.mode > 0) {
            long long cost = block_list[mi.name].cost * (mi.cnt - 1);
            if (cost > 0) {
                economic.reduceMoney(mi.pl, cost);
                msg += config_j["msg"]["money.use"];
                msg = s_replace(msg, "%Cost%", std::to_string(cost));
                msg = s_replace(msg, "%Remain%", std::to_string(economic.getMoney(mi.pl)));
                msg = s_replace(msg, "%Name%", config_j["money.name"]);
            }
        }
        if (config_j["switch"]["mine.success"])
            mi.pl->sendTextPacket(msg);
    }
    task_list.erase(task_id);
}
