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
#include <MC/ItemStack.hpp>
#include <MC/ItemInstance.hpp>
#include <MC/ListTag.hpp>
#include <EventAPI.h>

#include "Plugin.h"
#include "Utils.h"
#include "Config.h"
#include "Economic.h"
#include "PlayerSetting.h"

#include <map>
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
    ItemStack *tool{};//工具
    short enchU;//耐久附魔等级(没有为0)
    Player* pl;
} MinerInfo;

std::unordered_map<int, MinerInfo> task_list;//id,cnt
std::map<string, int> pos2id;//"dim,x,y,z",id;使用map方便删除失败的数据
std::unordered_set<string> chaining_blocks;//

extern std::unordered_map<string, BlockInfo> block_list;//方块列表
extern nlohmann::json config_j;

extern bool useMoney;

void PluginInit() {
    initConfig();
    initEventOnPlayerDestroy();
    initEventOnBlockChange();
    registerCommand();
}

void initEventOnPlayerDestroy() {
    Event::PlayerDestroyBlockEvent::subscribe([](const Event::PlayerDestroyBlockEvent &e) {
        extern PlayerSetting playerSetting;
        if(e.mPlayer->getPlayerGameType() != 0) return true;
        if(!playerSetting.getSwitch(e.mPlayer->getXuid())) return true;
        BlockInstance bli = e.mBlockInstance;
        BlockPos blp = bli.getPosition();
        
        if (chaining_blocks.contains(getBlockDimAndPos(bli))) {
        	return true;//如果是连锁采集的就不处理(pl->playerDestroy()似乎不会触发此事件)
        }
        Block *bl = bli.getBlock();
        string bn = bl->getTypeName();
        //logger.debug("{} BREAK {} AT {},{},{}", e.mPlayer->getRealName(), bl->getTypeName(), blp.x, blp.y, blp.z);
        auto r = block_list.find(bn);
        if (r != block_list.end()) {//如果是可以连锁挖掘的方块

            ItemStack *tool = (ItemStack *) &e.mPlayer->getCarriedItem();
            auto &material = bl->getMaterial();

            //判断是否含有精准采集
            auto nbt = tool->getNbt();
            //logger.debug("{}", nbt->toSNBT());
            bool hasSilkTouch = getEnchantLevel(nbt, 16);

            //如果该工具无法挖掘就结束
            bool canThisToolChain = (material.isAlwaysDestroyable() || tool->canDestroySpecial(*bl)) && !hasSilkTouch;
            if (!canThisToolChain) return true;

            //logger.debug("{} is chainable using {}", bn, tool->getTypeName());
            int limit = block_list[bn].limit;
            if(tool->isDamageableItem())
                limit = std::min(limit, tool->getMaxDamage() - getDamageFromNbt(nbt) - 1);//留一点耐久,防止炸掉
            if (useMoney && block_list[bn].cost > 0)
                limit = std::min(limit, int(Economic::getMoney(e.mPlayer->getXuid()) / block_list[bn].cost));

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
                pos2id.insert({pos,id});
                //logger.debug("start mine task id:{} for block:{} max:{}", id, task_list[id].name, task_list[id].limit);

                //miner1(id, &blp, e.mPlayer);
            }
        }
        return true;
    });
}

void initEventOnBlockChange() {
    Event::BlockChangedEvent::subscribe([](const Event::BlockChangedEvent& e) {
        BlockInstance newBli = e.mNewBlockInstance;
        //block replaced by air
        if (newBli.getBlock()->getTypeName() == "minecraft:air") {
            BlockInstance preBli = e.mPreviousBlockInstance;
            map<string, int>::iterator it = pos2id.find(getBlockDimAndPos(preBli));
            if (it != pos2id.end()) {//this block has a task
                BlockPos blp = preBli.getPosition();
                miner1((*it).second, &blp);//execute
                ++it;//it points to the gap between two items
                for (auto i = pos2id.begin(); i != it; i++) {//rm tasks that aren't executed
                    task_list.erase((*i).second);//rm task from task_list
                }
                pos2id.erase(pos2id.begin(), it);//rm all pairs before it
                //logger.debug("{} {}", task_list.size(), pos2id.size());
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
    return 0;
}

bool toolDamage(ItemStack *tool, int count) {
    auto nbt = tool->getNbt();
    if (nbt->contains("tag")) {//必须判断否则会报错
        auto tag = nbt->getCompound("tag");
        if (tag->contains("Damage")) {
            if (tag->getInt("Damage") + count < tool->getMaxDamage()) {
                tag->putInt("Damage", tag->getInt("Damage") + count);
                //logger.debug("{}", tag->getInt("Damage"));
                //由于首个方块的破坏事件未处理完成,必须手动设置nbt否则会被还原
                tool->setNbt((CompoundTag *) nbt.get());
                return true;
            }
        }
    }
    return false;
}

int countTaskList() {
    return (int)task_list.size();
}

int countPos2Id() {
    return (int)pos2id.size();
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
                );//生成六种情况
                Block *bl = Level::getBlock(newpos, task_list[id].dimId);
                if (bl->getTypeName() == task_list[id].name) {
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
                        Level::destroyBlock(*Level::getBlockSource(task_list[id].dimId), newpos, false);//remove the block
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
            toolDamage(mi.tool, mi.cntD);
            //手动给玩家替换工具
            mi.pl->refreshInventory();
            string msg = config_j["msg"]["mine.success"];
            msg = s_replace(msg,"%Count%",std::to_string(mi.cnt));
            if (useMoney) {
                long long cost = block_list[mi.name].cost * (mi.cnt - 1);//有一个时自己挖的
                Economic::reduceMoney(mi.pl->getXuid(), cost);
                msg += config_j["msg"]["money.use"];
                msg = s_replace(msg,"%Cost%",std::to_string(cost));
                msg = s_replace(msg,"%Remain%",std::to_string(Economic::getMoney(mi.pl->getXuid())));
            }
            mi.pl->sendTextPacket(msg);
        }
        task_list.erase(id);
    }
    //logger.debug("task {} end.", id);
}
