// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class CerealItemComponentFactory {

#define AFTER_EXTRA
// Add Member There
public:
struct Constructor {
    Constructor() = delete;
    Constructor(Constructor const&) = delete;
    Constructor(Constructor const&&) = delete;
};

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_CEREALITEMCOMPONENTFACTORY
public:
    class CerealItemComponentFactory& operator=(class CerealItemComponentFactory const &) = delete;
    CerealItemComponentFactory(class CerealItemComponentFactory const &) = delete;
    CerealItemComponentFactory() = delete;
#endif


public:
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_CEREALITEMCOMPONENTFACTORY
#endif
    MCAPI static class entt::meta_any constructComponent(std::string const &);
    MCAPI static class std::shared_ptr<class ItemComponent> constructItemComponent(std::string const &);
    MCAPI static class entt::meta_any getComponent(std::string const &, void *);
    MCAPI static void setItemContext(class ComponentItem *);

//private:


private:
    MCAPI static class ComponentItem * mItemContext;
    MCAPI static class std::map<std::string, struct CerealItemComponentFactory::Constructor, struct std::less<std::string>, class std::allocator<struct std::pair<std::string const, struct CerealItemComponentFactory::Constructor>>> mRegisteredComponents;


};