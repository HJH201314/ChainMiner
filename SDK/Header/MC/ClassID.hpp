// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ClassID {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_CLASSID
public:
    class ClassID& operator=(class ClassID const &) = delete;
    ClassID(class ClassID const &) = delete;
    ClassID() = delete;
#endif

public:

protected:

private:
    MCAPI static unsigned __int64 getNextID();

};