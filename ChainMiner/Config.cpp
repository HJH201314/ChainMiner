#include "pch.h"
#include "Config.h"
#include "Economic.h"
#include "PlayerSetting.h"

#define CONFIG_FILE "plugins/ChainMiner/config.json"
#define DEFAULT_CONFIG 

using json = nlohmann::json;

extern Logger logger;
std::unordered_map<string, BlockInfo> block_list;
json config_j;//全局储存配置
bool useMoney = true;
PlayerSetting playerSetting;

void initConfig() {
    if (!std::filesystem::exists("plugins/ChainMiner/"))
        std::filesystem::create_directories("plugins/ChainMiner/");
    if (std::filesystem::exists(CONFIG_FILE) && !std::filesystem::is_empty(CONFIG_FILE)) {
        try {
            logger.info("载入配置...");
            readConfig();
            logger.info("载入完成!");
        }
        catch (std::exception &e) {
            logger.error("Config File isInvalid, Err {}", e.what());
            Sleep(1000 * 100);
            exit(1);
        }
        catch (...) {
            logger.error("Config File isInvalid");
            Sleep(1000 * 100);
            exit(1);
        }
    } else {
        logger.info("写出并应用默认配置...");
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
    //方块列表
    for (auto &el: config_j["blocks"].items()) {
        block_list[el.key()] = {el.value()["limit"], el.value()["cost"]};
    }
    //money
    if (!config_j["money"]) {
        useMoney = false;
    } else {
        if(Economic::init()) {
            useMoney = true;
        } else {
            useMoney = false;
            logger.info("未检测到LLMoney,付费连锁将会失效!");
        }
    }
    //player_setting
    playerSetting.load();
}

void updateConfig() {

}

#define DEFAULT_PARAMS {{"limit",256},{"cost",0}}

void writeDefaultConfig() {
    json j = {
            {"version", CURRENT_CONFIG_VERSION},//版本
            {"command", "hcm"},//指令
            {"command注释", "插件的指令名,允许文本,reload无法重载该项"},
            {"money", true},//是否使用money
            {"money注释", "是否对接LLMoney,允许布尔true/false"},
            {"switch", {
                    {"default", true},
                    {"switch.default注释", "玩家没有进行设置时的默认开关,允许布尔true/false"}
            }},
            {"blocks注释1", "允许连锁采集的方块对应的命名空间ID,可按照样例自由添加."},
            {"blocks注释2", "cost表示每连锁采集一个该种方块消耗的金钱,limit表示连锁采集的最大数值."},
            {"blocks注释3", "最大数值几百已经很多了,调到几千玩家可以用来崩服."},
            {"blocks", {
                    {"minecraft:log", DEFAULT_PARAMS},//原木
                    {"minecraft:log2", DEFAULT_PARAMS},//原木
                    {"minecraft:crimson_stem", DEFAULT_PARAMS},//原木
                    {"minecraft:warped_stem", DEFAULT_PARAMS},//原木
                    {"minecraft:iron_ore", DEFAULT_PARAMS},//铁矿
                    {"minecraft:gold_ore", DEFAULT_PARAMS},//金矿
                    {"minecraft:diamond_ore", DEFAULT_PARAMS},//钻石矿
                    {"minecraft:lapis_ore", DEFAULT_PARAMS},//青金石矿
                    {"minecraft:redstone_ore", DEFAULT_PARAMS},//红石矿
                    {"minecraft:coal_ore", DEFAULT_PARAMS},//煤矿
                    {"minecraft:copper_ore", DEFAULT_PARAMS},//铜矿
                    {"minecraft:emerald_ore", DEFAULT_PARAMS},//绿宝石矿
                    {"minecraft:quartz_ore", DEFAULT_PARAMS},//石英矿
                    {"minecraft:deepslate_copper_ore", DEFAULT_PARAMS},//深层铜矿
                    {"minecraft:nether_gold_ore", DEFAULT_PARAMS},//下界金矿
                    {"minecraft:ancient_debris", DEFAULT_PARAMS},//下界残骸
                    {"minecraft:deepslate_iron_ore", DEFAULT_PARAMS},//深层铁矿
                    {"minecraft:deepslate_gold_ore", DEFAULT_PARAMS},//深层金矿
                    {"minecraft:deepslate_diamond_ore", DEFAULT_PARAMS},//深层钻石矿
                    {"minecraft:deepslate_lapis_ore", DEFAULT_PARAMS},//深层青金石矿
                    {"minecraft:deepslate_redstone_ore", DEFAULT_PARAMS},//深层红石矿
                    {"minecraft:deepslate_emerald_ore", DEFAULT_PARAMS},//深层绿宝石矿
                    {"minecraft:deepslate_coal_ore", DEFAULT_PARAMS}//深层煤矿
            }},
            {"msg", {
                    {"mine.success", "§a连锁采集 §e%Count% §a个方块."},
                    {"mine.success注释", "成功采集后的消息提示,%Count%表示成功采集的方块数量"},
                    {"money.use", "§b使用了 §e%Cost% §b个金币§c,§b剩余 §e%Remain% §b金币."},
                    {"money.use注释", "消耗金钱后的消息提示,%Cost%表示消耗的金钱数量,%Remain%表示剩余的金钱数量"},
                    {"switch.on", "§c[§6连§e锁§a采§b集§c] §a开启成功！"},
                    {"switch.on注释", "执行指令/hcm on后的提示"},
                    {"switch.off", "§c[§6连§e锁§a采§b集§c] §a关闭成功！"},
                    {"switch.off注释", "执行指令/hcm off后的提示"},
            }}
    };
    std::ofstream configFile(CONFIG_FILE);
    if (!configFile.is_open()) {
        logger.warn("Failed to open file: " CONFIG_FILE);
        return;
    }
    configFile << j.dump(4);
    configFile.close();
    readConfig();
}