// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "HeavyBlock.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ConcretePowderBlock : public HeavyBlock {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_CONCRETEPOWDERBLOCK
public:
    class ConcretePowderBlock& operator=(class ConcretePowderBlock const &) = delete;
    ConcretePowderBlock(class ConcretePowderBlock const &) = delete;
    ConcretePowderBlock() = delete;
#endif


public:
    /*0*/ virtual ~ConcretePowderBlock();
    /*19*/ virtual void __unk_vfn_19();
    /*29*/ virtual void __unk_vfn_29();
    /*30*/ virtual void __unk_vfn_30();
    /*32*/ virtual void __unk_vfn_32();
    /*33*/ virtual void __unk_vfn_33();
    /*34*/ virtual void __unk_vfn_34();
    /*36*/ virtual void __unk_vfn_36();
    /*37*/ virtual void __unk_vfn_37();
    /*38*/ virtual void __unk_vfn_38();
    /*39*/ virtual void __unk_vfn_39();
    /*40*/ virtual void __unk_vfn_40();
    /*41*/ virtual void __unk_vfn_41();
    /*42*/ virtual void __unk_vfn_42();
    /*44*/ virtual void __unk_vfn_44();
    /*45*/ virtual void __unk_vfn_45();
    /*46*/ virtual void __unk_vfn_46();
    /*47*/ virtual void __unk_vfn_47();
    /*48*/ virtual void __unk_vfn_48();
    /*49*/ virtual void __unk_vfn_49();
    /*54*/ virtual bool isValidAuxValue(int) const;
    /*59*/ virtual void __unk_vfn_59();
    /*60*/ virtual void __unk_vfn_60();
    /*73*/ virtual void __unk_vfn_73();
    /*80*/ virtual void __unk_vfn_80();
    /*98*/ virtual void neighborChanged(class BlockSource &, class BlockPos const &, class BlockPos const &) const;
    /*101*/ virtual class ItemInstance getResourceItem(class Randomize &, class Block const &, int) const;
    /*105*/ virtual void __unk_vfn_105();
    /*123*/ virtual bool shouldStopFalling(class Actor &) const;
    /*124*/ virtual void __unk_vfn_124();
    /*126*/ virtual void __unk_vfn_126();
    /*127*/ virtual void __unk_vfn_127();
    /*132*/ virtual void __unk_vfn_132();
    /*134*/ virtual std::string buildDescriptionId(class Block const &) const;
    /*135*/ virtual bool isAuxValueRelevantForPicking() const;
    /*148*/ virtual void __unk_vfn_148();
    /*157*/ virtual void __unk_vfn_157();
    /*158*/ virtual class ItemInstance getSilkTouchItemInstance(class Block const &) const;
    /*168*/ virtual void __unk_vfn_168();
    /*169*/ virtual void __unk_vfn_169();
    /*170*/ virtual void __unk_vfn_170();
    /*171*/ virtual void onPlace(class BlockSource &, class BlockPos const &) const;
    /*177*/ virtual void __unk_vfn_177();
    /*187*/ virtual class mce::Color getMapColor(class BlockSource &, class BlockPos const &) const;
    /*188*/ virtual void __unk_vfn_188();
    /*192*/ virtual class mce::Color getDustColor(class Block const &) const;
    /*193*/ virtual std::string getDustParticleName(class Block const &) const;
    /*194*/ virtual void __unk_vfn_194();
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_CONCRETEPOWDERBLOCK
#endif
    MCAPI ConcretePowderBlock(std::string const &, int);

//private:
    MCAPI bool _tryTouchWater(class BlockSource &, class BlockPos const &, class std::optional<enum BlockColor>) const;


private:


};