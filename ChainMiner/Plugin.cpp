#include "pch.h"

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

#include <unordered_map>
#include <unordered_set>

Logger logger("ChainMiner");

std::unordered_map<string,int> chainables {};

typedef struct minerinfo {
	string name;//方块名称
	int dimId;//维度id
	int limit;//最大挖掘数量
	int cnt;//已挖掘数量
} MinerInfo;

std::unordered_map<int, MinerInfo> task_list;//id,cnt
std::unordered_set<string> chaining_blocks;//blockpos of prechain blocks

//声明
void initEventOnPlayerDestroy();
void registerCommand();
//六向采集
void miner1(int id, BlockPos* pos, Player* pl, bool sub = false);
//便捷函数
short getEnchantLevel(std::unique_ptr<CompoundTag>& nbt, short id);

void PluginInit() {
	initConfig();
	initEventOnPlayerDestroy();
	registerCommand();
}

void initEventOnPlayerDestroy() {
	Event::PlayerDestroyBlockEvent::subscribe([](const Event::PlayerDestroyBlockEvent& e) {
		BlockInstance bli = e.mBlockInstance;
		BlockPos blp = bli.getPosition();

		//if (chaining_blocks.contains(blp.toString())) {
		//	return true;//如果是连锁采集的就不处理
		//}

		Block* bl = bli.getBlock();
		string bn = bl->getTypeName();
		logger.debug("{} BREAK {} AT {},{},{}", e.mPlayer->getRealName(), bl->getTypeName(), blp.x, blp.y, blp.z);
        logger.debug("{}","hhhh");
		auto r = chainables.find(bn);
		if (r != chainables.end()) {//如果是可以连锁挖掘的方块

			ItemStack* tool = (ItemStack*)&e.mPlayer->getCarriedItem();
			auto& material = bl->getMaterial();

			//判断是否含有精准采集
			auto nbt = tool->getNbt();
			bool hasSilkTouch = getEnchantLevel(nbt, 16);
			
			bool canThisToolChain = (material.isAlwaysDestroyable() || tool->canDestroySpecial(*bl)) && !hasSilkTouch;
			if (!canThisToolChain) return true;//如果该工具无法挖掘就结束

			//logger.debug("{} is chainable using {}", bn, tool->getTypeName());

			int id = (int)task_list.size() + 1;
			task_list.insert(std::pair<int, MinerInfo>{
				id,
				{ bn, bli.getDimensionId(), chainables[bn], 0 }
			});
			//logger.debug("start mine task id:{} for block:{} max:{}", id, task_list[id].name, task_list[id].limit);

			chaining_blocks.insert(blp.toString());
			miner1(id, &blp, e.mPlayer);
			chaining_blocks.erase(blp.toString());
		}
		return true;
		});
}

//get enchant level with nbt && enchid
//return level (0 when non-exist)
short getEnchantLevel(std::unique_ptr<CompoundTag>& nbt, short id) {
	if (nbt->contains("tag")) {//必须判断否则会报错
		auto tag = nbt->getCompound("tag");
		if (tag->contains("ench")) {
			ListTag* ench = tag->getList("ench");
			for (auto it = ench->begin(); it != ench->end(); ++it) {
				CompoundTag* ec = (*it)->asCompoundTag();
				logger.debug("ec::{} {}", ec->toSNBT(), ec->getShort("id"));
				if (ec->getShort("id") == id) {
					return ec->getShort("lvl");
				}
			}
		}
	}
	return 0;
}

#define random(x) rand()%(x)

void miner1(int id, BlockPos* pos, Player* pl, bool sub) {
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
				Block* bl = Level::getBlock(newpos, task_list[id].dimId);
				if (bl->getTypeName() == task_list[id].name && !chaining_blocks.count(newpos.toString())) {
					logger.debug("{} can be mine", newpos.toString());

                    //
					ItemStack* item = (ItemStack*)&pl->getCarriedItem();
					
					//break a block
					chaining_blocks.insert(newpos.toString());
					bl->playerDestroy(*pl, newpos);//playerDestroy并没有移除掉方块
					Level::destroyBlock(*Level::getBlockSource(task_list[id].dimId), newpos, false);//移除方块

					//update damage of the tool

					task_list[id].cnt++;
					miner1(id, &newpos, pl, true);
					chaining_blocks.erase(newpos.toString());
				}
			}
		}	
	}
	////超过限制数量/挖完了/没有相同方块
end:
	if (!sub) {//入口miner
		task_list.erase(id);
	}
	//logger.debug("task {} end.", id);

	return;
}
