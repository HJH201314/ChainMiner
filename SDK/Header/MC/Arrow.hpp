// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Actor.hpp"
#include "AbstractArrow.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class Arrow : public AbstractArrow {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_ARROW
public:
    class Arrow& operator=(class Arrow const &) = delete;
    Arrow(class Arrow const &) = delete;
    Arrow() = delete;
#endif


public:
    /*8*/ virtual void reloadHardcoded(enum Actor::InitializationMethod, class VariantParameterList const &);
    /*14*/ virtual ~Arrow();
    /*40*/ virtual void __unk_vfn_40();
    /*48*/ virtual void normalTick();
    /*60*/ virtual void __unk_vfn_60();
    /*67*/ virtual void __unk_vfn_67();
    /*81*/ virtual void __unk_vfn_81();
    /*87*/ virtual void __unk_vfn_87();
    /*88*/ virtual void playerTouch(class Player &);
    /*94*/ virtual void __unk_vfn_94();
    /*97*/ virtual void __unk_vfn_97();
    /*104*/ virtual void __unk_vfn_104();
    /*106*/ virtual void __unk_vfn_106();
    /*107*/ virtual void __unk_vfn_107();
    /*108*/ virtual void __unk_vfn_108();
    /*180*/ virtual void __unk_vfn_180();
    /*194*/ virtual void __unk_vfn_194();
    /*219*/ virtual void __unk_vfn_219();
    /*220*/ virtual void __unk_vfn_220();
    /*237*/ virtual void setAuxValue(int);
    /*245*/ virtual void __unk_vfn_245();
    /*248*/ virtual void __unk_vfn_248();
    /*264*/ virtual void __unk_vfn_264();
    /*268*/ virtual void readAdditionalSaveData(class CompoundTag const &, class DataLoadHelper &);
    /*269*/ virtual void addAdditionalSaveData(class CompoundTag &) const;
    /*272*/ virtual void __unk_vfn_272();
    /*281*/ virtual void __unk_vfn_281();
    /*282*/ virtual void shoot(class Vec3 const &, float, float, class Vec3 const &);
    /*284*/ virtual class ItemStack _getPickupItem() const;
    /*285*/ virtual void applyParticleColor(class Particle *);
    /*286*/ virtual class mce::Color getEffectColor();
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_ARROW
    MCVAPI bool canMakeStepSound() const;
#endif
    MCAPI Arrow(class ActorDefinitionGroup *, struct ActorDefinitionIdentifier const &, class EntityContext &);
    MCAPI void addMobEffect(class MobEffectInstance);
    MCAPI int getAuxValue() const;
    MCAPI void setCritical(bool);
    MCAPI void setEnchantFlame(int);
    MCAPI void setEnchantInfinity(int);
    MCAPI void setEnchantPower(int);
    MCAPI void setEnchantPunch(int);



};