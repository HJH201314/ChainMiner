// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Feature.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class SeaAnemoneFeature : public Feature {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_SEAANEMONEFEATURE
public:
    class SeaAnemoneFeature& operator=(class SeaAnemoneFeature const &) = delete;
    SeaAnemoneFeature(class SeaAnemoneFeature const &) = delete;
    SeaAnemoneFeature() = delete;
#endif


public:
    /*0*/ virtual ~SeaAnemoneFeature();
    /*2*/ virtual void __unk_vfn_2();
    /*3*/ virtual bool place(class BlockSource &, class BlockPos const &, class Random &) const;
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_SEAANEMONEFEATURE
#endif



};