// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA

#undef BEFORE_EXTRA

class InsideWaterlilyBlockSystemImpl {

#define AFTER_EXTRA

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_INSIDEWATERLILYBLOCKSYSTEMIMPL
public:
    class InsideWaterlilyBlockSystemImpl& operator=(class InsideWaterlilyBlockSystemImpl const &) = delete;
    InsideWaterlilyBlockSystemImpl(class InsideWaterlilyBlockSystemImpl const &) = delete;
    InsideWaterlilyBlockSystemImpl() = delete;
#endif


public:
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_INSIDEWATERLILYBLOCKSYSTEMIMPL
#endif
    MCAPI static void _tickMovementSystem(class StrictEntityContext const &, struct InsideBlockWithPosComponent<struct WaterlilyBlockFlag> const &, struct StateVectorComponent &);



};