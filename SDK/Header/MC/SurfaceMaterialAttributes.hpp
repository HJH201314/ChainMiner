// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

struct SurfaceMaterialAttributes {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_SURFACEMATERIALATTRIBUTES
public:
    struct SurfaceMaterialAttributes& operator=(struct SurfaceMaterialAttributes const &) = delete;
    SurfaceMaterialAttributes() = delete;
#endif

public:
    MCAPI SurfaceMaterialAttributes(struct SurfaceMaterialAttributes &&);
    MCAPI SurfaceMaterialAttributes(struct SurfaceMaterialAttributes const &);
    MCAPI struct SurfaceMaterialAttributes & operator=(struct SurfaceMaterialAttributes &&);
    MCAPI ~SurfaceMaterialAttributes();

protected:

private:

};