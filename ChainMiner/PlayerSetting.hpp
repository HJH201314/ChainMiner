#pragma once

#include "pch.h"
#include "Global.h"
#include "Config.h"
#include "Utils.hpp"

#define PLAYER_SETTING_FILE "plugins/ChainMiner/player.json"

using json = nlohmann::json;

extern Logger logger;

extern vector<string> op_list;

typedef string xuid_t;

class PlayerSetting {
    nlohmann::json player_j = {};
public:
    void load() {
        if (!std::filesystem::exists("plugins/ChainMiner/")) {
            std::filesystem::create_directory("plugins/ChainMiner/");
        }
        else {
            create_empty_file();//不存在或为空才创建
            read_player_setting();
            //logger.debug("{}", player_j.dump(4));
        }
    }
    void turnOn(const xuid_t &xuid, const string &nsid) {//开启指定项目
        //两种情况
        //当nsid包含minecraft:即表示某个方块时，删除该属性（因为默认为true）
        //当nsid不包含时，设置为true
        if (nsid.find("minecraft:") == 1) player_j[xuid].erase(nsid);
        else player_j[xuid][nsid] = true;
        save_player_setting();
    }
    void turnOn(const xuid_t &xuid) {
        player_j[xuid]["switch"] = true;
        save_player_setting();
    }
    void turnOff(const xuid_t &xuid, const string &nsid){//关闭指定项目
        player_j[xuid][nsid] = false;
        save_player_setting();
    }
    void turnOff(const xuid_t &xuid) {
        player_j[xuid]["switch"] = false;
        save_player_setting();
    }
    bool getSwitch(const xuid_t& xuid, const string &nsid) {//获取指定项目开关
        extern json config_j;
        if (player_j.contains(xuid) && player_j[xuid].contains(nsid)) {
            return player_j[xuid][nsid];
        }
        else if (config_j["switch"].contains(nsid)) {
            return bool(config_j["switch"][nsid]);
        }
        else {
            return true;
        }
    }
    bool getSwitch(const xuid_t &xuid) {
        extern json config_j;
        if (player_j.contains(xuid)) {
            if (player_j[xuid].contains("switch")) {
                return bool(player_j[xuid]["switch"]);
            }
            else {
                return bool(config_j["switch"]["default"]);
            }
        }
        else {
            return bool(config_j["switch"]["default"]);
        }
    }
    void setSwitch(const xuid_t& xuid, const string& nsid, const bool& value) {
        player_j[xuid][nsid] = value;
        save_player_setting();
    }
    static void setOP(const xuid_t &xuid) {
        std::cout << "0";
        extern json config_j;
        std::cout << "1";
        op_list.push_back(xuid);
        std::cout << "2";
        config_j["op"] = op_list;
        std::cout << "3";
        saveConfig();
        std::cout << "4";
    }
    static void delOP(const xuid_t& xuid) {
        extern json config_j;
        v_remove(op_list, xuid);
        config_j["op"] = op_list;
        saveConfig();
    }

private:
    void create_empty_file() {
        if (!std::filesystem::exists(PLAYER_SETTING_FILE) || std::filesystem::is_empty(PLAYER_SETTING_FILE)) {
            std::ofstream file(PLAYER_SETTING_FILE);
            if (!file.is_open()) {
                logger.warn("Failed to open file: " PLAYER_SETTING_FILE);
                return;
            }
            file << player_j.dump(4);
            file.close();
        }
    }
    void read_player_setting() {
        std::ifstream file(PLAYER_SETTING_FILE);
        if (!file.is_open()) {
            logger.warn("Failed to open file: " PLAYER_SETTING_FILE);
            return;
        }
        file >> player_j;
        file.close();
    }
    void save_player_setting() {
        std::ofstream file(PLAYER_SETTING_FILE);
        if (!file.is_open()) {
            logger.warn("Failed to open file: " PLAYER_SETTING_FILE);
            return;
        }
        file << player_j.dump(4);
        file.close();
    }
};