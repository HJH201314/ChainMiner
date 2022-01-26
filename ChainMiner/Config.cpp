#include "pch.h"
#include "Config.h"

#define CONFIG_FILE "plugins/ChainMiner/config.json"

using json = nlohmann::json;

extern Logger logger;
extern std::unordered_map<string, int> chainables;
json config_j;//全局储存配置

void initConfig() {
	if (!std::filesystem::exists("plugins/ChainMiner/"))
		std::filesystem::create_directories("plugins/ChainMiner/");
	if (std::filesystem::exists(CONFIG_FILE) && !std::filesystem::is_empty(CONFIG_FILE)) {
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
		logger.debug("写出并应用默认配置...");
		writeDefaultConfig();
	}
}

#define CURRENT_CONFIG_VERSION 1

void readConfig() {
	std::ifstream configFile(CONFIG_FILE);
	if (!configFile.is_open()) {
		logger.warn("无法打开文件: " CONFIG_FILE);
		return;
	}
	configFile >> config_j;
	configFile.close();
	for (auto& el : config_j["blocks"].items()) {
		chainables[el.key()] = el.value()["maximum"];
	}
	logger.debug("载入完成!");
}

void updateConfig() {

}
#define DEFAULT_PARAMS {{"maximum",256},{"cost",1}}

void writeDefaultConfig() {
	json j = {
		{"version",CURRENT_CONFIG_VERSION},//版本
        {"command","hcm"},//指令
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
	std::ofstream configFile(CONFIG_FILE);
	if (!configFile.is_open()) {
		logger.warn("无法打开文件: " CONFIG_FILE);
		return;
	}
	configFile << j.dump(4);
	configFile.close();
    readConfig();
}