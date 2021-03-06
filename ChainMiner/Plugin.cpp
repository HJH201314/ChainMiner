#include "pch.h"
#include "LLAPI.h"

#include <MC/Level.hpp>
#include <MC/BlockInstance.hpp>
#include <MC/Block.hpp>
#include <MC/BlockSource.hpp>
#include <MC/Material.hpp>
#include <MC/Actor.hpp>
#include <MC/Item.hpp>
#include <MC/Player.hpp>
#include <MC/SimulatedPlayer.hpp>
#include <MC/ItemStack.hpp>
#include <MC/ItemInstance.hpp>
#include <MC/ListTag.hpp>
#include <MC/HashedString.hpp>
#include <EventAPI.h>

#include "Utils.hpp"
#include "Plugin.h"
#include "Global.h"
#include "Config.h"
#include "Economic.h"

#include <unordered_map>
#include <random>
#include <utility>

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

std::unordered_map<int, MinerInfo> task_list;//id,cnt
std::unordered_set<string> chaining_blocks;//

extern std::unordered_map<string, BlockInfo> block_list;//方块列表
extern nlohmann::json config_j;

void PluginInit() {
    initConfig();
    initEventOnPlayerDestroy();
    // initEventOnBlockChange();
    registerCommand();
}

void initEventOnPlayerDestroy() {
    Event::PlayerDestroyBlockEvent::subscribe([](const Event::PlayerDestroyBlockEvent &e) {
        if(e.mPlayer->getPlayerGameType() != 0) return true;
        if(!playerSetting.getSwitch(e.mPlayer->getXuid())) return true;
        BlockInstance bli = e.mBlockInstance;
        BlockPos blp = bli.getPosition();
        
        if (chaining_blocks.find(getBlockDimAndPos(bli)) != chaining_blocks.end()) {
        	return true;//如果是连锁采集的就不处理(pl->playerDestroy()似乎不会触发此事件)
        }
        Block *bl = bli.getBlock();
        string bn = bl->getTypeName();
        //logger.info("{} {} {} {}", bl->getName().getString(), bl->getId(), bl->getDescriptionId(), bl->getVariant());
        //logger.debug("{} BREAK {} AT {},{},{}", e.mPlayer->getRealName(), bl->getTypeName(), blp.x, blp.y, blp.z);
        auto r = block_list.find(bn);
        if (r != block_list.end()) {//如果是可以连锁挖掘的方块
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
            if(tool->isDamageableItem())
                limit = std::min(limit, tool->getMaxDamage() - getDamageFromNbt(nbt) - 1);//留一点耐久,防止炸掉
            if (Economic::mode > 0 && block_list[bn].cost > 0)
                limit = std::min(limit, int(Economic::getMoney(e.mPlayer) / block_list[bn].cost));

            //仅当多个时
            if (limit > 1) {
                //add task
                int id = (int) task_list.size() + 1;
                task_list.insert(std::pair<int, MinerInfo>{
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

                miner1(id, &blp, false);
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
short getEnchantLevel(std::unique_ptr<CompoundTag> &nbt, short id) {
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

int getDamageFromNbt(std::unique_ptr<CompoundTag> &nbt) {
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

bool toolDamage(ItemStack &tool, int count) {
    auto nbt = tool.getNbt();
    //logger.debug("before:{}", nbt->toSNBT());
    if (nbt->contains("tag")) {//必须判断否则会报错
        auto tag = nbt->getCompound("tag");
        if (tag->contains("Damage")) {
            if (tag->getInt("Damage") + count < tool.getMaxDamage()) {
                tag->putInt("Damage", tag->getInt("Damage") + count);
                //logger.debug("{}", tag->getInt("Damage"));

                tool.setNbt(nbt.get());
                //logger.debug("after:{}", tool.getNbt()->toSNBT());
                return true;
            }
            else return false;
        }
        else { //没有Damage
            tag->putInt("Damage", count);
            tool.setNbt(nbt.get());
        }
    }
    else { //没有tag
        auto compoundTag = CompoundTag::create();
        compoundTag->putInt("Damage", count);
        nbt->putCompound("tag", std::unique_ptr<CompoundTag>(compoundTag.release()));
        tool.setNbt(nbt.get());
        //logger.debug("new damage:{}", nbt->toSNBT());
    }
    return true;
}

int countTaskList() {
    return (int)task_list.size();
}

int countChainingBlocks() {
    return (int)chaining_blocks.size();
}

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
            if (Economic::mode > 0) {
                long long cost = block_list[mi.name].cost * (mi.cnt - 1);//有一个是自己挖的
                if (cost > 0) {
                    Economic::reduceMoney(mi.pl, cost);
                    msg += config_j["msg"]["money.use"];
                    msg = s_replace(msg, "%Cost%", std::to_string(cost));
                    msg = s_replace(msg, "%Remain%", std::to_string(Economic::getMoney(mi.pl)));
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
