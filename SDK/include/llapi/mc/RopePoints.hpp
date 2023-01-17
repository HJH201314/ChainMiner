/**
 * @file  RopePoints.hpp
 * @note  This Header is auto generated by LiteLoaderBDS Toolchain.
 *
 */
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA

#undef BEFORE_EXTRA

/**
 * @brief MC class RopePoints.
 *
 */
class RopePoints {

#define AFTER_EXTRA

#undef AFTER_EXTRA
#ifndef DISABLE_CONSTRUCTOR_PREVENTION_ROPEPOINTS
public:
    class RopePoints& operator=(class RopePoints const &) = delete;
    RopePoints(class RopePoints const &) = delete;
    RopePoints() = delete;
#endif

public:
    /**
     * @symbol ?beginRope@RopePoints@@QEAAXXZ
     * @hash   -1140505533
     */
    MCAPI void beginRope();
    /**
     * @symbol ?endRope@RopePoints@@QEAAXXZ
     * @hash   -688431533
     */
    MCAPI void endRope();
    /**
     * @symbol ?freezeInterpolation@RopePoints@@QEAAXXZ
     * @hash   -286130013
     */
    MCAPI void freezeInterpolation();
    /**
     * @symbol ?pushBack@RopePoints@@QEAAXAEBVVec3@@@Z
     * @hash   836364564
     */
    MCAPI void pushBack(class Vec3 const &);
    /**
     * @symbol ?reserve@RopePoints@@QEAAX_K@Z
     * @hash   866406537
     */
    MCAPI void reserve(unsigned __int64);
    /**
     * @symbol ?size@RopePoints@@QEBA_KXZ
     * @hash   -1925128255
     */
    MCAPI unsigned __int64 size() const;
    /**
     * @symbol ??1RopePoints@@QEAA@XZ
     * @hash   957538303
     */
    MCAPI ~RopePoints();

};