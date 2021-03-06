// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class DynamicJumpControl {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_DYNAMICJUMPCONTROL
public:
    class DynamicJumpControl& operator=(class DynamicJumpControl const &) = delete;
    DynamicJumpControl(class DynamicJumpControl const &) = delete;
#endif


public:
    /*0*/ virtual ~DynamicJumpControl();
    /*1*/ virtual void initializeInternal(class Mob &, struct JumpControlDescription *);
    /*2*/ virtual std::unique_ptr<class JumpControl> clone() const;
    /*3*/ virtual void tick(class JumpControlComponent &, class Mob &);
    /*4*/ virtual int getJumpDelay(class JumpControlComponent const &) const;
    /*5*/ virtual float getJumpPower(class JumpControlComponent const &) const;
    /*6*/ virtual enum JumpType getJumpType(class JumpControlComponent const &) const;
    /*7*/ virtual void setJumpType(class JumpControlComponent &, enum JumpType);
    /*8*/ virtual void resetSpeedModifier(class JumpControlComponent const &, class Mob &);
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_DYNAMICJUMPCONTROL
#endif
    MCAPI DynamicJumpControl();



};