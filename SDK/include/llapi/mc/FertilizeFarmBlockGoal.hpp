/**
 * @file  FertilizeFarmBlockGoal.hpp
 * @note  This Header is auto generated by LiteLoaderBDS Toolchain.
 *
 */
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "BaseMoveToBlockGoal.hpp"

#define BEFORE_EXTRA

#undef BEFORE_EXTRA

/**
 * @brief MC class FertilizeFarmBlockGoal.
 *
 */
class FertilizeFarmBlockGoal : public BaseMoveToBlockGoal {

#define AFTER_EXTRA

#undef AFTER_EXTRA
#ifndef DISABLE_CONSTRUCTOR_PREVENTION_FERTILIZEFARMBLOCKGOAL
public:
    class FertilizeFarmBlockGoal& operator=(class FertilizeFarmBlockGoal const &) = delete;
    FertilizeFarmBlockGoal(class FertilizeFarmBlockGoal const &) = delete;
    FertilizeFarmBlockGoal() = delete;
#endif

public:
    /**
     * @vftbl  0
     * @hash   1021698212
     */
    virtual ~FertilizeFarmBlockGoal();
    /**
     * @vftbl  1
     * @symbol ?canUse@FertilizeFarmBlockGoal@@UEAA_NXZ
     * @hash   953842390
     */
    virtual bool canUse();
    /**
     * @vftbl  2
     * @symbol ?canContinueToUse@FertilizeFarmBlockGoal@@UEAA_NXZ
     * @hash   -637912332
     */
    virtual bool canContinueToUse();
    /**
     * @vftbl  3
     * @hash   -1264449677
     */
    virtual void __unk_vfn_3();
    /**
     * @vftbl  4
     * @symbol ?start@FertilizeFarmBlockGoal@@UEAAXXZ
     * @hash   33948607
     */
    virtual void start();
    /**
     * @vftbl  5
     * @symbol ?stop@FertilizeFarmBlockGoal@@UEAAXXZ
     * @hash   -1664116929
     */
    virtual void stop();
    /**
     * @vftbl  6
     * @symbol ?tick@FertilizeFarmBlockGoal@@UEAAXXZ
     * @hash   1903273818
     */
    virtual void tick();
    /**
     * @vftbl  7
     * @symbol ?appendDebugInfo@FertilizeFarmBlockGoal@@UEBAXAEAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z
     * @hash   -178102774
     */
    virtual void appendDebugInfo(std::string &) const;
    /**
     * @vftbl  8
     * @hash   -1310126968
     */
    virtual void __unk_vfn_8();
    /**
     * @vftbl  9
     * @hash   -1251451191
     */
    virtual void __unk_vfn_9();
    /**
     * @vftbl  11
     * @symbol ?isValidTarget@FertilizeFarmBlockGoal@@MEAA_NAEAVBlockSource@@AEBVBlockPos@@@Z
     * @hash   -572474991
     */
    virtual bool isValidTarget(class BlockSource &, class BlockPos const &);
    /**
     * @symbol ??0FertilizeFarmBlockGoal@@QEAA@AEAVMob@@@Z
     * @hash   -1650803709
     */
    MCAPI FertilizeFarmBlockGoal(class Mob &);

//protected:
    /**
     * @symbol ?tryFertilizeCrop@FertilizeFarmBlockGoal@@IEAA_NAEAVBlockSource@@AEBVBlockPos@@@Z
     * @hash   -1735868554
     */
    MCAPI bool tryFertilizeCrop(class BlockSource &, class BlockPos const &);

//private:
    /**
     * @symbol ?_findFertilizer@FertilizeFarmBlockGoal@@AEAA_NXZ
     * @hash   -130631738
     */
    MCAPI bool _findFertilizer();

protected:

private:

};