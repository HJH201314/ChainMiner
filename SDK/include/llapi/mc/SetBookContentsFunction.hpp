/**
 * @file  SetBookContentsFunction.hpp
 * @note  This Header is auto generated by LiteLoaderBDS Toolchain.
 *
 */
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Json.hpp"
#include "LootItemFunction.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

/**
 * @brief MC class SetBookContentsFunction.
 *
 */
class SetBookContentsFunction : public LootItemFunction {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA
#ifndef DISABLE_CONSTRUCTOR_PREVENTION_SETBOOKCONTENTSFUNCTION
public:
    class SetBookContentsFunction& operator=(class SetBookContentsFunction const &) = delete;
    SetBookContentsFunction(class SetBookContentsFunction const &) = delete;
    SetBookContentsFunction() = delete;
#endif

public:
    /**
     * @vftbl  0
     * @hash   -132851349
     */
    virtual ~SetBookContentsFunction();
    /**
     * @vftbl  1
     * @symbol ?apply@SetBookContentsFunction@@UEAAXAEAVItemStack@@AEAVRandom@@AEAVLootTableContext@@@Z
     * @hash   1947402345
     */
    virtual void apply(class ItemStack &, class Random &, class LootTableContext &);
    /**
     * @vftbl  3
     * @symbol ?apply@SetBookContentsFunction@@UEAAXAEAVItemInstance@@AEAVRandom@@AEAVLootTableContext@@@Z
     * @hash   924307390
     */
    virtual void apply(class ItemInstance &, class Random &, class LootTableContext &);
    /**
     * @symbol ??0SetBookContentsFunction@@QEAA@AEAV?$vector@V?$unique_ptr@VLootItemCondition@@U?$default_delete@VLootItemCondition@@@std@@@std@@V?$allocator@V?$unique_ptr@VLootItemCondition@@U?$default_delete@VLootItemCondition@@@std@@@std@@@2@@std@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@1AEBV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@2@@Z
     * @hash   -54446945
     */
    MCAPI SetBookContentsFunction(std::vector<std::unique_ptr<class LootItemCondition>> &, std::string const &, std::string const &, std::vector<std::string> const &);
    /**
     * @symbol ?deserialize@SetBookContentsFunction@@SA?AV?$unique_ptr@VLootItemFunction@@U?$default_delete@VLootItemFunction@@@std@@@std@@VValue@Json@@AEAV?$vector@V?$unique_ptr@VLootItemCondition@@U?$default_delete@VLootItemCondition@@@std@@@std@@V?$allocator@V?$unique_ptr@VLootItemCondition@@U?$default_delete@VLootItemCondition@@@std@@@std@@@2@@3@@Z
     * @hash   1665541183
     */
    MCAPI static std::unique_ptr<class LootItemFunction> deserialize(class Json::Value, std::vector<std::unique_ptr<class LootItemCondition>> &);

//private:
    /**
     * @symbol ?_fillUserData@SetBookContentsFunction@@AEAAXAEAVCompoundTag@@@Z
     * @hash   -1983989801
     */
    MCAPI void _fillUserData(class CompoundTag &);

private:

};