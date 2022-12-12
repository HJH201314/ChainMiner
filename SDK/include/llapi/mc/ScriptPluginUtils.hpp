/**
 * @file  ScriptPluginUtils.hpp
 *
 */
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Scripting.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

/**
 * @brief MC namespace ScriptPluginUtils.
 *
 */
namespace ScriptPluginUtils {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA
    /**
     * @hash   -1107786420
     * @symbol ?CreateRuntimeByType@ScriptPluginUtils@@YA?AV?$unique_ptr@VIRuntime@Scripting@@U?$default_delete@VIRuntime@Scripting@@@std@@@std@@W4ScriptRuntimeType@@AEAVLifetimeRegistry@Scripting@@PEAVDependencyLocator@6@@Z
     */
    MCAPI std::unique_ptr<class Scripting::IRuntime> CreateRuntimeByType(enum ScriptRuntimeType, class Scripting::LifetimeRegistry &, class Scripting::DependencyLocator *);
    /**
     * @hash   -832862568
     * @symbol ?GetRuntimeType@ScriptPluginUtils@@YA?AW4ScriptRuntimeType@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z
     */
    MCAPI enum ScriptRuntimeType GetRuntimeType(std::string const &);
    /**
     * @hash   -1981121244
     * @symbol ?GetRuntimeTypeFromFileExtension@ScriptPluginUtils@@YA?AW4ScriptRuntimeType@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z
     */
    MCAPI enum ScriptRuntimeType GetRuntimeTypeFromFileExtension(std::string const &);
    /**
     * @hash   -1632828223
     * @symbol ?INTERNAL_RELEASE@ScriptPluginUtils@@3V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@B
     */
    MCAPI extern std::string const INTERNAL_RELEASE;
    /**
     * @hash   753113983
     * @symbol ?JAVA_SCRIPT_RUNTIME_EXTENSION@ScriptPluginUtils@@3V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@B
     */
    MCAPI extern std::string const JAVA_SCRIPT_RUNTIME_EXTENSION;
    /**
     * @hash   -145948671
     * @symbol ?JAVA_SCRIPT_RUNTIME_NAME@ScriptPluginUtils@@3V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@B
     */
    MCAPI extern std::string const JAVA_SCRIPT_RUNTIME_NAME;
    /**
     * @hash   724422454
     * @symbol ?SanitizeRuntimeName@ScriptPluginUtils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBV23@@Z
     */
    MCAPI std::string SanitizeRuntimeName(std::string const &);

};