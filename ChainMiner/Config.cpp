#include "pch.h"
#include "Economic.h"
#include "PlayerSetting.h"
#include "Config.h"

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

#define CURRENT_CONFIG_VERSION 7

void readConfig() {
    std::ifstream configFile(CONFIG_FILE);
    if (!configFile.is_open()) {
        logger.warn("无法打开文件: " CONFIG_FILE);
        return;
    }
    configFile >> config_j;
    configFile.close();
    //update config
    if (config_j["version"] < CURRENT_CONFIG_VERSION) {
        updateConfig();
    }
    //方块列表
    for (auto &el: config_j["blocks"].items()) {
        block_list[el.key()] = {256, 0, false};
        if (el.value().contains("limit")) {
            block_list[el.key()].limit = el.value()["limit"];
        } else logger.warn("{} in config.json doesn't have element \"limit\", Default: 256.", el.key());
        if (el.value().contains("cost")) {
            block_list[el.key()].cost = el.value()["cost"];
        } else logger.warn("{} in config.json doesn't have element \"cost\", Default: 0.", el.key());
        if (el.value().find("tools") != el.value().end()) {//工具列表
            block_list[el.key()].tools = el.value()["tools"].get<std::vector<string>>();
        }
        if (el.value().find("similar") != el.value().end()) {//同类方块
            block_list[el.key()].similar = el.value()["similar"].get<std::vector<string>>();
        }
        if (el.value().contains("SilkTouch")) {
            block_list[el.key()].enchSilkTouch = int(el.value()["SilkTouch"]);
        }
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
    logger.info("更新配置文件...");
    json json_new = getDefaultConfig();
    json_new.merge_patch(config_j);//将已有配置合并到默认配置，避免被覆盖
    json_new["version"] = CURRENT_CONFIG_VERSION;
    std::ofstream configFile(CONFIG_FILE);
    if (!configFile.is_open()) {
        logger.warn("Failed to open file: " CONFIG_FILE);
        return;
    }
    configFile << json_new.dump(4);
    //std::cout << std::setw(4) << json_new << std::endl;
    configFile.close();
    config_j.merge_patch(json_new);//最后再把配置合并回去
}

#define DEFAULT_PARAMS {"limit",256},{"cost",0}
#define DEFAULT_PARAMS_LOG {{"limit",256},{"cost",0},{"SilkTouch",2},{"tools",{"minecraft:wooden_axe","minecraft:stone_axe","minecraft:iron_axe","minecraft:diamond_axe","minecraft:golden_axe","minecraft:netherite_axe"}}}

void writeDefaultConfig() {
    json j = getDefaultConfig();
    std::ofstream configFile(CONFIG_FILE);
    if (!configFile.is_open()) {
        logger.warn("Failed to open file: " CONFIG_FILE);
        return;
    }
    configFile << j.dump(4);
    configFile.close();
    readConfig();
}

json getDefaultConfig() {
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
                    {"minecraft:log", DEFAULT_PARAMS_LOG},//原木
                    {"minecraft:log2", DEFAULT_PARAMS_LOG},//原木
                    {"minecraft:crimson_stem", DEFAULT_PARAMS_LOG},//原木
                    {"minecraft:warped_stem", DEFAULT_PARAMS_LOG},//原木
                    {"minecraft:quartz_ore", {DEFAULT_PARAMS}},//石英矿
                    {"minecraft:nether_gold_ore", {DEFAULT_PARAMS}},//下界金矿
                    {"minecraft:ancient_debris", {DEFAULT_PARAMS}},//下界残骸
                    {"minecraft:iron_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:deepslate_iron_ore"}}}},//铁矿
                    {"minecraft:gold_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:deepslate_gold_ore"}}}},//金矿
                    {"minecraft:diamond_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:deepslate_diamond_ore"}}}},//钻石矿
                    {"minecraft:lapis_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:deepslate_lapis_ore"}}}},//青金石矿
                    {"minecraft:coal_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:deepslate_coal_ore"}}}},//煤矿
                    {"minecraft:copper_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:deepslate_copper_ore"}}}},//铜矿
                    {"minecraft:emerald_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:deepslate_emerald_ore"}}}},//绿宝石矿
                    {"minecraft:lit_redstone_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:lit_deepslate_redstone_ore","minecraft:redstone_ore","minecraft:deepslate_redstone_ore"}}}},//红石矿
                    {"minecraft:lit_deepslate_redstone_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:lit_redstone_ore","minecraft:redstone_ore","minecraft:deepslate_redstone_ore"}}}},//深层红石矿
                    {"minecraft:deepslate_copper_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:copper_ore"}}}},//深层铜矿
                    {"minecraft:deepslate_iron_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:iron_ore"}}}},//深层铁矿
                    {"minecraft:deepslate_gold_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:gold_ore"}}}},//深层金矿
                    {"minecraft:deepslate_diamond_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:diamond_ore"}}}},//深层钻石矿
                    {"minecraft:deepslate_lapis_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:lapis_ore"}}}},//深层青金石矿
                    {"minecraft:deepslate_emerald_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:emerald_ore"}}}},//深层绿宝石矿
                    {"minecraft:deepslate_coal_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:coal_ore"}}}}//深层煤矿
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
    return j;
}