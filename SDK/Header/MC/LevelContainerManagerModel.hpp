// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "ContainerManagerModel.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class LevelContainerManagerModel : public ContainerManagerModel {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_LEVELCONTAINERMANAGERMODEL
public:
    class LevelContainerManagerModel& operator=(class LevelContainerManagerModel const &) = delete;
    LevelContainerManagerModel(class LevelContainerManagerModel const &) = delete;
    LevelContainerManagerModel() = delete;
#endif


public:
    /*0*/ virtual ~LevelContainerManagerModel();
    /*6*/ virtual std::vector<class ItemStack> getItemCopies() const;
    /*7*/ virtual void setSlot(int, class ItemStack const &, bool);
    /*8*/ virtual class ItemStack const & getSlot(int) const;
    /*9*/ virtual void setData(int, int);
    /*10*/ virtual void broadcastChanges();
    /*16*/ virtual bool isValid(float);
    /*17*/ virtual class ContainerScreenContext _postInit();
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_LEVELCONTAINERMANAGERMODEL
#endif
    MCAPI LevelContainerManagerModel(enum ContainerID, class Player &, class BlockPos const &, enum BlockActorType);
    MCAPI LevelContainerManagerModel(enum ContainerID, class Player &, struct ActorUniqueID);
    MCAPI class BlockPos const & getBlockPos() const;
    MCAPI struct ActorUniqueID getEntityUniqueID() const;

//protected:
    MCAPI class BlockActor * _getBlockEntity();
    MCAPI class Container * _getRawContainer();


protected:


};