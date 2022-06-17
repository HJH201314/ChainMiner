// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Json.hpp"
#include "Item.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ArmorItem : public Item {

#define AFTER_EXTRA
// Add Member There
public:
class ArmorMaterial {
public:
    ArmorMaterial() = delete;
    ArmorMaterial(ArmorMaterial const&) = delete;
    ArmorMaterial(ArmorMaterial const&&) = delete;
};

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_ARMORITEM
public:
    class ArmorItem& operator=(class ArmorItem const &) = delete;
    ArmorItem(class ArmorItem const &) = delete;
    ArmorItem() = delete;
#endif


public:
    /*0*/ virtual ~ArmorItem();
    /*7*/ virtual void __unk_vfn_7();
    /*10*/ virtual void __unk_vfn_10();
    /*11*/ virtual bool isArmor() const;
    /*13*/ virtual void __unk_vfn_13();
    /*15*/ virtual void __unk_vfn_15();
    /*17*/ virtual bool isDyeable() const;
    /*51*/ virtual void __unk_vfn_51();
    /*53*/ virtual void __unk_vfn_53();
    /*60*/ virtual void appendFormattedHovertext(class ItemStackBase const &, class Level &, std::string &, bool) const;
    /*61*/ virtual bool isValidRepairItem(class ItemStackBase const &, class ItemStackBase const &, class BaseGameVersion const &) const;
    /*62*/ virtual int getEnchantSlot() const;
    /*63*/ virtual int getEnchantValue() const;
    /*64*/ virtual int getArmorValue() const;
    /*65*/ virtual int getToughnessValue() const;
    /*66*/ virtual void __unk_vfn_66();
    /*68*/ virtual int getDamageChance(int) const;
    /*70*/ virtual void __unk_vfn_70();
    /*71*/ virtual void __unk_vfn_71();
    /*72*/ virtual void __unk_vfn_72();
    /*73*/ virtual class mce::Color getColor(class CompoundTag const *, class ItemDescriptor const &) const;
    /*74*/ virtual bool hasCustomColor(class CompoundTag const *) const;
    /*75*/ virtual void __unk_vfn_75();
    /*76*/ virtual void clearColor(class ItemStackBase &) const;
    /*78*/ virtual void setColor(class ItemStackBase &, class mce::Color const &) const;
    /*79*/ virtual void __unk_vfn_79();
    /*80*/ virtual void __unk_vfn_80();
    /*82*/ virtual int buildIdAux(short, class CompoundTag const *) const;
    /*84*/ virtual class ItemStack & use(class ItemStack &, class Player &) const;
    /*85*/ virtual bool dispense(class BlockSource &, class Container &, int, class Vec3 const &, unsigned char) const;
    /*89*/ virtual void hurtActor(class ItemStack &, class Actor &, class Mob &) const;
    /*93*/ virtual bool mineBlock(class ItemStack &, class Block const &, int, int, int, class Actor *) const;
    /*119*/ virtual struct TextureUVCoordinateSet const & getIcon(class ItemStackBase const &, int, bool) const;
    /*121*/ virtual class Item & setIcon(std::string const &, int);
    /*133*/ virtual float getArmorKnockbackResistance() const;
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_ARMORITEM
#endif
    MCAPI ArmorItem(std::string const &, int, class ArmorItem::ArmorMaterial const &, int, enum ArmorSlot);
    MCAPI static class ArmorItem::ArmorMaterial const CHAIN;
    MCAPI static class ArmorItem::ArmorMaterial const DIAMOND;
    MCAPI static class ArmorItem::ArmorMaterial const ELYTRA;
    MCAPI static class ArmorItem::ArmorMaterial const GOLD;
    MCAPI static class ArmorItem::ArmorMaterial const IRON;
    MCAPI static class ArmorItem::ArmorMaterial const LEATHER;
    MCAPI static class ArmorItem::ArmorMaterial const NETHERITE;
    MCAPI static class ArmorItem::ArmorMaterial const TURTLE;
    MCAPI static bool dispenseArmor(class BlockSource &, class Container &, int, class Vec3 const &, unsigned char, enum ArmorSlot);
    MCAPI static enum ArmorSlot getSlotForItem(class ItemStackBase const &);
    MCAPI static bool isDamageable(class ItemDescriptor const &);
    MCAPI static int const mHealthPerSlot[];

//private:
    MCAPI class ItemInstance getTierItem() const;


private:


};