// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "persona.hpp"

#define BEFORE_EXTRA

#undef BEFORE_EXTRA

class AnimatedImageData {

#define AFTER_EXTRA

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_ANIMATEDIMAGEDATA
public:
    class AnimatedImageData& operator=(class AnimatedImageData const &) = delete;
    AnimatedImageData() = delete;
#endif


public:
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_ANIMATEDIMAGEDATA
#endif
    MCAPI AnimatedImageData(class AnimatedImageData const &);
    MCAPI AnimatedImageData(enum persona::AnimatedTextureType, enum persona::AnimationExpression, struct mce::Image const &, float);



};