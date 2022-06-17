// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Json.hpp"
#include "CommandOrigin.hpp"

#define BEFORE_EXTRA

#undef BEFORE_EXTRA

class ExecuteContextCommandOrigin : public CommandOrigin {

#define AFTER_EXTRA

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_EXECUTECONTEXTCOMMANDORIGIN
public:
    class ExecuteContextCommandOrigin& operator=(class ExecuteContextCommandOrigin const &) = delete;
    ExecuteContextCommandOrigin(class ExecuteContextCommandOrigin const &) = delete;
    ExecuteContextCommandOrigin() = delete;
#endif


public:
    /*0*/ virtual ~ExecuteContextCommandOrigin();
    /*1*/ virtual std::string const & getRequestId() const;
    /*2*/ virtual std::string getName() const;
    /*3*/ virtual class BlockPos getBlockPosition() const;
    /*4*/ virtual class Vec3 getWorldPosition() const;
    /*5*/ virtual class std::optional<class Vec2> getRotation() const;
    /*6*/ virtual class Level * getLevel() const;
    /*7*/ virtual class Dimension * getDimension() const;
    /*8*/ virtual class Actor * getEntity() const;
    /*9*/ virtual enum CommandPermissionLevel getPermissionsLevel() const;
    /*10*/ virtual std::unique_ptr<class CommandOrigin> clone() const;
    /*23*/ virtual enum CommandOriginType getOriginType() const;
    /*27*/ virtual void updateValues();
    /*28*/ virtual class Vec3 const getExecutePosition(int, class CommandPositionFloat const &) const;
    /*29*/ virtual class CompoundTag serialize() const;
    /*30*/ virtual bool isValid() const;
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_EXECUTECONTEXTCOMMANDORIGIN
#endif
    MCAPI ExecuteContextCommandOrigin(struct ActorUniqueID, class Vec3 const &, class std::optional<class Vec2> const &, struct ActorUniqueID, struct ActorUniqueID, enum ActorLocation, class AutomaticID<class Dimension, int>, class Level &);
    MCAPI void setDimension(class Dimension &);
    MCAPI void setExecutionEntity(class Actor const &);
    MCAPI void setPosition(class Vec3 const &);
    MCAPI void setPositionEntity(class Actor const &);
    MCAPI void setRotationEntity(class Actor const &);
    MCAPI static std::unique_ptr<class ExecuteContextCommandOrigin> load(class CompoundTag const &, class ServerLevel &);



};