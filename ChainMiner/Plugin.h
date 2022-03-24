#pragma once

#ifndef CHAINMINER_PLUGIN_H
#define CHAINMINER_PLUGIN_H
//init
void initEventOnPlayerDestroy();

//void initEventOnBlockChange();

void registerCommand();

//miner
void miner1(int id, BlockPos* pos, bool sub = false);

//funcs
string getBlockDimAndPos(BlockInstance& bli);

#include <MC/CompoundTag.hpp>//compile needed

short getEnchantLevel(std::unique_ptr<CompoundTag>& nbt, short id);

int getDamageFromNbt(std::unique_ptr<CompoundTag>& nbt);

bool toolDamage(ItemStack& tool, int count);

int countTaskList();

//int countPos2Id();

int countChainingBlocks();

#endif //CHAINMINER_PLUGIN_H