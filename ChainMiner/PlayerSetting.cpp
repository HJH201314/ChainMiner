#include "pch.h"
#include "PlayerSetting.h"

#define PLAYER_SETTING_FILE "plugins/ChainMiner/player.json"

using json = nlohmann::json;

extern Logger logger;

typedef string xuid_t;

void PlayerSetting::load() {
    if(!std::filesystem::exists("plugins/ChainMiner/")) {
        std::filesystem::create_directory("plugins/ChainMiner/");
    } else {
        create_empty_file();//不存在或为空才创建
        read_player_setting();
    }
}

void PlayerSetting::turnOn(const xuid_t& xuid) {
    player_j[xuid]["switch"] = true;
    save_player_setting();
}

void PlayerSetting::turnOff(const xuid_t& xuid) {
    player_j[xuid]["switch"] = false;
    save_player_setting();
}

bool PlayerSetting::getSwitch(const xuid_t& xuid) {
    extern json config_j;
    if(player_j.contains(xuid)) {
        if(player_j[xuid].contains("switch")) {
            return bool(player_j[xuid]["switch"]);
        } else {
            return bool(config_j["switch"]["default"]);
        }
    } else {
        return config_j["switch"]["default"];
    }
}

void PlayerSetting::create_empty_file() {
    if(!std::filesystem::exists(PLAYER_SETTING_FILE) || std::filesystem::is_empty(PLAYER_SETTING_FILE)) {
        std::ofstream file(PLAYER_SETTING_FILE);
        if (!file.is_open()) {
            logger.warn("Failed to open file: " PLAYER_SETTING_FILE);
            return;
        }
        file << player_j.dump(4);
        file.close();
    }
}

void PlayerSetting::read_player_setting() {
    std::ifstream file(PLAYER_SETTING_FILE);
    if(!file.is_open()) {
        logger.warn("Failed to open file: " PLAYER_SETTING_FILE);
        return;
    }
    file >> player_j;
    file.close();
}

void PlayerSetting::save_player_setting() {
    std::ofstream file(PLAYER_SETTING_FILE);
    if (!file.is_open()) {
        logger.warn("Failed to open file: " PLAYER_SETTING_FILE);
        return;
    }
    file << player_j.dump(4);
    file.close();
}