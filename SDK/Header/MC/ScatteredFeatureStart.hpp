// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "StructureStart.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ScatteredFeatureStart : public StructureStart {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_SCATTEREDFEATURESTART
public:
    class ScatteredFeatureStart& operator=(class ScatteredFeatureStart const &) = delete;
    ScatteredFeatureStart(class ScatteredFeatureStart const &) = delete;
    ScatteredFeatureStart() = delete;
#endif


public:
    /*0*/ virtual ~ScatteredFeatureStart();
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_SCATTEREDFEATURESTART
public:
#endif
    MCAPI ScatteredFeatureStart(class BiomeSource const &, short, int, int, class IPreliminarySurfaceProvider const &);


};