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

#include "Config.h"
#include "Economic.h"

#include <unordered_map>
#include <random>
#include <utility>

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
} MinerInfo;

std::unordered_map<int, MinerInfo> task_list;//id,cnt

extern std::unordered_map<string, BlockInfo> block_list;//方块列表
extern nlohmann::json config_j;

bool useMoney = false;

//声明
void initEventOnPlayerDestroy();

void registerCommand();

//六向采集
void miner1(int id, BlockPos *pos, Player *pl, bool sub = false);

//便捷函数
short getEnchantLevel(std::unique_ptr<CompoundTag> &nbt, short id);

int getDamageFromNbt(std::unique_ptr<CompoundTag> &nbt);

bool toolDamage(ItemStack *tool, int count);

string s_replace(string strSrc, const string& oldStr, const string& newStr, int count = -1);

void PluginInit() {
    initConfig();
    initEventOnPlayerDestroy();
    registerCommand();
    if (config_j["money"]) {
        if (Economic::init()) {
            useMoney = true;
        } else {
            logger.info("未检测到LLMoney,付费连锁将会失效!");
        }
    }
}

void initEventOnPlayerDestroy() {
    Event::PlayerDestroyBlockEvent::subscribe([](const Event::PlayerDestroyBlockEvent &e) {
        BlockInstance bli = e.mBlockInstance;
        BlockPos blp = bli.getPosition();

        //if (chaining_blocks.contains(blp.toString())) {
        //	return true;//如果是连锁采集的就不处理(pl->playerDestroy()似乎不会触发此事件)
        //}
        Block *bl = bli.getBlock();
        string bn = bl->getTypeName();
        logger.debug("{} BREAK {} AT {},{},{}", e.mPlayer->getRealName(), bl->getTypeName(), blp.x, blp.y, blp.z);
        auto r = block_list.find(bn);
        if (r != block_list.end()) {//如果是可以连锁挖掘的方块

            ItemStack *tool = (ItemStack *) &e.mPlayer->getCarriedItem();
            auto &material = bl->getMaterial();

            //判断是否含有精准采集
            auto nbt = tool->getNbt();
            logger.debug("{}", nbt->toSNBT());
            bool hasSilkTouch = getEnchantLevel(nbt, 16);

            //如果该工具无法挖掘就结束
            bool canThisToolChain = (material.isAlwaysDestroyable() || tool->canDestroySpecial(*bl)) && !hasSilkTouch;
            if (!canThisToolChain) return true;

            //logger.debug("{} is chainable using {}", bn, tool->getTypeName());
            int limit = std::min(block_list[bn].limit, tool->getMaxDamage() - getDamageFromNbt(nbt) - 1);//留一点耐久,防止炸掉
            if (useMoney && block_list[bn].cost > 0)
                limit = std::min(limit, int(Economic::getMoney(e.mPlayer->getXuid()) / block_list[bn].cost));

            //仅当多个时
            if (limit > 1) {
                //加入临时任务
                int id = (int) task_list.size() + 1;
                task_list.insert(std::pair<int, MinerInfo>{
                        id,
                        {bn,
                         bli.getDimensionId(),
                         limit,
                         0,
                         0,
                         tool,
                         getEnchantLevel(nbt, 17)
                        }
                });
                //logger.debug("start mine task id:{} for block:{} max:{}", id, task_list[id].name, task_list[id].limit);

                miner1(id, &blp, e.mPlayer);
            }
        }
        return true;
    });
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
                logger.debug("{}", tag->getInt("Damage"));
                //由于首个方块的破坏事件未处理完成,必须手动设置nbt否则会被还原
                tool->setNbt((CompoundTag *) nbt.get());
                return true;
            }
        }
    }
    return false;
}

void miner1(int id, BlockPos *pos, Player *pl, bool sub) {
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
                    logger.debug("{} can be mine", newpos.toString());

                    //累计耐久损失
                    if (task_list[id].enchU == 0 ||
                        (task_list[id].enchU > 0 && ud(re) < (100 / (task_list[id].enchU + 1))))
                        task_list[id].cntD++;

                    //break a block
                    bl->playerDestroy(*pl, newpos);//playerDestroy有掉落物但没有移除掉方块
                    Level::destroyBlock(*Level::getBlockSource(task_list[id].dimId), newpos, false);//移除方块
                    task_list[id].cnt++;

                    miner1(id, &newpos, pl, true);
                }
            }
        }
    }
    ////超过限制数量/挖完了/没有相同方块
    end:
    if (!sub) {//是入口miner
        //减少耐久
        toolDamage(task_list[id].tool, task_list[id].cntD);
        //手动给玩家替换工具
        pl->refreshInventory();
        string msg = config_j["msg"]["mine.success"];
        msg = s_replace(msg,"%Count%",std::to_string(task_list[id].cnt));
        if (useMoney) {
            long long cost = block_list[task_list[id].name].cost * (task_list[id].cnt - 1);//有一个时自己挖的
            Economic::reduceMoney(pl->getXuid(), cost);
            msg += config_j["msg"]["money.use"];
            msg = s_replace(msg,"%Cost%",std::to_string(cost));
            msg = s_replace(msg,"%Remain%",std::to_string(Economic::getMoney(pl->getXuid())));
        }
        task_list.erase(id);
        pl->sendTextPacket(msg);
    }
    //logger.debug("task {} end.", id);
}

string s_replace(string strSrc,
                 const string& oldStr, const string& newStr, int count) {
    string strRet = strSrc;
    size_t pos = 0;
    int l_count = 0;
    if (-1 == count) // replace all
        count = strRet.size();
    while ((pos = strRet.find(oldStr, pos)) != string::npos)
    {
        strRet.replace(pos, oldStr.size(), newStr);
        if (++l_count >= count) break;
        pos += newStr.size();
    }
    return strRet;
}
