// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Json.hpp"
#include "Social.hpp"
#include "RakNet.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class LevelData {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_LEVELDATA
public:
    class LevelData& operator=(class LevelData const &) = delete;
    LevelData(class LevelData const &) = delete;
    LevelData() = delete;
#endif


public:
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_LEVELDATA
#endif
    MCAPI LevelData(class LevelSettings const &, std::string const &, enum GeneratorType, class BlockPos const &, bool, enum EducationEditionOffer, float, float);
    MCAPI LevelData(bool);
    MCAPI struct LevelDataValue const * _getValue(class HashedString const &) const;
    MCAPI bool achievementsWillBeDisabledOnLoad() const;
    MCAPI std::unique_ptr<class CompoundTag> createTag() const;
    MCAPI void disableAchievements();
    MCAPI bool educationFeaturesEnabled() const;
    MCAPI struct AdventureSettings const & getAdventureSettings() const;
    MCAPI struct AdventureSettings & getAdventureSettings();
    MCAPI class BaseGameVersion const & getBaseGameVersion() const;
    MCAPI std::string const getBiomeOverride() const;
    MCAPI bool getBonusChestSpawned() const;
    MCAPI enum ChatRestrictionLevel getChatRestrictionLevel() const;
    MCAPI struct Tick const & getCurrentTick() const;
    MCAPI bool getCustomSkinsDisabled() const;
    MCAPI class Abilities & getDefaultAbilities();
    MCAPI class PermissionsHandler & getDefaultPermissions();
    MCAPI class PermissionsHandler const & getDefaultPermissions() const;
    MCAPI class CompoundTag const & getEduSharedUriResource() const;
    MCAPI enum EducationEditionOffer getEducationEditionOffer() const;
    MCAPI std::string const & getEducationProductId() const;
    MCAPI class Experiments & getExperiments();
    MCAPI class Experiments const & getExperiments() const;
    MCAPI class Json::Value const & getFlatWorldGeneratorOptions() const;
    MCAPI bool getForceGameType() const;
    MCAPI enum Difficulty getGameDifficulty() const;
    MCAPI class GameRules const & getGameRules() const;
    MCAPI class GameRules & getGameRules();
    MCAPI enum GameType getGameType() const;
    MCAPI enum GeneratorType getGenerator() const;
    MCAPI bool getLANBroadcast() const;
    MCAPI bool getLANBroadcastIntent() const;
    MCAPI __int64 getLastPlayed() const;
    MCAPI std::string const & getLevelName() const;
    MCAPI float getLightningLevel() const;
    MCAPI int getLightningTime() const;
    MCAPI int getLimitedWorldDepth() const;
    MCAPI int getLimitedWorldWidth() const;
    MCAPI class CompoundTag & getLoadedPlayerTag();
    MCAPI bool getMultiplayerGameIntent() const;
    MCAPI int getNetherScale() const;
    MCAPI enum NetherWorldType getNetherType() const;
    MCAPI bool getOnlySpawnV1Villagers() const;
    MCAPI bool getPersonaDisabled() const;
    MCAPI enum Social::GamePublishSetting getPlatformBroadcastIntent() const;
    MCAPI enum Social::GamePublishSetting getPlatformBroadcastMode() const;
    MCAPI class ContentIdentity const & getPremiumTemplateContentIdentity() const;
    MCAPI float getRainLevel() const;
    MCAPI int getRainTime() const;
    MCAPI class LevelSeed64 getSeed() const;
    MCAPI unsigned int getServerChunkTickRange() const;
    MCAPI class BlockPos const & getSpawnPos() const;
    MCAPI struct SpawnSettings const & getSpawnSettings() const;
    MCAPI enum StorageVersion getStorageVersion() const;
    MCAPI enum GeneratorType getStoredGenerator() const;
    MCAPI void getTagData(class CompoundTag const &);
    MCAPI int getTime() const;
    MCAPI bool getUseMsaGamertagsOnly() const;
    MCAPI class BlockPos const & getWorldCenter() const;
    MCAPI unsigned int getWorldStartCount() const;
    MCAPI struct PackIdVersion const & getWorldTemplateIdentity() const;
    MCAPI enum WorldVersion getWorldVersion() const;
    MCAPI enum Social::GamePublishSetting getXBLBroadcastIntent() const;
    MCAPI enum Social::GamePublishSetting getXBLBroadcastMode() const;
    MCAPI bool hasAchievementsDisabled() const;
    MCAPI bool hasBonusChestEnabled() const;
    MCAPI bool hasCommandsEnabled() const;
    MCAPI bool hasConfirmedPlatformLockedContent() const;
    MCAPI bool hasLockedBehaviorPack() const;
    MCAPI bool hasLockedResourcePack() const;
    MCAPI bool hasMapsCenteredToOrigin() const;
    MCAPI bool hasStartWithMapEnabled() const;
    MCAPI void incrementTick();
    MCAPI bool isEditorWorld() const;
    MCAPI bool isEducationEditionLevel() const;
    MCAPI bool isFromLockedTemplate() const;
    MCAPI bool isFromWorldTemplate() const;
    MCAPI bool isLegacyLevel() const;
    MCAPI bool isLightning() const;
    MCAPI bool isMultiplayerGame() const;
    MCAPI bool isPremiumWorldTemplate() const;
    MCAPI bool isRaining() const;
    MCAPI bool isTexturepacksRequired() const;
    MCAPI bool isWorldTemplateOptionLocked() const;
    MCAPI class LevelData & operator=(class LevelData &&);
    MCAPI void recordStartUp();
    MCAPI void setBaseGameVersion(class BaseGameVersion const &);
    MCAPI void setBonusChestSpawned(bool);
    MCAPI void setChatRestrictionLevel(enum ChatRestrictionLevel);
    MCAPI void setCommandsEnabled(bool);
    MCAPI void setCustomSkinsDisabled(bool);
    MCAPI void setDataDrivenGenerator(enum GeneratorType);
    MCAPI void setEduSharedUriResource(struct EduSharedUriResource const &);
    MCAPI void setEducationEditionOffer(enum EducationEditionOffer);
    MCAPI void setEducationOid(std::string const &);
    MCAPI void setForceGameType(bool);
    MCAPI void setGameDifficulty(enum Difficulty);
    MCAPI void setGameType(enum GameType);
    MCAPI void setGenerator(enum GeneratorType);
    MCAPI void setHasLockedBehaviorPack(bool);
    MCAPI void setHasLockedResourcePack(bool);
    MCAPI void setLANBroadcast(bool);
    MCAPI void setLANBroadcastIntent(bool);
    MCAPI void setLevelName(std::string const &);
    MCAPI void setLightningLevel(float);
    MCAPI void setLightningTime(int);
    MCAPI void setMultiplayerGame(bool);
    MCAPI void setMultiplayerGameIntent(bool);
    MCAPI void setOnlySpawnV1Villagers(bool);
    MCAPI void setPersonaDisabled(bool);
    MCAPI void setPlatformBroadcastIntent(enum Social::GamePublishSetting);
    MCAPI void setPlatformBroadcastMode(enum Social::GamePublishSetting);
    MCAPI void setPremiumTemplateContentIdentity(class ContentIdentity const &);
    MCAPI void setRainLevel(float);
    MCAPI void setRainTime(int);
    MCAPI void setSeed(class LevelSeed64);
    MCAPI void setServerChunkTickRange(unsigned int);
    MCAPI void setSpawnPos(class BlockPos const &);
    MCAPI void setStorageVersion(enum StorageVersion);
    MCAPI void setTagData(class CompoundTag &) const;
    MCAPI void setTexturepacksRequired(bool);
    MCAPI void setTime(int);
    MCAPI void setUseMsaGamertagsOnly(bool);
    MCAPI void setWorldTemplateIdentity(struct PackIdVersion const &);
    MCAPI void setWorldTemplateOptionLocked(bool);
    MCAPI void setWorldVersion(enum WorldVersion);
    MCAPI void setXBLBroadcastIntent(enum Social::GamePublishSetting);
    MCAPI void setXBLBroadcastMode(enum Social::GamePublishSetting);
    MCAPI void touchLastLoadedWithVersion();
    MCAPI void updateLastTimePlayed() const;
    MCAPI void v1_read(class RakNet::BitStream &, enum StorageVersion);
    MCAPI ~LevelData();

//private:
    MCAPI void _determineMaxBaseGameVersion();
    MCAPI void _setGameRulesBasedOnPremiumContentIdentity();
    MCAPI void _setValue(class HashedString const &, struct LevelDataValue &&);


private:


};