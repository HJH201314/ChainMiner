/**
 * @file  RepeaterBlock.hpp
 * @note  This Header is auto generated by LiteLoaderBDS Toolchain.
 *
 */
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "DiodeBlock.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

/**
 * @brief MC class RepeaterBlock.
 *
 */
class RepeaterBlock : public DiodeBlock {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA
#ifndef DISABLE_CONSTRUCTOR_PREVENTION_REPEATERBLOCK
public:
    class RepeaterBlock& operator=(class RepeaterBlock const &) = delete;
    RepeaterBlock(class RepeaterBlock const &) = delete;
    RepeaterBlock() = delete;
#endif

public:
    /**
     * @vftbl  0
     * @hash   -1443393485
     */
    virtual ~RepeaterBlock();
    /**
     * @vftbl  19
     * @hash   -227039124
     */
    virtual void __unk_vfn_19();
    /**
     * @vftbl  29
     * @hash   -198409973
     */
    virtual void __unk_vfn_29();
    /**
     * @vftbl  30
     * @hash   -178092511
     */
    virtual void __unk_vfn_30();
    /**
     * @vftbl  32
     * @hash   -176245469
     */
    virtual void __unk_vfn_32();
    /**
     * @vftbl  33
     * @hash   -175321948
     */
    virtual void __unk_vfn_33();
    /**
     * @vftbl  34
     * @hash   -174398427
     */
    virtual void __unk_vfn_34();
    /**
     * @vftbl  36
     * @hash   -172551385
     */
    virtual void __unk_vfn_36();
    /**
     * @vftbl  37
     * @hash   -171627864
     */
    virtual void __unk_vfn_37();
    /**
     * @vftbl  38
     * @hash   -170704343
     */
    virtual void __unk_vfn_38();
    /**
     * @vftbl  39
     * @hash   -169780822
     */
    virtual void __unk_vfn_39();
    /**
     * @vftbl  40
     * @hash   -149463360
     */
    virtual void __unk_vfn_40();
    /**
     * @vftbl  41
     * @hash   -148539839
     */
    virtual void __unk_vfn_41();
    /**
     * @vftbl  42
     * @hash   -147616318
     */
    virtual void __unk_vfn_42();
    /**
     * @vftbl  44
     * @hash   -145769276
     */
    virtual void __unk_vfn_44();
    /**
     * @vftbl  45
     * @hash   -144845755
     */
    virtual void __unk_vfn_45();
    /**
     * @vftbl  46
     * @hash   -143922234
     */
    virtual void __unk_vfn_46();
    /**
     * @vftbl  47
     * @hash   -142998713
     */
    virtual void __unk_vfn_47();
    /**
     * @vftbl  48
     * @hash   -142075192
     */
    virtual void __unk_vfn_48();
    /**
     * @vftbl  49
     * @hash   -141151671
     */
    virtual void __unk_vfn_49();
    /**
     * @vftbl  54
     * @hash   -117140125
     */
    virtual void __unk_vfn_54();
    /**
     * @vftbl  60
     * @hash   -92205058
     */
    virtual void __unk_vfn_60();
    /**
     * @vftbl  61
     * @hash   -91281537
     */
    virtual void __unk_vfn_61();
    /**
     * @vftbl  64
     * @symbol ?shouldConnectToRedstone@RepeaterBlock@@UEBA_NAEAVBlockSource@@AEBVBlockPos@@H@Z
     * @hash   -1442523730
     */
    virtual bool shouldConnectToRedstone(class BlockSource &, class BlockPos const &, int) const;
    /**
     * @vftbl  75
     * @hash   -58958302
     */
    virtual void __unk_vfn_75();
    /**
     * @vftbl  79
     * @symbol ?setupRedstoneComponent@RepeaterBlock@@UEBAXAEAVBlockSource@@AEBVBlockPos@@@Z
     * @hash   1452845139
     */
    virtual void setupRedstoneComponent(class BlockSource &, class BlockPos const &) const;
    /**
     * @vftbl  82
     * @hash   -33099714
     */
    virtual void __unk_vfn_82();
    /**
     * @vftbl  92
     * @symbol ?mayPlace@RepeaterBlock@@UEBA_NAEAVBlockSource@@AEBVBlockPos@@@Z
     * @hash   -146562421
     */
    virtual bool mayPlace(class BlockSource &, class BlockPos const &) const;
    /**
     * @vftbl  100
     * @symbol ?neighborChanged@RepeaterBlock@@UEBAXAEAVBlockSource@@AEBVBlockPos@@1@Z
     * @hash   -546665161
     */
    virtual void neighborChanged(class BlockSource &, class BlockPos const &, class BlockPos const &) const;
    /**
     * @vftbl  102
     * @symbol ?asItemInstance@RepeaterBlock@@UEBA?AVItemInstance@@AEBVBlock@@PEBVBlockActor@@@Z
     * @hash   -1208944843
     */
    virtual class ItemInstance asItemInstance(class Block const &, class BlockActor const *) const;
    /**
     * @vftbl  105
     * @hash   1432640646
     */
    virtual void __unk_vfn_105();
    /**
     * @vftbl  123
     * @hash   1488051906
     */
    virtual void __unk_vfn_123();
    /**
     * @vftbl  125
     * @hash   1489898948
     */
    virtual void __unk_vfn_125();
    /**
     * @vftbl  126
     * @hash   1490822469
     */
    virtual void __unk_vfn_126();
    /**
     * @vftbl  131
     * @hash   1514834015
     */
    virtual void __unk_vfn_131();
    /**
     * @vftbl  151
     * @symbol ?animateTick@RepeaterBlock@@UEBAXAEAVBlockSource@@AEBVBlockPos@@AEAVRandom@@@Z
     * @hash   -1533563046
     */
    virtual void animateTick(class BlockSource &, class BlockPos const &, class Random &) const;
    /**
     * @vftbl  156
     * @hash   1576709922
     */
    virtual void __unk_vfn_156();
    /**
     * @vftbl  163
     * @symbol ?onRemove@RepeaterBlock@@UEBAXAEAVBlockSource@@AEBVBlockPos@@@Z
     * @hash   2082607290
     */
    virtual void onRemove(class BlockSource &, class BlockPos const &) const;
    /**
     * @vftbl  166
     * @hash   1547586817
     */
    virtual void __unk_vfn_166();
    /**
     * @vftbl  167
     * @hash   1548510338
     */
    virtual void __unk_vfn_167();
    /**
     * @vftbl  168
     * @hash   1549433859
     */
    virtual void __unk_vfn_168();
    /**
     * @vftbl  169
     * @symbol ?onPlace@RepeaterBlock@@UEBAXAEAVBlockSource@@AEBVBlockPos@@@Z
     * @hash   -1223374577
     */
    virtual void onPlace(class BlockSource &, class BlockPos const &) const;
    /**
     * @vftbl  172
     * @hash   1630274140
     */
    virtual void __unk_vfn_172();
    /**
     * @vftbl  173
     * @symbol ?tick@RepeaterBlock@@UEBAXAEAVBlockSource@@AEBVBlockPos@@AEAVRandom@@@Z
     * @hash   1755472891
     */
    virtual void tick(class BlockSource &, class BlockPos const &, class Random &) const;
    /**
     * @vftbl  176
     * @hash   1626510864
     */
    virtual void __unk_vfn_176();
    /**
     * @vftbl  178
     * @symbol ?use@RepeaterBlock@@UEBA_NAEAVPlayer@@AEBVBlockPos@@E@Z
     * @hash   -1522631046
     */
    virtual bool use(class Player &, class BlockPos const &, unsigned char) const;
    /**
     * @vftbl  179
     * @symbol ?canSurvive@RepeaterBlock@@UEBA_NAEAVBlockSource@@AEBVBlockPos@@@Z
     * @hash   -1944048085
     */
    virtual bool canSurvive(class BlockSource &, class BlockPos const &) const;
    /**
     * @vftbl  186
     * @hash   1662597375
     */
    virtual void __unk_vfn_186();
    /**
     * @vftbl  188
     * @symbol ?getResourceItem@RepeaterBlock@@UEBA?AVItemInstance@@AEAVRandomize@@AEBVBlock@@H@Z
     * @hash   -1720139341
     */
    virtual class ItemInstance getResourceItem(class Randomize &, class Block const &, int) const;
    /**
     * @vftbl  193
     * @symbol ?isLocked@RepeaterBlock@@UEBA_NAEAVBlockSource@@AEBVBlockPos@@@Z
     * @hash   -1751176099
     */
    virtual bool isLocked(class BlockSource &, class BlockPos const &) const;
    /**
     * @vftbl  199
     * @symbol ?isAlternateInput@RepeaterBlock@@MEBA_NAEBVBlock@@@Z
     * @hash   1185193140
     */
    virtual bool isAlternateInput(class Block const &) const;
    /**
     * @vftbl  203
     * @symbol ?getTurnOnDelay@RepeaterBlock@@MEBAHAEBVBlock@@@Z
     * @hash   -1243693526
     */
    virtual int getTurnOnDelay(class Block const &) const;
    /**
     * @vftbl  204
     * @symbol ?getOnBlock@RepeaterBlock@@MEBAPEBVBlock@@PEBV2@@Z
     * @hash   -1169188786
     */
    virtual class Block const * getOnBlock(class Block const *) const;
    /**
     * @vftbl  205
     * @symbol ?getOffBlock@RepeaterBlock@@MEBAPEBVBlock@@PEBV2@@Z
     * @hash   -2005188286
     */
    virtual class Block const * getOffBlock(class Block const *) const;
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_REPEATERBLOCK
    /**
     * @symbol ?canBeSilkTouched@RepeaterBlock@@UEBA_NXZ
     * @hash   -67678519
     */
    MCVAPI bool canBeSilkTouched() const;
    /**
     * @symbol ?isInteractiveBlock@RepeaterBlock@@UEBA_NXZ
     * @hash   1680736024
     */
    MCVAPI bool isInteractiveBlock() const;
#endif
    /**
     * @symbol ??0RepeaterBlock@@QEAA@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H_N@Z
     * @hash   -1425768018
     */
    MCAPI RepeaterBlock(std::string const &, int, bool);
    /**
     * @symbol ?updateDelay@RepeaterBlock@@QEBAXAEAVBlockSource@@AEBVBlockPos@@_N@Z
     * @hash   1102952836
     */
    MCAPI void updateDelay(class BlockSource &, class BlockPos const &, bool) const;
    /**
     * @symbol ?DELAY_RENDER_OFFSETS@RepeaterBlock@@2QBMB
     * @hash   -1667525454
     */
    MCAPI static float const DELAY_RENDER_OFFSETS[];

//private:

private:
    /**
     * @symbol ?DELAYS@RepeaterBlock@@0QBHB
     * @hash   -1564835407
     */
    MCAPI static int const DELAYS[];

};