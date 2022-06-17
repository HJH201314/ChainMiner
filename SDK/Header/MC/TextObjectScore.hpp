// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Json.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class TextObjectScore {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_TEXTOBJECTSCORE
public:
    class TextObjectScore& operator=(class TextObjectScore const &) = delete;
    TextObjectScore(class TextObjectScore const &) = delete;
    TextObjectScore() = delete;
#endif


public:
    /*0*/ virtual ~TextObjectScore();
    /*1*/ virtual std::string asString() const;
    /*2*/ virtual class Json::Value asJsonValue() const;
    /*3*/ virtual class Json::Value resolve(struct ResolveData const &) const;
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_TEXTOBJECTSCORE
#endif
    MCAPI TextObjectScore(std::string, std::string);
    MCAPI static std::string const RAW_TEXT_SCORE_KEY;
    MCAPI static std::string const RAW_TEXT_SCORE_NAME_KEY;
    MCAPI static std::string const RAW_TEXT_SCORE_OBJECTIVE_KEY;
    MCAPI static std::string const RAW_TEXT_SCORE_STAR;



};