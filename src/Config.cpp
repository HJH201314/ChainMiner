#include "pch.h"
#include "Global.h"
#include "Economic.h"
#include "Config.h"

#define CONFIG_FILE "plugins/ChainMiner/config.json"

using json = nlohmann::json;

extern Logger logger;
std::unordered_map<string, BlockInfo> block_list;

//初始化全局变量
json config_j;//全局储存配置
PlayerSetting playerSetting;
Economic economic;

vector<string> op_list;

//初始化
bool ConfigManager::multiply_damage_switch = false;
double ConfigManager::multiply_damage_min = 1;
double ConfigManager::multiply_damage_max = 1;

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

#define CURRENT_CONFIG_VERSION 23

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
        if (el.value().contains("texture")) {
            block_list[el.key()].texture = el.value()["texture"];
        }
        if (el.value().contains("name")) {
            block_list[el.key()].name = el.value()["name"];
        }
        if (el.value().contains("enabled")) {
            block_list[el.key()].enabled = el.value()["enabled"];
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
    //ConfigManager
    //logger.debug("{} {}", config_j["multiply_damage"][0].is_number(), (double)config_j["multiply_damage"][0]);
    if (config_j["multiply_damage"].size() == 2 && config_j["multiply_damage"][0].is_number() && config_j["multiply_damage"][1].is_number()) {
        if (config_j["multiply_damage"][0] <= config_j["multiply_damage"][1]) {
            ConfigManager::multiply_damage_switch = true;
            ConfigManager::multiply_damage_min = config_j["multiply_damage"][0];
            ConfigManager::multiply_damage_max = config_j["multiply_damage"][1];
        }
        else {
            logger.warn("multiply_damage配置异常!");
        }
    }
}

void updateConfig() {
    logger.info("更新配置文件...");
    json json_new = getDefaultConfig();
    json_new.merge_patch(config_j);//将已有配置合并到默认配置，避免被覆盖
    if (config_j["version"] < 20) {
        // 复制旧版配置文件
        std::filesystem::path original_path = "plugins/ChainMiner/config.json";
        std::filesystem::path destination_path = "plugins/ChainMiner/config.json.v19";
        try {
            std::filesystem::copy_file(original_path, destination_path,
                std::filesystem::copy_options::overwrite_existing);
            logger.info("备份旧版配置文件至 plugins/ChainMiner/config.json.v19");
        }
        catch (const std::filesystem::filesystem_error& e) {
            std::cout << "Error copying file: " << e.what() << std::endl;
            logger.warn("备份旧版配置文件失败");
        }
        json_new = getDefaultConfig();
        config_j = json_new;
    }
    if (config_j["version"] < 22) { // 解决深色橡木的texture错误
        if (json_new.contains("blocks") && json_new["blocks"].contains("minecraft:dark_oak_log")) {
            json_new["blocks"]["minecraft:dark_oak_log"]["texture"] = "textures/blocks/log_big_oak_top";
        }
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
            {"default_detect_method", "block"},
            {"switch", {
                    {"default", true},
                    {"chain_while_sneaking_only", false},
                    {"mine.success", true},
                    {"mine.damage", true},
                    {"switch.default注释", "玩家没有进行设置时的默认开关,允许布尔true/false"}
            }},
            {"multiply_damage", json::array({1,1})},
            {"op", json::array({})},
            {"blocks注释1", "允许连锁采集的方块对应的命名空间ID,可按照样例自由添加."},
            {"blocks注释2", "cost表示每连锁采集一个该种方块消耗的金钱,limit表示连锁采集的最大数值."},
            {"blocks", {
                    // {"minecraft:log", {DEFAULT_PARAMS_LOG,{"texture","textures/blocks/log_oak_top"},{"name","橡木/云杉木/白桦木/丛林木"}}},//木头（橡木、云杉木、白桦木、丛林木）
                    // {"minecraft:log2", {DEFAULT_PARAMS_LOG,{"texture","textures/blocks/log_acacia_top"},{"name","金合欢木/深色橡木"}}},//木头（金合欢木、深色橡木）
                    {"minecraft:oak_log", {DEFAULT_PARAMS_LOG,{"texture","textures/blocks/log_oak_top"},{"name","橡木原木"}}},//橡木原木
                    {"minecraft:spruce_log", {DEFAULT_PARAMS_LOG,{"texture","textures/blocks/log_spruce_top"},{"name","云杉木原木"}}},//云杉木原木
                    {"minecraft:birch_log", {DEFAULT_PARAMS_LOG,{"texture","textures/blocks/log_birch_top"},{"name","白桦木原木"}}},//白桦木原木
                    {"minecraft:jungle_log", {DEFAULT_PARAMS_LOG,{"texture","textures/blocks/log_jungle_top"},{"name","云杉木原木"}}},//云杉木原木
                    {"minecraft:acacia_log", {DEFAULT_PARAMS_LOG,{"texture","textures/blocks/log_acacia_top"},{"name","金合欢木原木"}}},//金合欢木原木
                    {"minecraft:dark_oak_log", {DEFAULT_PARAMS_LOG,{"texture","textures/blocks/log_big_oak_top"},{"name","深色橡木原木"}}},//深色橡木原木
                    {"minecraft:mangrove_log", {DEFAULT_PARAMS_LOG,{"texture","textures/blocks/mangrove_log_top"},{"name","红树原木"}}},//红树原木
                    {"minecraft:cherry_log", {DEFAULT_PARAMS_LOG,{"texture","textures/blocks/cherry_log_top"},{"name","樱花原木"}}},//红树原木
                    {"minecraft:crimson_stem", {DEFAULT_PARAMS_LOG,{"texture","textures/blocks/huge_fungus/stripped_crimson_stem_top"},{"name","绯红菌柄"}}},//绯红菌柄
                    {"minecraft:warped_stem", {DEFAULT_PARAMS_LOG,{"texture","textures/blocks/huge_fungus/stripped_warped_stem_top"},{"name","诡异菌柄"}}},//诡异菌柄
                    {"minecraft:quartz_ore", {DEFAULT_PARAMS,{"name","下界石英矿石"}}},//石英矿
                    {"minecraft:nether_gold_ore", {DEFAULT_PARAMS,{"name","下界金矿石"}}},//下界金矿
                    {"minecraft:ancient_debris", {DEFAULT_PARAMS,{"texture","textures/blocks/ancient_debris_top"},{"name","远古残骸"}}},//远古残骸
                    {"minecraft:iron_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:deepslate_iron_ore"}},{"name","铁矿石"}}},//铁矿
                    {"minecraft:gold_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:deepslate_gold_ore"}},{"name","金矿石"}}},//金矿
                    {"minecraft:diamond_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:deepslate_diamond_ore"}},{"name","钻石矿石"}}},//钻石矿
                    {"minecraft:lapis_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:deepslate_lapis_ore"}},{"name","青金石矿石"}}},//青金石矿
                    {"minecraft:coal_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:deepslate_coal_ore"}},{"name","煤矿石"}}},//煤矿
                    {"minecraft:copper_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:deepslate_copper_ore"}},{"name","铜矿石"}}},//铜矿
                    {"minecraft:emerald_ore", {DEFAULT_PARAMS,{"similar",{"minecraft:deepslate_emerald_ore"}},{"name","绿宝石矿石"}}},//绿宝石矿
                    {"minecraft:lit_redstone_ore", {DEFAULT_PARAMS,{"texture","textures/blocks/redstone_ore"},{"similar",{"minecraft:lit_deepslate_redstone_ore","minecraft:redstone_ore","minecraft:deepslate_redstone_ore"}},{"name","红石矿石"}}},//红石矿
                    {"minecraft:lit_deepslate_redstone_ore", {DEFAULT_PARAMS,{"texture","textures/blocks/deepslate/deepslate_redstone_ore"},{"similar",{"minecraft:lit_redstone_ore","minecraft:redstone_ore","minecraft:deepslate_redstone_ore"}},{"name","深层红石矿石"}}},//深层红石矿
                    {"minecraft:deepslate_copper_ore", {DEFAULT_PARAMS,{"texture","textures/blocks/deepslate/deepslate_copper_ore"},{"similar",{"minecraft:copper_ore"}},{"name","深层铜矿石"}}},//深层铜矿
                    {"minecraft:deepslate_iron_ore", {DEFAULT_PARAMS,{"texture","textures/blocks/deepslate/deepslate_iron_ore"},{"similar",{"minecraft:iron_ore"}},{"name","深层铁矿石"}}},//深层铁矿
                    {"minecraft:deepslate_gold_ore", {DEFAULT_PARAMS,{"texture","textures/blocks/deepslate/deepslate_gold_ore"},{"similar",{"minecraft:gold_ore"}},{"name","深层金矿石"}}},//深层金矿
                    {"minecraft:deepslate_diamond_ore", {DEFAULT_PARAMS,{"texture","textures/blocks/deepslate/deepslate_diamond_ore"},{"similar",{"minecraft:diamond_ore"}},{"name","深层钻石矿石"}}},//深层钻石矿
                    {"minecraft:deepslate_lapis_ore", {DEFAULT_PARAMS,{"texture","textures/blocks/deepslate/deepslate_lapis_ore"},{"similar",{"minecraft:lapis_ore"}},{"name","深层青金石矿石"}}},//深层青金石矿
                    {"minecraft:deepslate_emerald_ore", {DEFAULT_PARAMS,{"texture","textures/blocks/deepslate/deepslate_emerald_ore"},{"similar",{"minecraft:emerald_ore"}},{"name","深层绿宝石矿石"}}},//深层绿宝石矿
                    {"minecraft:deepslate_coal_ore", {DEFAULT_PARAMS,{"texture","textures/blocks/deepslate/deepslate_coal_ore"},{"similar",{"minecraft:coal_ore"}},{"name","深层煤矿石"}}}//深层煤矿
            }},
            {"msg", {
                    {"mine.success", "§a连锁采集 §e%Count% §a个方块."},
                    {"mine.success注释", "成功采集后的消息提示, %Count% - 成功采集的方块数量"},
                    {"mine.damage", "§c消耗 §6%Damage% §c点耐久."},
                    {"mine.damage注释", "成狗采集后的耐久消耗提示, %Damage% - 消耗的耐久"},
                    {"money.use", "§b使用了 §e%Cost% §b个%Name%§c, §b剩余 §e%Remain% §b%Name%."},
                    {"money.use注释", "消耗金钱后的消息提示, %Cost% - 消耗金钱, %Name% - 金钱名称, %Remain% - 剩余金钱"},
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