// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class DateManager {

#define AFTER_EXTRA
// Add Member There
public:
enum TimeZoneType;

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_DATEMANAGER
public:
    class DateManager& operator=(class DateManager const &) = delete;
    DateManager(class DateManager const &) = delete;
    DateManager() = delete;
#endif


public:
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_DATEMANAGER
#endif
    MCAPI static std::string getCurrentTimestampFileName();
    MCAPI static __int64 getRealTime();
    MCAPI static struct tm toDateTime(__int64, enum DateManager::TimeZoneType);
    MCAPI static std::string toString(struct tm const &, std::string const &);
    MCAPI static std::string toString(__int64 const &, enum DateManager::TimeZoneType, std::string const &);
    MCAPI static std::string toString_DateTime(struct tm const &, enum DateManager::TimeZoneType);
    MCAPI static std::string toString_DateTime(__int64 const &, enum DateManager::TimeZoneType);



};