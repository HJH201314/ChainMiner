// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class AgentBodyControl {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_AGENTBODYCONTROL
public:
    class AgentBodyControl& operator=(class AgentBodyControl const &) = delete;
    AgentBodyControl(class AgentBodyControl const &) = delete;
#endif

public:
    /*0*/ virtual ~AgentBodyControl();
    /*1*/ virtual void clientTick(class Mob &);
    MCAPI AgentBodyControl();

protected:

private:

};