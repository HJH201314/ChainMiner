/**
 * @file  IgniteSubcomponent.hpp
 * @note  This Header is auto generated by LiteLoaderBDS Toolchain.
 *
 */
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

/**
 * @brief MC class IgniteSubcomponent.
 *
 */
class IgniteSubcomponent {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA
#ifndef DISABLE_CONSTRUCTOR_PREVENTION_IGNITESUBCOMPONENT
public:
    class IgniteSubcomponent& operator=(class IgniteSubcomponent const &) = delete;
    IgniteSubcomponent(class IgniteSubcomponent const &) = delete;
#endif

public:
    /**
     * @vftbl  0
     * @hash   1677797297
     */
    virtual ~IgniteSubcomponent();
    /**
     * @vftbl  1
     * @hash   -1316591615
     */
    virtual void __unk_vfn_1();
    /**
     * @vftbl  2
     * @hash   -1315668094
     */
    virtual void __unk_vfn_2();
    /**
     * @vftbl  3
     * @symbol ?doOnHitEffect@IgniteSubcomponent@@UEAAXAEAVActor@@AEAVProjectileComponent@@@Z
     * @hash   813866411
     */
    virtual void doOnHitEffect(class Actor &, class ProjectileComponent &);
    /**
     * @vftbl  4
     * @symbol ?getName@IgniteSubcomponent@@UEAAPEBDXZ
     * @hash   1663840982
     */
    virtual char const * getName();
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_IGNITESUBCOMPONENT
    /**
     * @symbol ?readfromJSON@IgniteSubcomponent@@UEAAXAEAVValue@Json@@AEBVSemVersion@@@Z
     * @hash   -138370239
     */
    MCVAPI void readfromJSON(class Json::Value &, class SemVersion const &);
    /**
     * @symbol ?writetoJSON@IgniteSubcomponent@@UEBAXAEAVValue@Json@@@Z
     * @hash   -1290587432
     */
    MCVAPI void writetoJSON(class Json::Value &) const;
#endif
    /**
     * @symbol ??0IgniteSubcomponent@@QEAA@XZ
     * @hash   -1528674637
     */
    MCAPI IgniteSubcomponent();

};