/**
 * @file  CurrentSwimAmountSystem.hpp
 *
 */
#pragma once
#define AUTO_GENERATED
#include "llapi/Global.h"

#define BEFORE_EXTRA

#undef BEFORE_EXTRA

/**
 * @brief MC class CurrentSwimAmountSystem.
 *
 */
class CurrentSwimAmountSystem {

#define AFTER_EXTRA

#undef AFTER_EXTRA
#ifndef DISABLE_CONSTRUCTOR_PREVENTION_CURRENTSWIMAMOUNTSYSTEM
public:
    class CurrentSwimAmountSystem& operator=(class CurrentSwimAmountSystem const &) = delete;
    CurrentSwimAmountSystem(class CurrentSwimAmountSystem const &) = delete;
    CurrentSwimAmountSystem() = delete;
#endif

public:
    /**
     * @symbol ?createSystem\@CurrentSwimAmountSystem\@\@SA?AUTickingSystemWithInfo\@\@XZ
     */
    MCAPI static struct TickingSystemWithInfo createSystem();
    /**
     * @symbol ?tick\@CurrentSwimAmountSystem\@\@SAXV?$ViewT\@VStrictEntityContext\@\@VEntityRegistryBase\@\@U?$Include\@V?$FlagComponent\@UActorMovementTickNeededFlag\@\@\@\@\@\@USwimAmountComponent\@\@$$CBUSynchedActorDataComponent\@\@\@\@\@Z
     */
    MCAPI static void tick(class ViewT<class StrictEntityContext, class EntityRegistryBase, struct Include<class FlagComponent<struct ActorMovementTickNeededFlag>>, struct SwimAmountComponent, struct SynchedActorDataComponent const>);

//private:
    /**
     * @symbol ?_doCurrentSwimAmountSystem\@CurrentSwimAmountSystem\@\@CAXAEBVStrictEntityContext\@\@AEAUSwimAmountComponent\@\@AEBUSynchedActorDataComponent\@\@\@Z
     */
    MCAPI static void _doCurrentSwimAmountSystem(class StrictEntityContext const &, struct SwimAmountComponent &, struct SynchedActorDataComponent const &);

private:

};
