// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class JukeboxBlockActor {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_JUKEBOXBLOCKACTOR
public:
    class JukeboxBlockActor& operator=(class JukeboxBlockActor const &) = delete;
    JukeboxBlockActor(class JukeboxBlockActor const &) = delete;
    JukeboxBlockActor() = delete;
#endif


public:
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_JUKEBOXBLOCKACTOR
    MCVAPI std::unique_ptr<class BlockActorDataPacket> _getUpdatePacket(class BlockSource &);
    MCVAPI void _onUpdatePacket(class CompoundTag const &, class BlockSource &);
    MCVAPI bool canPullOutItem(class BlockSource &, int, int, class ItemInstance const &) const;
    MCVAPI bool canPushInItem(class BlockSource &, int, int, class ItemInstance const &) const;
    MCVAPI class Container * getContainer();
    MCVAPI class Container const * getContainer() const;
    MCVAPI int getContainerSize() const;
    MCVAPI class ItemStack const & getItem(int) const;
    MCVAPI int getMaxStackSize() const;
    MCVAPI void load(class Level &, class CompoundTag const &, class DataLoadHelper &);
    MCVAPI void onChanged(class BlockSource &);
    MCVAPI bool save(class CompoundTag &) const;
    MCVAPI void serverInitItemStackIds(int, int, class std::function<void (int, class ItemStack const &)>);
    MCVAPI void setItem(int, class ItemStack const &);
    MCVAPI void startOpen(class Player &);
    MCVAPI void stopOpen(class Player &);
    MCVAPI void tick(class BlockSource &);
#endif
    MCAPI JukeboxBlockActor(class BlockPos const &);
    MCAPI class ItemStack const & getRecord() const;
    MCAPI bool isRecordPlaying() const;
    MCAPI void setRecord(class ItemStack const &);
    MCAPI void stopPlayingRecord(class BlockSource &) const;

//private:
    MCAPI void _onChanged(class BlockSource &, enum LevelSoundEvent);
    MCAPI void _spawnMusicParticles(class Level &, float);


private:


};