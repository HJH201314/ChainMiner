#pragma once

#ifndef CHAINMINER_PLUGIN_H
#define CHAINMINER_PLUGIN_H
//init
void initEventOnPlayerDestroy();

//void initEventOnBlockChange();

void registerCommand();

//miner
void miner1(int id, BlockPos* pos, bool sub = false);
void miner2(int task_id, BlockPos* start_pos);

//funcs
string getBlockDimAndPos(BlockInstance& bli);

#include <llapi/mc/CompoundTag.hpp>//compile needed

short getEnchantLevel(std::unique_ptr<CompoundTag>& nbt, short id);

int getDamageFromNbt(std::unique_ptr<CompoundTag>& nbt);

int toolDamage(ItemStack& tool, int count);

int countTaskList();

//int countPos2Id();

int countChainingBlocks();

#endif //CHAINMINER_PLUGIN_H