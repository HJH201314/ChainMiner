// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Feature.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class IcebergFeature : public Feature {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_ICEBERGFEATURE
public:
    class IcebergFeature& operator=(class IcebergFeature const &) = delete;
    IcebergFeature(class IcebergFeature const &) = delete;
    IcebergFeature() = delete;
#endif


public:
    /*0*/ virtual ~IcebergFeature();
    /*2*/ virtual void __unk_vfn_2();
    /*3*/ virtual bool place(class BlockSource &, class BlockPos const &, class Random &) const;
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_ICEBERGFEATURE
#endif

//private:
    MCAPI void carve(int, int, class BlockPos const &, class BlockSource &, bool, float, class BlockPos const &, int, int) const;
    MCAPI void generateIcebergBlock(class BlockSource &, class Random &, class BlockPos const &, int, int, int, int, int, int, bool, bool, float, int, class Block const &) const;
    MCAPI int heightDependentRadiusRound(class Random &, int, int, int) const;
    MCAPI float signedDistanceEllipse(int, int, class BlockPos const &, int, int, float) const;


private:


};