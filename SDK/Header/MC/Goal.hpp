// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class Goal {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_GOAL
public:
    class Goal& operator=(class Goal const &) = delete;
    Goal(class Goal const &) = delete;
#endif


public:
    /*0*/ virtual ~Goal();
    /*1*/ virtual void __unk_vfn_1() = 0;
    /*2*/ virtual bool canContinueToUse();
    /*3*/ virtual bool canBeInterrupted();
    /*4*/ virtual void __unk_vfn_4() = 0;
    /*5*/ virtual void __unk_vfn_5();
    /*6*/ virtual void __unk_vfn_6();
    /*7*/ virtual void __unk_vfn_7();
    /*8*/ virtual bool isTargetGoal() const;
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_GOAL
    MCVAPI void onPlayerDimensionChanged(class Player *, class AutomaticID<class Dimension, int>);
    MCVAPI void start();
    MCVAPI void stop();
    MCVAPI void tick();
#endif
    MCAPI Goal();
    MCAPI int getRequiredControlFlags() const;
    MCAPI unsigned short getTypeId() const;
    MCAPI void setRequiredControlFlags(int);
    MCAPI void setTypeId(unsigned short);



};