// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class UseActorNode {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_USEACTORNODE
public:
    class UseActorNode& operator=(class UseActorNode const &) = delete;
    UseActorNode(class UseActorNode const &) = delete;
#endif


public:
    /*0*/ virtual ~UseActorNode();
    /*1*/ virtual enum BehaviorStatus tick(class Actor &);
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_USEACTORNODE
#endif
    MCAPI UseActorNode();



};