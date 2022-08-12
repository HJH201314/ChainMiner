// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Actor.hpp"
#include "Monster.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class EnderMan : public Monster {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_ENDERMAN
public:
    class EnderMan& operator=(class EnderMan const &) = delete;
    EnderMan(class EnderMan const &) = delete;
    EnderMan() = delete;
#endif


public:
    /*14*/ virtual ~EnderMan();
    /*41*/ virtual void __unk_vfn_41();
    /*49*/ virtual void normalTick();
    /*61*/ virtual void __unk_vfn_61();
    /*68*/ virtual void __unk_vfn_68();
    /*82*/ virtual void __unk_vfn_82();
    /*85*/ virtual void __unk_vfn_85();
    /*88*/ virtual void __unk_vfn_88();
    /*96*/ virtual void __unk_vfn_96();
    /*99*/ virtual void __unk_vfn_99();
    /*106*/ virtual void __unk_vfn_106();
    /*108*/ virtual void __unk_vfn_108();
    /*109*/ virtual void __unk_vfn_109();
    /*111*/ virtual void __unk_vfn_111();
    /*132*/ virtual bool shouldRender() const;
    /*134*/ virtual enum LevelSoundEvent getAmbientSound() const;
    /*182*/ virtual void __unk_vfn_182();
    /*196*/ virtual void __unk_vfn_196();
    /*213*/ virtual bool canBeAffectedByArrow(class MobEffectInstance const &) const;
    /*222*/ virtual void __unk_vfn_222();
    /*223*/ virtual void __unk_vfn_223();
    /*248*/ virtual void __unk_vfn_248();
    /*251*/ virtual void __unk_vfn_251();
    /*269*/ virtual void __unk_vfn_269();
    /*270*/ virtual bool _hurt(class ActorDamageSource const &, float, bool, bool);
    /*273*/ virtual void readAdditionalSaveData(class CompoundTag const &, class DataLoadHelper &);
    /*274*/ virtual void addAdditionalSaveData(class CompoundTag &) const;
    /*277*/ virtual void __unk_vfn_277();
    /*285*/ virtual void __unk_vfn_285();
    /*294*/ virtual void hurtEffects(class ActorDamageSource const &, float, bool, bool);
    /*300*/ virtual void aiStep();
    /*313*/ virtual void __unk_vfn_313();
    /*317*/ virtual void __unk_vfn_317();
    /*351*/ virtual void __unk_vfn_351();
    /*360*/ virtual void newServerAiStep();
    /*365*/ virtual void __unk_vfn_365();
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_ENDERMAN
#endif
    MCAPI EnderMan(class ActorDefinitionGroup *, struct ActorDefinitionIdentifier const &, class EntityContext &);
    MCAPI class Block const & getCarryingBlock() const;
    MCAPI void setCarryingBlock(class Block const &);
    MCAPI static class std::shared_ptr<class AttributeModifier> SPEED_MODIFIER_ATTACKING;
    MCAPI static class mce::UUID const SPEED_MODIFIER_ATTACKING_UUID;
    MCAPI static class std::set<class Block const *, struct std::less<class Block const *>, class std::allocator<class Block const *>> mMayTake;
    MCAPI static void shutdown();

//private:


private:
    MCAPI static bool mMayTakeIsSetup;


};