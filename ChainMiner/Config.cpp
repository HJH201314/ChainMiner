#include "pch.h"
#include "Config.h"

#define CONFIG_PATH "plugins/ChainMiner/config.json"

extern Logger logger;
extern std::unordered_map<string, int> chainables;

void initConfig() {
	if (!std::filesystem::exists("plugins/ChainMiner/"))
		std::filesystem::create_directories("plugins/ChainMiner/");
	if (std::filesystem::exists("plugins/ChainMiner/config.json") && !std::filesystem::is_empty("plugins/ChainMiner/config.json")) {
		try {
			logger.debug("载入配置...");
			readConfig();
		}
		catch (std::exception& e) {
			logger.error("Config File isInvalid, Err {}", e.what());
			Sleep(1000 * 100);
			exit(1);
		}
		catch (...) {
			logger.error("Config File isInvalid");
			Sleep(1000 * 100);
			exit(1);
		}
	}
	else {
		logger.debug("写出默认配置...");
		writeDefaultConfig();
	}
}

#define CURRENT_CONFIG_VERSION 1

using json = nlohmann::json;

void readConfig() {
	std::ifstream configFile(CONFIG_PATH);
	if (!configFile.is_open()) {
		logger.warn("无法打开文件: " CONFIG_PATH);
		return;
	}
	json j;
	configFile >> j;
	configFile.close();
	for (auto& el : j["blocks"].items()) {
		chainables.insert(std::pair<string, int>{el.key(), el.value()});
	}
	logger.debug("载入完成!");
}

void updateConfig() {

}
#define DEFAULT_PARAMS {{"maximum",100},{"cost",1}}

void writeDefaultConfig() {
	json j = {
		{"version",CURRENT_CONFIG_VERSION},//版本
		{"blocks",{
			{"minecraft:log",DEFAULT_PARAMS},//原木
			{"minecraft:iron_ore",DEFAULT_PARAMS},//铁矿
			{"minecraft:gold_ore",DEFAULT_PARAMS},//金矿
			{"minecraft:diamond_ore",DEFAULT_PARAMS},//钻石矿
			{"minecraft:lapis_ore",DEFAULT_PARAMS},//青金石矿
			{"minecraft:redstone_ore",DEFAULT_PARAMS},//红石矿
			{"minecraft:coal_ore",DEFAULT_PARAMS},//煤矿
			{"minecraft:copper_ore",DEFAULT_PARAMS},//铜矿
			{"minecraft:emerald_ore",DEFAULT_PARAMS},//绿宝石矿
			{"minecraft:quartz_ore",DEFAULT_PARAMS},//石英矿
			{"minecraft:deepslate_copper_ore",DEFAULT_PARAMS},//深层铜矿
			{"minecraft:nether_gold_ore",DEFAULT_PARAMS},//下界金矿
			{"minecraft:ancient_debris",DEFAULT_PARAMS},//下界残骸
			{"minecraft:deepslate_iron_ore",DEFAULT_PARAMS},//深层铁矿
			{"minecraft:deepslate_gold_ore",DEFAULT_PARAMS},//深层金矿
			{"minecraft:deepslate_diamond_ore",DEFAULT_PARAMS},//深层钻石矿
			{"minecraft:deepslate_lapis_ore",DEFAULT_PARAMS},//深层青金石矿
			{"minecraft:deepslate_redstone_ore",DEFAULT_PARAMS},//深层红石矿
			{"minecraft:deepslate_emerald_ore",DEFAULT_PARAMS},//深层绿宝石矿
			{"minecraft:deepslate_coal_ore",DEFAULT_PARAMS}//深层煤矿
		}}
	};
	std::ofstream configFile("plugins/ChainMiner/config.json");
	if (!configFile.is_open()) {
		logger.warn("无法打开文件: " CONFIG_PATH);
		return;
	}
	configFile << j.dump(4);
	configFile.close();
}