// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "NavigationScriptActorComponent.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ScriptNavigationFlyComponent : public NavigationScriptActorComponent {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_SCRIPTNAVIGATIONFLYCOMPONENT
public:
    class ScriptNavigationFlyComponent& operator=(class ScriptNavigationFlyComponent const &) = delete;
    ScriptNavigationFlyComponent(class ScriptNavigationFlyComponent const &) = delete;
    ScriptNavigationFlyComponent() = delete;
#endif


public:
    /*0*/ virtual ~ScriptNavigationFlyComponent();
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_SCRIPTNAVIGATIONFLYCOMPONENT
#endif
    MCAPI static class Scripting::ClassBindingBuilder<class ScriptNavigationFlyComponent> bind(struct Scripting::Version);



};