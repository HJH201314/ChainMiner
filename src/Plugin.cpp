#include "pch.h"

#include <llapi/mc/Level.hpp>
#include <llapi/mc/BlockInstance.hpp>
#include <llapi/mc/Block.hpp>
#include <llapi/mc/Material.hpp>
#include <llapi/mc/Actor.hpp>
#include <llapi/mc/Player.hpp>
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

std::random_device rd; //使用硬件熵源的非确定随机数生成器(类)
std::default_random_engine re(rd()); //设置随机数分布类型
std::uniform_int_distribution<int> ud(0, 99); //设置随机数返回
//std::bernoulli_distribution rand_dist(0.5);//50%生成true

typedef struct minerinfo {
    string name; //方块名称
    int dimId{}; //维度id
    int limit{}; //最大挖掘数量
    int cnt{}; //已挖掘数量
    int cntD{}; //需要扣除的耐久
    ItemStack *tool{}; //工具
    short enchU{}; //耐久附魔等级(没有为0)
    Player *pl{};
} MinerInfo;

// unordered_map<string, int> pos2id; // pos, task_id
unordered_map<int, MinerInfo> task_list; //id,cnt
unordered_set<string> chaining_blocks; //避免在call事件的时候进入死循环

extern unordered_map<string, BlockInfo> block_list; //方块列表
extern nlohmann::json config_j;

void PluginInit() {
    logger.info("初始化... v{}.{}.{}.{}", PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR, PLUGIN_VERSION_REVISION,
                PLUGIN_VERSION_BUILD);
    logger.info("Compiled at {}, {}", __DATE__, __TIME__);
    initConfig();
    initEventOnPlayerDestroy();
    registerCommand();
    logger.info(
        fmt::format(fg(fmt::color::light_steel_blue) | fmt::emphasis::bold, "催更及反馈群：") + fmt::format(
            fg(fmt::color::gold) | fmt::emphasis::bold, "322586206"));
}

void initEventOnPlayerDestroy() {
    Event::PlayerDestroyBlockEvent::subscribe_ref([](Event::PlayerDestroyBlockEvent &e) {
        // To prevent recursion while detecting block destroyability
        if (chaining_blocks.contains(getBlockDimAndPos(e.mBlockInstance))) {
            return true;
        }

        // Handle event in the next tick for compatibility
        Schedule::nextTick([=]() {
            BlockInstance bli = e.mBlockInstance;
            const BlockPos blp = bli.getPosition();
            // logger.debug("PlayerDestroy: {},{},{}", blp.x, blp.y, blp.z);

            // 仅在生存模式下可连锁
            if (e.mPlayer->getPlayerGameType() != GameType::Survival) return true;
            // 仅当玩家连锁开关打开时可连锁 (默认开启)
            if (!playerSetting.getSwitch(e.mPlayer->getXuid())) return true;
            // 开启潜行连锁 (默认关闭) 后，仅当玩家潜行时可连锁
            if (playerSetting.getSwitch(e.mPlayer->getXuid(), "chain_while_sneaking_only") && !e.mPlayer->isSneaking())
                return true;

            const Block *bl = bli.getBlock();
            const string bn = bl->getName().getString();
            // logger.debug("{} {} {} {} {},{},{}", bl->getName().getString(), bl->getId(), bl->getDescriptionId(), bl->getVariant(), blp.x, blp.y, blp.z);
            // logger.debug("{} BREAK {} AT {},{},{}", e.mPlayer->getRealName(), bl->getTypeName(), blp.x, blp.y, blp.z);

            // 检测方块是否在设置的方块列表中
            if (const auto r = block_list.find(bn); r != block_list.end()) {
                // 仅在方块连锁启用时可连锁 (默认启用)
                if (!r->second.enabled) return true;
                // 仅在玩家的相应方块开关开启时可连锁 (默认开启)
                if (!playerSetting.getSwitch(e.mPlayer->getXuid(), bn)) return true;
                auto *tool = const_cast<ItemStack *>(&e.mPlayer->getSelectedItem());
                const string toolType = tool->getTypeName();
                //logger.info("{}", toolType);
                auto &material = bl->getMaterial();

                //判断是否含有精准采集bl->getName();
                const auto nbt = tool->getNbt();
                //logger.debug("{}", nbt->toSNBT());
                const bool hasSilkTouch = getEnchantLevel(nbt, 16);

                //如果该工具无法挖掘就结束
                if (const bool canThisToolChain = (
                                                      r->second.tools.empty() //没有设置指定工具
                                                      || v_contains(r->second.tools, toolType) //使用了指定工具
                                                      || v_contains(r->second.tools, string("")) //使用空字符串允许使用手挖掘
                                                  )
                                                  && (material.isAlwaysDestroyable() || tool->canDestroySpecial(*bl)) //可挖掘
                                                  && ((r->second.enchSilkTouch == 1 && hasSilkTouch) //仅精准采集工具
                                                      || (r->second.enchSilkTouch == 0 && !hasSilkTouch) //禁止精准采集工具
                                                      || r->second.enchSilkTouch == 2) //不论是否精准采集
                                                  ; !canThisToolChain) return true;

                //logger.debug("{} is chainable using {}", bn, tool->getTypeName());
                int limit = block_list[bn].limit;
                if (tool->isDamageableItem()) {
                    limit = std::min(
                        limit,
                        static_cast<int>((tool->getMaxDamage() - getDamageFromNbt(nbt) - 1) / (
                                             ConfigManager::multiply_damage_switch
                                                 ? ConfigManager::multiply_damage_max
                                                 : 1))); //留一点耐久,防止炸掉
                }
                if (economic.mode > 0 && block_list[bn].cost > 0)
                    limit = std::min(limit, static_cast<int>(economic.getMoney(e.mPlayer) / block_list[bn].cost));

                //仅当多个时
                if (limit > 1) {
                    //add task
                    const int id = static_cast<int>(task_list.size()) + 1;
                    task_list.insert(pair<int, MinerInfo>{
                        id,
                        {
                            bn,
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

        return true;
    });
}

//get a string like "dim,x,y,z"
string getBlockDimAndPos(BlockInstance &bli) {
    string pos = to_string(bli.getDimensionId()) + ','
                 + bli.getPosition().toString();
    return pos;
}

//get enchant level with nbt && enchid
//return level (0 when non-exist)
short getEnchantLevel(const unique_ptr<CompoundTag> &nbt, const short id) {
    if (nbt->contains("tag")) {
        //必须判断否则会报错
        if (const auto tag = nbt->getCompound("tag"); tag->contains(ItemStack::TAG_ENCHANTS)) {
            for (const ListTag *ench = tag->getList(ItemStack::TAG_ENCHANTS); const auto it : *ench) {
                if (const CompoundTag *ec = it->asCompoundTag(); ec->getShort("id") == id) {
                    return ec->getShort("lvl");
                }
            }
        }
    }
    return 0;
}

int getDamageFromNbt(const unique_ptr<CompoundTag> &nbt) {
    if (nbt->contains("tag")) {
        //必须判断否则会报错
        if (const auto tag = nbt->getCompound("tag"); tag->contains("Damage")) {
            return tag->getInt("Damage");
        }
    }
    /*else {
        logger.debug("no tag:{}", nbt->toSNBT());
    }*/
    return 0;
}

int toolDamage(ItemStack &tool, const int count) {
    int damage = count;
    const auto nbt = tool.getNbt();
    // logger.debug("before: {} {}", nbt->toSNBT(), tool.getMaxDamage());
    if (ConfigManager::multiply_damage_switch) {
        const double rate = ConfigManager::multiply_damage_min + (
                          ConfigManager::multiply_damage_max - ConfigManager::multiply_damage_min) * ud(re) / 100;
        //logger.debug("rate:{}", rate);
        damage = static_cast<int>(count * rate);
    }
    // logger.debug("{} {} {}", tool.getDamageValue(), tool.hasDamageValue(), damage);
    /*tool.setDamageValue(tool.getDamageValue() + damage);*/
    if (nbt->contains("tag")) {
        //必须判断否则会报错
        if (const auto tag = nbt->getCompound("tag"); tag->contains("Damage")) {
            if (tag->getInt("Damage") + damage < tool.getMaxDamage()) {
                tag->putInt("Damage", tag->getInt("Damage") + damage);
                //logger.debug("{}", tag->getInt("Damage"));

                tool.setNbt(nbt.get());
                //logger.debug("after:{}", tool.getNbt()->toSNBT());
            } else damage = 0;
        } else {
            //没有Damage
            tag->putInt("Damage", damage);
            tool.setNbt(nbt.get());
        }
    } else {
        //没有tag
        auto compoundTag = CompoundTag::create();
        compoundTag->putInt("Damage", damage);
        nbt->putCompound("tag", unique_ptr<CompoundTag>(compoundTag.release()));
        tool.setNbt(nbt.get());
        //logger.debug("new damage:{}", nbt->toSNBT());
    }
    // logger.debug("after: {} {}", nbt->toSNBT(), tool.getMaxDamage());
    return damage;
}

int countTaskList() {
    return static_cast<int>(task_list.size());
}

int countChainingBlocks() {
    return static_cast<int>(chaining_blocks.size());
}

//使用队列进行连锁采集
#include <tuple>
using std::tuple;
using std::get;

void miner2(int task_id, const BlockPos *start_pos) {
    queue<BlockPos> block_q;
    block_q.push(*start_pos);
    // 与方块相邻的六个方块
    static vector<tuple<int, int, int> > dirs1 = {{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};
    // 以方块为中心的26个方块，优先相邻方块
    static vector<tuple<int, int, int> > dirs2 = {
        {1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}, // 相邻六个
        {1, 0, 1}, {-1, 0, 1}, {0, 1, 1}, {0, -1, 1}, {1, 1, 1}, {-1, -1, 1}, {1, -1, 1}, {-1, 1, 1}, // z+1 剩下8个
        {1, 0, -1}, {-1, 0, -1}, {0, 1, -1}, {0, -1, -1}, {1, 1, -1}, {-1, -1, -1}, {1, -1, -1}, {-1, 1, -1}, // z-1剩下8个
        {1, 1, 0}, {-1, -1, 0}, {1, -1, 0}, {-1, 1, 0} // z剩下4个
    };

    // 判断使用的连锁范围
    vector<tuple<int, int, int> > &dirs = dirs1;
    if (config_j["default_detect_method"] == "cube" || block_list[task_list[task_id].name].detectMode == "cube") {
        dirs = dirs2;
    }

    while (task_list[task_id].cnt < task_list[task_id].limit && !block_q.empty()) {
        BlockPos curpos = block_q.front();
        for (auto & dir : dirs) {
            auto newpos = BlockPos(
                curpos.x + get<0>(dir),
                curpos.y + get<1>(dir),
                curpos.z + get<2>(dir)
            );
            const Block *bl = Level::getBlock(newpos, task_list[task_id].dimId);
            if (const auto r = block_list.find(task_list[task_id].name);
                bl->getName().getString() == task_list[task_id].name ||
                v_contains(r->second.similar, bl->getName().getString())) {
                block_q.push(newpos);
            }
        }

        if (const Block *bl = Level::getBlock(curpos, task_list[task_id].dimId); bl->getId() != 0) {
            //累计耐久损失
            //1.当工具未附魔耐久时
            //2.当附魔了耐久的工具踩中扣除概率1/(level+1)
            if (task_list[task_id].enchU == 0 ||
                (task_list[task_id].enchU > 0 && ud(re) < (100 / (task_list[task_id].enchU + 1))))
                task_list[task_id].cntD++;

            //破坏方块
            //主动call玩家破坏事件，当事件被拦截时结束连锁（某个方块进入了领地等）
            //TODO(低优先级):应当连锁所有能连锁的方块而不是一遇到拦截就结束
            const auto ev = new Event::PlayerDestroyBlockEvent();
            ev->mBlockInstance = Level::getBlockInstance(curpos, task_list[task_id].dimId);
            ev->mPlayer = task_list[task_id].pl;
            string dp = getBlockDimAndPos(ev->mBlockInstance);
            chaining_blocks.insert(dp);
            const bool res = ev->call();
            chaining_blocks.erase(dp);
            if (!res) {
                break;
            } else {
                bl->playerDestroy(*task_list[task_id].pl, curpos); // playerDestroy仅生成掉落物
                Level::setBlock(curpos, task_list[task_id].dimId, "minecraft:air", 0);
                task_list[task_id].cnt++;
            }
        }
        block_q.pop();
    }

    //在下一刻进行结果计算，否则手持物品无法更新
    Schedule::nextTick([&, task_id]() {
        if (const auto [name, dimId, limit, cnt, cntD, tool, enchU, pl] = task_list[task_id]; cnt > 0) {
            //减少耐久
            ItemStack curTool = pl->getSelectedItem();
            const int dmg = toolDamage(curTool, cntD);
            //手动给玩家替换工具
            // mi.pl->setItemSlot(mi.pl->getEquipmentSlotForItem(tool), tool);
            pl->setSelectedItem(curTool);
            pl->refreshInventory();
            const string prefix = ConfigManager::msg_prefix;
            string msg = prefix;
            msg += s_replace(config_j["msg"]["mine.success"], "%Count%", std::to_string(cnt)); //有一个是自己挖的
            if (config_j["switch"]["mine.damage"]) {
                msg += (msg.length() > prefix.length() ? " " : "") + s_replace(
                    config_j["msg"]["mine.damage"], "%Damage%", std::to_string(dmg));
            }
            if (economic.mode > 0) {
                if (const long long cost = block_list[name].cost * (cnt - 1); cost > 0) {
                    economic.reduceMoney(pl, cost);
                    msg += (msg.length() > prefix.length() ? " " : "") + config_j["msg"]["money.use"];
                    msg = s_replace(msg, "%Cost%", std::to_string(cost));
                    msg = s_replace(msg, "%Remain%", std::to_string(economic.getMoney(pl)));
                    msg = s_replace(msg, "%Name%", config_j["money.name"]);
                }
            }
            if (curTool.hasDamageValue() && (curTool.getMaxDamage() - curTool.getDamageValue()) <= 2) {
                msg += (msg.length() > prefix.length() ? '\n' + prefix : "");
                msg += s_replace(config_j["msg"]["mine.damage.warning"], "%Damage%",
                                 std::to_string(curTool.getMaxDamage() - curTool.getDamageValue()));
            }
            // 开启了成功提示且采集多个方块时发送提示
            if (config_j["switch"]["mine.success"] && cnt > 1) {
                pl->sendTextPacket(msg);
            }
        }

        task_list.erase(task_id);
    });
}
