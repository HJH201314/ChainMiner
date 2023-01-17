/**
 * @file  HideComponent.hpp
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
 * @brief MC class HideComponent.
 *
 */
class HideComponent {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA
#ifndef DISABLE_CONSTRUCTOR_PREVENTION_HIDECOMPONENT
public:
    class HideComponent& operator=(class HideComponent const &) = delete;
    HideComponent(class HideComponent const &) = delete;
#endif

public:
    /**
     * @symbol ??0HideComponent@@QEAA@XZ
     * @hash   1533541847
     */
    MCAPI HideComponent();
    /**
     * @symbol ?addAdditionalSaveData@HideComponent@@QEBAXAEAVCompoundTag@@@Z
     * @hash   1945080552
     */
    MCAPI void addAdditionalSaveData(class CompoundTag &) const;
    /**
     * @symbol ?initFromDefinition@HideComponent@@QEAAXAEAVActor@@@Z
     * @hash   -702980958
     */
    MCAPI void initFromDefinition(class Actor &);
    /**
     * @symbol ?isInRaid@HideComponent@@QEAA_NXZ
     * @hash   280152746
     */
    MCAPI bool isInRaid();
    /**
     * @symbol ?isReactingToBell@HideComponent@@QEAA_NXZ
     * @hash   -1827608886
     */
    MCAPI bool isReactingToBell();
    /**
     * @symbol ?readAdditionalSaveData@HideComponent@@QEAAXAEBVCompoundTag@@AEAVDataLoadHelper@@@Z
     * @hash   1328610725
     */
    MCAPI void readAdditionalSaveData(class CompoundTag const &, class DataLoadHelper &);
    /**
     * @symbol ?setInRaid@HideComponent@@QEAAXXZ
     * @hash   -10471001
     */
    MCAPI void setInRaid();
    /**
     * @symbol ?setNotHiding@HideComponent@@QEAAXXZ
     * @hash   56571795
     */
    MCAPI void setNotHiding();
    /**
     * @symbol ?setReactingToBell@HideComponent@@QEAAXXZ
     * @hash   1092218155
     */
    MCAPI void setReactingToBell();

};