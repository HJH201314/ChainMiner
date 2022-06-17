// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class SavedDataStorage {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_SAVEDDATASTORAGE
public:
    class SavedDataStorage& operator=(class SavedDataStorage const &) = delete;
    SavedDataStorage(class SavedDataStorage const &) = delete;
    SavedDataStorage() = delete;
#endif


public:
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_SAVEDDATASTORAGE
#endif
    MCAPI SavedDataStorage(class LevelStorage *);
    MCAPI bool loadAndSet(class SavedData &, std::string const &);
    MCAPI void save();
    MCAPI void set(std::string const &, class SavedData &);

//private:
    MCAPI void _save(class SavedData const &);


private:


};