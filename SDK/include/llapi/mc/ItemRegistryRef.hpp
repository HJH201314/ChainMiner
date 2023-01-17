/**
 * @file  ItemRegistryRef.hpp
 * @note  This Header is auto generated by LiteLoaderBDS Toolchain.
 *
 */
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA

#undef BEFORE_EXTRA

/**
 * @brief MC class ItemRegistryRef.
 *
 */
class ItemRegistryRef {

#define AFTER_EXTRA

#undef AFTER_EXTRA
#ifndef DISABLE_CONSTRUCTOR_PREVENTION_ITEMREGISTRYREF
public:
    class ItemRegistryRef& operator=(class ItemRegistryRef const &) = delete;
    ItemRegistryRef(class ItemRegistryRef const &) = delete;
    ItemRegistryRef() = delete;
#endif

public:
    /**
     * @symbol ?addItemToTagMap@ItemRegistryRef@@QEBAXAEBVItem@@@Z
     * @hash   2132317432
     */
    MCAPI void addItemToTagMap(class Item const &) const;
    /**
     * @symbol ?allowTagUpdate@ItemRegistryRef@@QEBA?AVTagUpdateToken@@XZ
     * @hash   925862774
     */
    MCAPI class TagUpdateToken allowTagUpdate() const;
    /**
     * @symbol ?alterAvailableCreativeItems@ItemRegistryRef@@QEBAXPEAVActorInfoRegistry@@AEAVLevelData@@@Z
     * @hash   -1741299138
     */
    MCAPI void alterAvailableCreativeItems(class ActorInfoRegistry *, class LevelData &) const;
    /**
     * @symbol ?canAddTags@ItemRegistryRef@@QEBA_NXZ
     * @hash   -992319654
     */
    MCAPI bool canAddTags() const;
    /**
     * @symbol ?clearItemAndCreativeItemRegistry@ItemRegistryRef@@QEBAXXZ
     * @hash   -1141215859
     */
    MCAPI void clearItemAndCreativeItemRegistry() const;
    /**
     * @symbol ?digestServerItemComponents@ItemRegistryRef@@QEBAXAEBV?$vector@U?$pair@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@VCompoundTag@@@std@@V?$allocator@U?$pair@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@VCompoundTag@@@std@@@2@@std@@@Z
     * @hash   1978392947
     */
    MCAPI void digestServerItemComponents(std::vector<struct std::pair<std::string, class CompoundTag>> const &) const;
    /**
     * @symbol ?finishedRegistration@ItemRegistryRef@@QEBAXXZ
     * @hash   1662654871
     */
    MCAPI void finishedRegistration() const;
    /**
     * @symbol ?getItem@ItemRegistryRef@@QEBA?AV?$WeakPtr@VItem@@@@AEBVHashedString@@@Z
     * @hash   -711413768
     */
    MCAPI class WeakPtr<class Item> getItem(class HashedString const &) const;
    /**
     * @symbol ?getItem@ItemRegistryRef@@QEBA?AV?$WeakPtr@VItem@@@@F@Z
     * @hash   889646875
     */
    MCAPI class WeakPtr<class Item> getItem(short) const;
    /**
     * @symbol ?getItemCount@ItemRegistryRef@@QEBAHXZ
     * @hash   -298762286
     */
    MCAPI int getItemCount() const;
    /**
     * @symbol ?getItemResponseFactory@ItemRegistryRef@@QEBAPEAVItemEventResponseFactory@@XZ
     * @hash   -246523313
     */
    MCAPI class ItemEventResponseFactory * getItemResponseFactory() const;
    /**
     * @symbol ?getNameFromLegacyID@ItemRegistryRef@@QEBA?AVHashedString@@F@Z
     * @hash   1072196332
     */
    MCAPI class HashedString getNameFromLegacyID(short) const;
    /**
     * @symbol ?initCreativeItemsServer@ItemRegistryRef@@QEBAXPEAVActorInfoRegistry@@PEAVBlockDefinitionGroup@@_NAEBVExperiments@@V?$function@$$A6AXVItemRegistryRef@@PEAVActorInfoRegistry@@PEAVBlockDefinitionGroup@@PEAVCreativeItemRegistry@@_NAEBVBaseGameVersion@@AEBVExperiments@@@Z@std@@@Z
     * @hash   1253677709
     */
    MCAPI void initCreativeItemsServer(class ActorInfoRegistry *, class BlockDefinitionGroup *, bool, class Experiments const &, class std::function<void (class ItemRegistryRef, class ActorInfoRegistry *, class BlockDefinitionGroup *, class CreativeItemRegistry *, bool, class BaseGameVersion const &, class Experiments const &)>) const;
    /**
     * @symbol ?initServerData@ItemRegistryRef@@QEBAXAEAVResourcePackManager@@AEBVExperiments@@W4ItemVersion@@@Z
     * @hash   -590621224
     */
    MCAPI void initServerData(class ResourcePackManager &, class Experiments const &, enum class ItemVersion) const;
    /**
     * @symbol ?isCreativeItem@ItemRegistryRef@@QEBA_NAEBVItemInstance@@@Z
     * @hash   1936191081
     */
    MCAPI bool isCreativeItem(class ItemInstance const &) const;
    /**
     * @symbol ?isUsingCombinedItemRegistry@ItemRegistryRef@@QEBA_NXZ
     * @hash   285528120
     */
    MCAPI bool isUsingCombinedItemRegistry() const;
    /**
     * @symbol ?lookupByName@ItemRegistryRef@@QEBA?AV?$WeakPtr@VItem@@@@AEAH0V?$basic_string_view@DU?$char_traits@D@std@@@std@@@Z
     * @hash   -1194952849
     */
    MCAPI class WeakPtr<class Item> lookupByName(int &, int &, class std::basic_string_view<char, struct std::char_traits<char>>) const;
    /**
     * @symbol ?lookupByName@ItemRegistryRef@@QEBA?AV?$WeakPtr@VItem@@@@AEAHV?$basic_string_view@DU?$char_traits@D@std@@@std@@@Z
     * @hash   1297999972
     */
    MCAPI class WeakPtr<class Item> lookupByName(int &, class std::basic_string_view<char, struct std::char_traits<char>>) const;
    /**
     * @symbol ?lookupByName@ItemRegistryRef@@QEBA?AV?$WeakPtr@VItem@@@@AEBVHashedString@@@Z
     * @hash   1707342964
     */
    MCAPI class WeakPtr<class Item> lookupByName(class HashedString const &) const;
    /**
     * @symbol ?lookupByNameNoAlias@ItemRegistryRef@@QEBA?AV?$WeakPtr@VItem@@@@AEBVHashedString@@@Z
     * @hash   1791147844
     */
    MCAPI class WeakPtr<class Item> lookupByNameNoAlias(class HashedString const &) const;
    /**
     * @symbol ?lookupByNameNoAlias@ItemRegistryRef@@QEBA?AV?$WeakPtr@VItem@@@@V?$basic_string_view@DU?$char_traits@D@std@@@std@@@Z
     * @hash   -1866553530
     */
    MCAPI class WeakPtr<class Item> lookupByNameNoAlias(class std::basic_string_view<char, struct std::char_traits<char>>) const;
    /**
     * @symbol ?lookupByNameNoParsing@ItemRegistryRef@@QEBA?AV?$WeakPtr@VItem@@@@AEAHAEBVHashedString@@@Z
     * @hash   1373640272
     */
    MCAPI class WeakPtr<class Item> lookupByNameNoParsing(int &, class HashedString const &) const;
    /**
     * @symbol ?lookupByTag@ItemRegistryRef@@QEBA?AV?$unordered_set@PEBVItem@@U?$hash@PEBVItem@@@std@@U?$equal_to@PEBVItem@@@3@V?$allocator@PEBVItem@@@3@@std@@AEBUItemTag@@@Z
     * @hash   -1367721775
     */
    MCAPI class std::unordered_set<class Item const *, struct std::hash<class Item const *>, struct std::equal_to<class Item const *>, class std::allocator<class Item const *>> lookupByTag(struct ItemTag const &) const;
    /**
     * @symbol ?lookupByVanillaName@ItemRegistryRef@@QEBA?AV?$WeakPtr@VItem@@@@AEBVHashedString@@@Z
     * @hash   -632586080
     */
    MCAPI class WeakPtr<class Item> lookupByVanillaName(class HashedString const &) const;
    /**
     * @symbol ?registerAlias@ItemRegistryRef@@QEBAXAEBVHashedString@@0AEBVBaseGameVersion@@@Z
     * @hash   -1261388930
     */
    MCAPI void registerAlias(class HashedString const &, class HashedString const &, class BaseGameVersion const &) const;
    /**
     * @symbol ?registerComplexAlias@ItemRegistryRef@@QEBA?AV?$WeakPtr@VItem@@@@AEBVHashedString@@V?$function@$$A6A?AVHashedString@@F@Z@std@@@Z
     * @hash   -1347112683
     */
    MCAPI class WeakPtr<class Item> registerComplexAlias(class HashedString const &, class std::function<class HashedString (short)>) const;
    /**
     * @symbol ?registerLegacyID@ItemRegistryRef@@QEBAXAEBVHashedString@@F@Z
     * @hash   -1130052698
     */
    MCAPI void registerLegacyID(class HashedString const &, short) const;
    /**
     * @symbol ?registerLegacyMapping@ItemRegistryRef@@QEBAXAEBVHashedString@@0AEBVBaseGameVersion@@@Z
     * @hash   -643854498
     */
    MCAPI void registerLegacyMapping(class HashedString const &, class HashedString const &, class BaseGameVersion const &) const;
    /**
     * @symbol ?setUseCombinedItemRegistryToggle@ItemRegistryRef@@QEBAX_N@Z
     * @hash   144735456
     */
    MCAPI void setUseCombinedItemRegistryToggle(bool) const;
    /**
     * @symbol ?setWorldBaseGameVersion@ItemRegistryRef@@QEBAXAEBVBaseGameVersion@@@Z
     * @hash   1394044668
     */
    MCAPI void setWorldBaseGameVersion(class BaseGameVersion const &) const;
    /**
     * @symbol ?shutdown@ItemRegistryRef@@QEBAXXZ
     * @hash   -145008755
     */
    MCAPI void shutdown() const;
    /**
     * @symbol ?startRegistration@ItemRegistryRef@@QEBAXXZ
     * @hash   -1489810583
     */
    MCAPI void startRegistration() const;
    /**
     * @symbol ?unregisterItem@ItemRegistryRef@@QEBAXAEBVHashedString@@@Z
     * @hash   -119981984
     */
    MCAPI void unregisterItem(class HashedString const &) const;
    /**
     * @symbol ?validateServerItemComponents@ItemRegistryRef@@QEBA?AV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AEBV?$vector@U?$pair@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@VCompoundTag@@@std@@V?$allocator@U?$pair@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@VCompoundTag@@@std@@@2@@3@@Z
     * @hash   -483160835
     */
    MCAPI std::vector<std::string> validateServerItemComponents(std::vector<struct std::pair<std::string, class CompoundTag>> const &) const;
    /**
     * @symbol ??1ItemRegistryRef@@QEAA@XZ
     * @hash   -1270903809
     */
    MCAPI ~ItemRegistryRef();

//private:
    /**
     * @symbol ?_lockRegistry@ItemRegistryRef@@AEBA?AV?$shared_ptr@VItemRegistry@@@std@@XZ
     * @hash   -1341004281
     */
    MCAPI class std::shared_ptr<class ItemRegistry> _lockRegistry() const;

private:
    /**
     * @symbol ?mCombinedItemRegistryInstance@ItemRegistryRef@@0V?$shared_ptr@VItemRegistry@@@std@@A
     * @hash   -267002990
     */
    MCAPI static class std::shared_ptr<class ItemRegistry> mCombinedItemRegistryInstance;

};