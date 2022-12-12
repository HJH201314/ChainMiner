/**
 * @file  InventoryContainerValidation.hpp
 *
 */
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "ContainerValidationBase.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

/**
 * @brief MC class InventoryContainerValidation.
 *
 */
class InventoryContainerValidation : public ContainerValidationBase {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA
#ifndef DISABLE_CONSTRUCTOR_PREVENTION_INVENTORYCONTAINERVALIDATION
public:
    class InventoryContainerValidation& operator=(class InventoryContainerValidation const &) = delete;
    InventoryContainerValidation(class InventoryContainerValidation const &) = delete;
    InventoryContainerValidation() = delete;
#endif

public:
    /**
     * @vftbl  0
     * @symbol __unk_destructor_0
     */
    virtual ~InventoryContainerValidation();
    /**
     * @hash   -1433618830
     * @vftbl  1
     * @symbol ?isValidSlotForContainer@ContainerValidationBase@@UEBA_NAEBVContainerScreenContext@@AEBVContainer@@H@Z
     */
    virtual bool isValidSlotForContainer(class ContainerScreenContext const &, class Container const &, int) const;
    /**
     * @vftbl  2
     * @symbol __unk_vfn_2
     */
    virtual void __unk_vfn_2();
    /**
     * @hash   -1313350911
     * @vftbl  3
     * @symbol ?getAvailableSetCount@ContainerValidationBase@@UEBAHHAEBVItemStackBase@@@Z
     */
    virtual int getAvailableSetCount(int, class ItemStackBase const &) const;
    /**
     * @vftbl  4
     * @symbol __unk_vfn_4
     */
    virtual void __unk_vfn_4();
    /**
     * @hash   1624935976
     * @vftbl  5
     * @symbol ?isItemAllowedToRemove@InventoryContainerValidation@@UEBA_NAEBVContainerScreenContext@@AEBVItemStackBase@@@Z
     */
    virtual bool isItemAllowedToRemove(class ContainerScreenContext const &, class ItemStackBase const &) const;
    /**
     * @vftbl  6
     * @symbol __unk_vfn_6
     */
    virtual void __unk_vfn_6();
    /**
     * @hash   118077081
     * @vftbl  7
     * @symbol ?canDestroy@ContainerValidationBase@@UEBA_NAEBVContainerScreenContext@@@Z
     */
    virtual bool canDestroy(class ContainerScreenContext const &) const;
    /**
     * @hash   -1801762366
     * @vftbl  8
     * @symbol ?getContainerOffset@InventoryContainerValidation@@UEBAHAEBVContainerScreenContext@@@Z
     */
    virtual int getContainerOffset(class ContainerScreenContext const &) const;
    /**
     * @hash   1478614642
     * @vftbl  9
     * @symbol ?getContainerSize@InventoryContainerValidation@@UEBAHAEBVContainerScreenContext@@AEBVContainer@@@Z
     */
    virtual int getContainerSize(class ContainerScreenContext const &, class Container const &) const;
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_INVENTORYCONTAINERVALIDATION
    /**
     * @hash   945694869
     * @symbol ?canItemMoveToContainer@InventoryContainerValidation@@UEBA_NAEBVItemStackBase@@@Z
     */
    MCVAPI bool canItemMoveToContainer(class ItemStackBase const &) const;
#endif

};