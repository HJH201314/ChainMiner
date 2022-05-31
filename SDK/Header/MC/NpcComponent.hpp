// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class NpcComponent {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_NPCCOMPONENT
public:
    class NpcComponent& operator=(class NpcComponent const &) = delete;
    NpcComponent(class NpcComponent const &) = delete;
#endif

public:
    /*0*/ virtual ~NpcComponent();
    /*
    inline  ~NpcComponent(){
         (NpcComponent::*rv)();
        *((void**)&rv) = dlsym("??1NpcComponent@@UEAA@XZ");
        return (this->*rv)();
    }
    */
    MCAPI NpcComponent(class NpcComponent &&);
    MCAPI NpcComponent();
    MCAPI void addAdditionalSaveData(class Actor &, class CompoundTag &) const;
    MCAPI void clearSceneStateForAllPlayers();
    MCAPI void executeCommandAction(class Actor &, class Player &, int, std::string const &);
    MCAPI struct NpcActionsContainer & getActionsContainer();
    MCAPI std::vector<int> getButtonCounts() const;
    MCAPI enum CommandPermissionLevel getCommandPermissionLevel() const;
    MCAPI bool getInteraction(class Actor &, class Player &, class ActorInteraction &);
    MCAPI std::string const & getInteractiveText(class Actor &) const;
    MCAPI std::string const & getName(class Actor const &) const;
    MCAPI std::string const & getNameRawText(class Actor const &) const;
    MCAPI int getSkinIndex() const;
    MCAPI void getUpdatedActions(std::string const &, std::vector<std::unique_ptr<class NpcAction>> &, bool &, bool &);
    MCAPI int getUrlCount() const;
    MCAPI void handleNpcRequest(class Actor &, class Player &, class NpcRequestPacket const &);
    MCAPI void initClientOnlyData(class Actor &);
    MCAPI void initFromDefinition(class Actor &);
    MCAPI void loadActions(class Actor &);
    MCAPI void loadInteractiveRawText(class Actor &);
    MCAPI void loadNPCData(class Actor &);
    MCAPI void loadNameRawText(class Actor &);
    MCAPI class NpcComponent & operator=(class NpcComponent &&);
    MCAPI void readAdditionalSaveData(class Actor &, class CompoundTag const &, class DataLoadHelper &);
    MCAPI void setActions(class Actor &, std::vector<std::unique_ptr<class NpcAction>> &&);
    MCAPI bool setDialogueScene(class Actor &, std::string const &);
    MCAPI void setInteractiveText(class Actor &, std::string const &, bool);
    MCAPI void setName(class Actor &, std::string const &, bool);
    MCAPI void setSceneStateForPlayer(class Actor &, struct ActorUniqueID const &, std::string const &);
    MCAPI void setSkin(class Actor &);
    MCAPI void setSkinIndex(class Actor &, int, bool);
    MCAPI static unsigned __int64 const MAX_NPC_NAME_LENGTH;

protected:

private:
    MCAPI void _defineEntityDataString(class Actor &, enum ActorDataIDs);
    MCAPI void _deserializeData();
    MCAPI void _loadActions(std::vector<std::unique_ptr<class NpcAction>> &, std::string const &) const;
    MCAPI std::string _serializeActions() const;
    MCAPI static std::string const ACTIONS_TAG;
    MCAPI static std::string const INTERACTIVE_TAG;
    MCAPI static std::string const NAME_RAW_TEXT_TAG;
    MCAPI static std::string const PLAYER_ID_TAG;
    MCAPI static std::string const PLAYER_SCENE_MAPPING_TAG;
    MCAPI static std::string const SCENE_NAME_TAG;
    MCAPI static std::string const URL_TAG;

};