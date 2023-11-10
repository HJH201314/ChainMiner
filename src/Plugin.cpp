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

// unordered_map<string, int> pos2id; // pos, task_id
unordered_map<int, MinerInfo> task_list;//id,cnt
unordered_set<string> chaining_blocks;//避免在call事件的时候进入死循环

extern unordered_map<string, BlockInfo> block_list;//方块列表
extern nlohmann::json config_j;

void PluginInit() {
    logger.info("初始化... v{}.{}.{}.{}", PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR, PLUGIN_VERSION_REVISION, PLUGIN_VERSION_BUILD);
    logger.info("Compiled at {}, {}", __DATE__, __TIME__);
    initConfig();
    initEventOnPlayerDestroy();
    // initEventOnBlockChanged();
    registerCommand();
    logger.info(fmt::format(fg(fmt::color::light_steel_blue) | fmt::emphasis::bold, "催更及反馈群：") + fmt::format(fg(fmt::color::gold) | fmt::emphasis::bold, "322586206"));
}

//void initEventOnBlockChanged() {
//    Event::BlockChangedEvent::subscribe([](const Event::BlockChangedEvent& e) {
//        BlockInstance bli = e.mNewBlockInstance;
//        auto blp = bli.getPosition();
//        // logger.debug("BlockChange: {},{},{}", blp.x, blp.y, blp.z);
//        if (!pos2id.empty()) {
//            auto t = pos2id.find(blp.toString());
//            if (t != pos2id.end()) {
//                miner2(t->second, &blp);
//                pos2id.erase(t->first);
//            }
//        }
//        return true;
//    });
//}

void initEventOnPlayerDestroy() {
    Event::PlayerDestroyBlockEvent::subscribe_ref([](Event::PlayerDestroyBlockEvent& e) {
        BlockInstance bli = e.mBlockInstance;
        BlockPos blp = bli.getPosition();
        // logger.debug("PlayerDestroy: {},{},{}", blp.x, blp.y, blp.z);

        if (chaining_blocks.count(getBlockDimAndPos(bli)) > 0) {
            return true;//如果是连锁采集的就不处理(pl->playerDestroy()不会触发此事件)
        }
        if (e.mPlayer->getPlayerGameType() != GameType::Survival) return true;
        if (!playerSetting.getSwitch(e.mPlayer->getXuid())) return true;
        if (playerSetting.getSwitch(e.mPlayer->getXuid(), "chain_while_sneaking_only") && !e.mPlayer->isSneaking()) return true;
        Block* bl = bli.getBlock();
        string bn = bl->getName().getString();
        // logger.debug("{} {} {} {} {},{},{}", bl->getName().getString(), bl->getId(), bl->getDescriptionId(), bl->getVariant(), blp.x, blp.y, blp.z);
        // logger.debug("{} BREAK {} AT {},{},{}", e.mPlayer->getRealName(), bl->getTypeName(), blp.x, blp.y, blp.z);
        auto r = block_list.find(bn);
        if (r != block_list.end()) {//如果是可以连锁挖掘的方块
            if (!r->second.enabled) return true;//方块全局关闭
            if (!playerSetting.getSwitch(e.mPlayer->getXuid(), bn)) return true;//方块被玩家关闭

            ItemStack* tool = (ItemStack*)&e.mPlayer->getSelectedItem();
            string toolType = tool->getTypeName();
            //logger.info("{}", toolType);
            auto& material = bl->getMaterial();

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
                int id = (int)task_list.size() + 1;
                task_list.insert(pair<int, MinerInfo>{
                    id,
                    { bn,
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

                miner2(id, &blp);

                // pos2id.insert(std::make_pair(blp.toString(), id));
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
        if (tag->contains(ItemStack::TAG_ENCHANTS)) {
            ListTag *ench = tag->getList(ItemStack::TAG_ENCHANTS);
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
     logger.debug("before: {} {}", nbt->toSNBT(), tool.getMaxDamage());
    if (ConfigManager::multiply_damage_switch) {
        double rate = ConfigManager::multiply_damage_min + (ConfigManager::multiply_damage_max - ConfigManager::multiply_damage_min) * ud(re) / 100;
        //logger.debug("rate:{}", rate);
        damage = count * rate;
    }
    // logger.debug("{} {} {}", tool.getDamageValue(), tool.hasDamageValue(), damage);
    /*tool.setDamageValue(tool.getDamageValue() + damage);*/
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
     logger.debug("after: {} {}", nbt->toSNBT(), tool.getMaxDamage());
    return damage;
}

int countTaskList() {
    return (int)task_list.size();
}

int countChainingBlocks() {
    return (int)chaining_blocks.size();
}

//使用队列进行连锁采集#include <llapi/ScheduleAPI.h>
#include <tuple>
using std::tuple;
using std::get;
void miner2(int task_id, BlockPos* start_pos) {
    queue<BlockPos> block_q;
    block_q.push(*start_pos);
    // 与方块相邻的六个方块
    static vector<tuple<int, int, int>> dirs1 = { {1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1} };
    // 以方块为中心的26个方块，优先相邻方块
    static vector<tuple<int, int, int>> dirs2 = {
        {1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}, // 相邻六个
        {1,0,1},{-1,0,1},{0,1,1},{0,-1,1},{1,1,1},{-1,-1,1},{1,-1,1},{-1,1,1}, // z+1 剩下8个
        {1,0,-1},{-1,0,-1},{0,1,-1},{0,-1,-1},{1,1,-1},{-1,-1,-1},{1,-1,-1},{-1,1,-1}, // z-1剩下8个
        {1,1,0},{-1,-1,0},{1,-1,0},{-1,1,0} // z剩下4个
    };

    // 判断使用的连锁范围
    vector<tuple<int, int, int>>& dirs = dirs1;
    if (config_j["default_detect_method"] == "cube") {
        dirs = dirs2;
    }
    
    while (task_list[task_id].cnt < task_list[task_id].limit && !block_q.empty()) {
        BlockPos curpos = block_q.front();
        for (size_t i = 0; i < dirs.size(); i++) {
            BlockPos newpos = BlockPos(
                curpos.x + get<0>(dirs[i]),
                curpos.y + get<1>(dirs[i]),
                curpos.z + get<2>(dirs[i])
            );
            Block* bl = Level::getBlock(newpos, task_list[task_id].dimId);
            auto r = block_list.find(task_list[task_id].name);
            if (bl->getName().getString() == task_list[task_id].name || v_contains(r->second.similar, bl->getName().getString())) {
                block_q.push(newpos);
            }
        }
        
        Block* bl = Level::getBlock(curpos, task_list[task_id].dimId);
        if (bl->getId() != 0) {
            //累计耐久损失
            //1.当工具未附魔耐久时
            //2.当附魔了耐久的工具踩中扣除概率1/(level+1)
            if (task_list[task_id].enchU == 0 ||
                (task_list[task_id].enchU > 0 && ud(re) < (100 / (task_list[task_id].enchU + 1))))
                task_list[task_id].cntD++;

            //破坏方块
            //主动call玩家破坏事件，当事件被拦截时结束连锁（某个方块进入了领地等）
            //TODO(低优先级):应当连锁所有能连锁的方块而不是一遇到拦截就结束
            auto ev = new Event::PlayerDestroyBlockEvent();
            ev->mBlockInstance = Level::getBlockInstance(curpos, task_list[task_id].dimId);
            ev->mPlayer = task_list[task_id].pl;
            string dp = getBlockDimAndPos(ev->mBlockInstance);
            chaining_blocks.insert(dp);
            bool res = ev->call();
            chaining_blocks.erase(dp);
            if (!res) {
                break;
            }
            else {
                // 非首个方块才进行模拟挖掘
                if (task_list[task_id].cnt != 0)
                    bl->playerDestroy(*task_list[task_id].pl, curpos); // playerDestroy仅生成掉落物
                Level::setBlock(curpos, task_list[task_id].dimId, "minecraft:air", 0);
                task_list[task_id].cnt++;
            }
        }
        block_q.pop();
    }

    //在下一刻进行结果计算，否则手持物品无法更新
    Schedule::nextTick([&, task_id]() {
        MinerInfo mi = task_list[task_id];
        if (mi.cnt > 0) {
            //减少耐久
            ItemStack tool = mi.pl->getSelectedItem();
            int dmg = toolDamage(tool, mi.cntD);
            //手动给玩家替换工具
            // mi.pl->setItemSlot(mi.pl->getEquipmentSlotForItem(tool), tool);
            mi.pl->setSelectedItem(tool);
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
            // 开启了成功提示且采集多个方块时发送提示
            if (config_j["switch"]["mine.success"] && mi.cnt > 1)
                mi.pl->sendTextPacket(msg);
        }

        task_list.erase(task_id);
        });
}
