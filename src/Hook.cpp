#include "pch.h"
#include <llapi/HookAPI.h>
#include <llapi/mc/Level.hpp>
#include <llapi/mc/Player.hpp>
#include <llapi/mc/ItemStack.hpp>
#include <llapi/mc/CommandOrigin.hpp>

// ?playerDestroy@BlockLegacy@@MEBAXAEAVPlayer@@AEBVBlockPos@@AEBVBlock@@@Z

/*extern Logger logger;

TInstanceHook(bool, "?playerDestroy@BlockLegacy@@MEBAXAEAVPlayer@@AEBVBlockPos@@AEBVBlock@@@Z", BlockLegacy, Player* player, const BlockPos* pos, const Block* block) {
    if (player != nullptr && player->isPlayer()) {
        logger.debug("{}", pos->toString());
        auto bi = Level::getBlockInstance(*pos, player->getDimensionId());
        auto pl = player;
        ItemStack item = pl->getSelectedItem();
#include "Plugin.h"
        logger.debug("{}", item.getNbt()->toJson(2));
        item.setDamageValue(50);
        logger.debug("{}", item.getNbt()->toJson(2));
        logger.debug("damage_value: {}", item.getDamageValue());
        pl->setSelectedItem(item);
        pl->refreshInventory();
    }
    return original(this, player, pos, block);
}*/

 /*TInstanceHook(bool, "?destroyBlock@SurvivalMode@@UEAA_NAEBVBlockPos@@E@Z", GameMode, BlockPos blockPos,
               unsigned __int8 uChar) {
    auto player = getPlayer();
    if (player && player->isPlayer()) {
        if (player->getPlayerGameType() != GameType::Creative) {
            auto bi = Level::getBlockInstance(blockPos, player->getDimensionId());

        }
    }
     return original(this, blockPos, uChar);
 }*/