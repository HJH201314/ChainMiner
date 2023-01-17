/**
 * @file  FireworksItem.hpp
 * @note  This Header is auto generated by LiteLoaderBDS Toolchain.
 *
 */
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Json.hpp"
#include "Item.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

/**
 * @brief MC class FireworksItem.
 *
 */
class FireworksItem : public Item {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA
#ifndef DISABLE_CONSTRUCTOR_PREVENTION_FIREWORKSITEM
public:
    class FireworksItem& operator=(class FireworksItem const &) = delete;
    FireworksItem(class FireworksItem const &) = delete;
    FireworksItem() = delete;
#endif

public:
    /**
     * @vftbl  0
     * @hash   -1883641459
     */
    virtual ~FireworksItem();
    /**
     * @vftbl  7
     * @hash   -1253298233
     */
    virtual void __unk_vfn_7();
    /**
     * @vftbl  11
     * @hash   -234427292
     */
    virtual void __unk_vfn_11();
    /**
     * @vftbl  14
     * @hash   -231656729
     */
    virtual void __unk_vfn_14();
    /**
     * @vftbl  16
     * @hash   -229809687
     */
    virtual void __unk_vfn_16();
    /**
     * @vftbl  51
     * @hash   -119910688
     */
    virtual void __unk_vfn_51();
    /**
     * @vftbl  53
     * @hash   -118063646
     */
    virtual void __unk_vfn_53();
    /**
     * @vftbl  56
     * @symbol ?isDestructive@FireworksItem@@UEBA_NH@Z
     * @hash   -559349684
     */
    virtual bool isDestructive(int) const;
    /**
     * @vftbl  60
     * @symbol ?appendFormattedHovertext@FireworksItem@@UEBAXAEBVItemStackBase@@AEAVLevel@@AEAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z
     * @hash   -1855797504
     */
    virtual void appendFormattedHovertext(class ItemStackBase const &, class Level &, std::string &, bool) const;
    /**
     * @vftbl  66
     * @hash   -86663932
     */
    virtual void __unk_vfn_66();
    /**
     * @vftbl  70
     * @hash   -63575907
     */
    virtual void __unk_vfn_70();
    /**
     * @vftbl  71
     * @hash   -62652386
     */
    virtual void __unk_vfn_71();
    /**
     * @vftbl  72
     * @hash   -61728865
     */
    virtual void __unk_vfn_72();
    /**
     * @vftbl  75
     * @hash   -58958302
     */
    virtual void __unk_vfn_75();
    /**
     * @vftbl  79
     * @hash   -275840522
     */
    virtual void __unk_vfn_79();
    /**
     * @vftbl  80
     * @hash   -255523060
     */
    virtual void __unk_vfn_80();
    /**
     * @vftbl  84
     * @symbol ?use@FireworksItem@@UEBAAEAVItemStack@@AEAV2@AEAVPlayer@@@Z
     * @hash   -880284177
     */
    virtual class ItemStack & use(class ItemStack &, class Player &) const;
    /**
     * @vftbl  85
     * @symbol ?dispense@FireworksItem@@UEBA_NAEAVBlockSource@@AEAVContainer@@HAEBVVec3@@E@Z
     * @hash   -747958165
     */
    virtual bool dispense(class BlockSource &, class Container &, int, class Vec3 const &, unsigned char) const;
    /**
     * @vftbl  132
     * @symbol ?_useOn@FireworksItem@@UEBA_NAEAVItemStack@@AEAVActor@@VBlockPos@@EAEBVVec3@@@Z
     * @hash   -815866817
     */
    virtual bool _useOn(class ItemStack &, class Actor &, class BlockPos, unsigned char, class Vec3 const &) const;
    /**
     * @symbol ??0FireworksItem@@QEAA@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z
     * @hash   -674377331
     */
    MCAPI FireworksItem(std::string const &, int);
    /**
     * @symbol ?TAG_EXPLOSIONS@FireworksItem@@2V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@B
     * @hash   1703978327
     */
    MCAPI static std::string const TAG_EXPLOSIONS;
    /**
     * @symbol ?TAG_E_FLIGHT@FireworksItem@@2V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@B
     * @hash   1153884471
     */
    MCAPI static std::string const TAG_E_FLIGHT;
    /**
     * @symbol ?TAG_FIREWORKS@FireworksItem@@2V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@B
     * @hash   348152789
     */
    MCAPI static std::string const TAG_FIREWORKS;
    /**
     * @symbol ?initFireworksRocketItem@FireworksItem@@SAAEBVItemInstance@@AEAV2@AEBV?$vector@VItemInstance@@V?$allocator@VItemInstance@@@std@@@std@@H@Z
     * @hash   -768240865
     */
    MCAPI static class ItemInstance const & initFireworksRocketItem(class ItemInstance &, std::vector<class ItemInstance> const &, int);
    /**
     * @symbol ?initFireworksRocketItem@FireworksItem@@SAAEBVItemStack@@AEAV2@AEBV?$vector@VItemStack@@V?$allocator@VItemStack@@@std@@@std@@H@Z
     * @hash   1837997496
     */
    MCAPI static class ItemStack const & initFireworksRocketItem(class ItemStack &, std::vector<class ItemStack> const &, int);

};