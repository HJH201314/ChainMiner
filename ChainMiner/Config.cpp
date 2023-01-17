#include "pch.h"
#include "Global.h"
#include "Economic.h"
#include "Config.h"

#define CONFIG_FILE "plugins/ChainMiner/config.json"
#define DEFAULT_CONFIG 

using json = nlohmann::json;

extern Logger logger;
std::unordered_map<string, BlockInfo> block_list;

//初始化全局变量
json config_j;//全局储存配置
PlayerSetting playerSetting;
Economic economic;

vector<string> op_list;

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
            //Sleep(1000 * 100);
            exit(1);
        }
        catch (...) {
            logger.error("Config File isInvalid");
            //Sleep(1000 * 100);
            exit(1);
        }
    } else {
        logger.info("写出并应用默认配置...");
        writeDefaultConfig();
    }
}

#define CURRENT_CONFIG_VERSION 15

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
        //logger.debug("{}", 1);
        if (el.value().contains("limit")) {
            block_list[el.key()].limit = el.value()["limit"];
        } else logger.warn("{} in config.json doesn't have element \"limit\", Default: 256.", el.key());
        //logger.debug("{}", 2);
        if (el.value().contains("cost")) {
            block_list[el.key()].cost = el.value()["cost"];
        } else logger.warn("{} in config.json doesn't have element \"cost\", Default: 0.", el.key());
        //logger.debug("{}", 3);
        if (el.value().find("tools") != el.value().end()) {//工具列表
            block_list[el.key()].tools = el.value()["tools"].get<std::vector<string>>();
        }
        //logger.debug("{}", 4);
        if (el.value().find("similar") != el.value().end()) {//同类方块
            block_list[el.key()].similar = el.value()["similar"].get<std::vector<string>>();
        }
        //logger.debug("{}", 5);
        if (el.value().contains("SilkTouch")) {
            block_list[el.key()].enchSilkTouch = int(el.value()["SilkTouch"]);
        }
        //logger.debug("{}", 6);
        if (el.value().contains("texture")) {
            block_list[el.key()].texture = el.value()["texture"];
        }
        //logger.debug("{}", 7);
    }
    //money
    economic.mode = 0;
    if (config_j["money"].is_string()) {
        if (config_j["money"] == "llmoney") {
            if (economic.init()) {
                economic.mode = 1;
            }
            else {
                economic.mode = 0;
                logger.warn("未检测到LLMoney,付费连锁将会失效!");
            }
        }
        else if (config_j["money"] == "scoreboard") {
            if (config_j["money.sbname"].is_string() && config_j["money.sbname"] != "") {
                economic.mode = 2;
                economic.sbname = config_j["money.sbname"];
            }
            else {
                economic.mode = 0;
                logger.warn("未配置记分板money名称,付费连锁将会失效!");
            }
        }
    }
    //player_setting
    playerSetting.load();
    //op_list
    op_list.clear();
    for (auto& op : config_j["op"]) {
        op_list.push_back(op);
    }
}

void updateConfig() {
    logger.info("更新配置文件...");
    json json_new = getDefaultConfig();
    json_new.merge_patch(config_j);//将已有配置合并到默认配置，避免被覆盖
    if (json_new["version"] < 14) {//14以下才会更新
        json_new["money"] = "llmoney";
        json_new["money注释"] = "money: llmoney 或 scoreboard, money.sbname: 记分项名";
    }
    if (json_new["version"] < 15) {
        json_new["msg"]["mine.success注释"] = "成功采集后的消息提示,%Count% - 成功采集的方块数量";
        json_new["msg"]["money.use注释"] = "消耗金钱后的消息提示,%Cost% - 消耗金钱,%Name% - 金钱名称,%Remain% - 剩余金钱";
    }
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

//保存config_j到文件
void saveConfig() {
    std::cout << "hihihi";
    std::ofstream configFile(CONFIG_FILE);
    if (!configFile.is_open()) {
        logger.warn("Failed to open file: " CONFIG_FILE);
        return;
    }
    configFile << config_j.dump(4);
    configFile.close();
}

#define DEFAULT_PARAMS {"limit",256},{"cost",0}
#define DEFAULT_PARAMS_LOG {"limit",256},{"cost",0},{"SilkTouch",2},{"tools",{"minecraft:wooden_axe","minecraft:stone_axe","minecraft:iron_axe","minecraft:diamond_axe","minecraft:golden_axe","minecraft:netherite_axe"}}

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
            {"money", "llmoney"},//是否使用money
            {"money.name", "金币"},
            {"money.sbname", "money"},
            {"money注释", "money: llmoney 或 scoreboard, money.sbname: 记分项名"},
            {"menu.count_per_page", -1},
            {"switch", {
                    {"default", true},
                    {"chain_while_sneaking_only", true},
                    {"mine.success", true},
                    {"switch.default注释", "玩家没有进行设置时的默认开关,允许布尔true/false"}
            }},
            {"op", json::array({})},
            {"blocks注释1", "允许连锁采集的方块对应的命名空间ID,可按照样例自由添加."},
            {"blocks注释2", "cost表示每连锁采集一个该种方块消耗的金钱,limit表示连锁采集的最大数值."},
            {"blocks注释3", "最大数值几百已经很多了,调到几千玩家可以用来崩服."},
            {"blocks", {
                    {"minecraft:log", {DEFAULT_PARAMS_LOG,{"texture","textures/blocks/log_oak"}}},//原木
                    {"minecraft:log2", {DEFAULT_PARAMS_LOG,{"texture","textures/blocks/log_acacia"}}},//原木
                    {"minecraft:crimson_stem", {DEFAULT_PARAMS_LOG,{"texture","textures/blocks/huge_fungus/stripped_crimson_stem_top"}}},//原木
                    {"minecraft:warped_stem", {DEFAULT_PARAMS_LOG,{"texture","textures/blocks/huge_fungus/stripped_warped_stem_top"}}},//原木
                    {"minecraft:quartz_ore", {DEFAULT_PARAMS}},//石英矿
                    {"minecraft:nether_gold_ore", {DEFAULT_PARAMS}},//下界金矿
                    {"minecraft:ancient_debris", {DEFAULT_PARAMS,{"texture","textures/blocks/ancient_debris_top"}}},//下界残骸
                    {"minecraft:iron_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:deepslate_iron_ore"}}}},//铁矿
                    {"minecraft:gold_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:deepslate_gold_ore"}}}},//金矿
                    {"minecraft:diamond_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:deepslate_diamond_ore"}}}},//钻石矿
                    {"minecraft:lapis_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:deepslate_lapis_ore"}}}},//青金石矿
                    {"minecraft:coal_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:deepslate_coal_ore"}}}},//煤矿
                    {"minecraft:copper_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:deepslate_copper_ore"}}}},//铜矿
                    {"minecraft:emerald_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:deepslate_emerald_ore"}}}},//绿宝石矿
                    {"minecraft:lit_redstone_ore", {DEFAULT_PARAMS,{"texture","textures/blocks/redstone_ore"},{"similar",{"minecraft:lit_deepslate_redstone_ore","minecraft:redstone_ore","minecraft:deepslate_redstone_ore"}}}},//红石矿
                    {"minecraft:lit_deepslate_redstone_ore", {DEFAULT_PARAMS,{"texture","textures/blocks/deepslate/deepslate_redstone_ore"},{"similar",{"minecraft:lit_redstone_ore","minecraft:redstone_ore","minecraft:deepslate_redstone_ore"}}}},//深层红石矿
                    {"minecraft:deepslate_copper_ore", {DEFAULT_PARAMS,{"texture","textures/blocks/deepslate/deepslate_copper_ore"},{"similar",{"minecraft:copper_ore"}}}},//深层铜矿
                    {"minecraft:deepslate_iron_ore", {DEFAULT_PARAMS,{"texture","textures/blocks/deepslate/deepslate_iron_ore"},{"similar",{"minecraft:iron_ore"}}}},//深层铁矿
                    {"minecraft:deepslate_gold_ore", {DEFAULT_PARAMS,{"texture","textures/blocks/deepslate/deepslate_gold_ore"},{"similar",{"minecraft:gold_ore"}}}},//深层金矿
                    {"minecraft:deepslate_diamond_ore", {DEFAULT_PARAMS,{"texture","textures/blocks/deepslate/deepslate_diamond_ore"},{"similar",{"minecraft:diamond_ore"}}}},//深层钻石矿
                    {"minecraft:deepslate_lapis_ore", {DEFAULT_PARAMS,{"texture","textures/blocks/deepslate/deepslate_lapis_ore"},{"similar",{"minecraft:lapis_ore"}}}},//深层青金石矿
                    {"minecraft:deepslate_emerald_ore", {DEFAULT_PARAMS,{"texture","textures/blocks/deepslate/deepslate_emerald_ore"},{"similar",{"minecraft:emerald_ore"}}}},//深层绿宝石矿
                    {"minecraft:deepslate_coal_ore", {DEFAULT_PARAMS,{"texture","textures/blocks/deepslate/deepslate_coal_ore"},{"similar",{"minecraft:coal_ore"}}}}//深层煤矿
            }},
            {"msg", {
                    {"mine.success", "§a连锁采集 §e%Count% §a个方块."},
                    {"mine.success注释", "成功采集后的消息提示,%Count% - 成功采集的方块数量"},
                    {"money.use", "§b使用了 §e%Cost% §b个%Name%§c,§b剩余 §e%Remain% §b%Name%."},
                    {"money.use注释", "消耗金钱后的消息提示,%Cost% - 消耗金钱,%Name% - 金钱名称,%Remain% - 剩余金钱"},
                    {"switch.on", "§c[§6连§e锁§a采§b集§c] §a开启成功！"},
                    {"switch.on注释", "执行指令/hcm on后的提示"},
                    {"switch.off", "§c[§6连§e锁§a采§b集§c] §a关闭成功！"},
                    {"switch.off注释", "执行指令/hcm off后的提示"},
                    {"switch.block.on", "§c[§6连§e锁§a采§b集§c] §a开启 §e%Block% §a采集！"},
                    {"switch.block.on注释", "开启指定方块的连锁采集的提示"},
                    {"switch.block.off", "§c[§6连§e锁§a采§b集§c] §a关闭 §e%Block% §a采集！"},
                    {"switch.block.off注释", "关闭指定方块的连锁采集的提示"},
            }}
    };
    return j;
}