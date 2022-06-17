// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ContainerScreenValidatorBase {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_CONTAINERSCREENVALIDATORBASE
public:
    class ContainerScreenValidatorBase& operator=(class ContainerScreenValidatorBase const &) = delete;
    ContainerScreenValidatorBase(class ContainerScreenValidatorBase const &) = delete;
    ContainerScreenValidatorBase() = delete;
#endif


public:
    /*0*/ virtual ~ContainerScreenValidatorBase();
    /*1*/ virtual class std::shared_ptr<class ContainerValidationCommitObject> postCommitItemRemoved(enum ContainerEnumName, int, class ItemStack const &);
    /*2*/ virtual bool isCraftingImplemented();
    /*3*/ virtual struct ContainerValidationCraftResult getCraftResult(class ContainerScreenContext const &, class ContainerScreenValidation &, std::unique_ptr<struct ContainerValidationCraftInputs>);
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_CONTAINERSCREENVALIDATORBASE
#endif
    MCAPI bool isValidContainerForScreen(enum ContainerEnumName) const;



};