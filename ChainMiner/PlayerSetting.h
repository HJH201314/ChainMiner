#ifndef CHAINMINER_PLAYER_H
#define CHAINMINER_PLAYER_H

#include "pch.h"

class PlayerSetting {
    nlohmann::json player_j = {};
public:
    void load();
    void turnOn(const xuid_t& xuid);
    void turnOff(const xuid_t& xuid);
    bool getSwitch(const xuid_t& xuid);

private:
    void create_empty_file();
    void read_player_setting();
    void save_player_setting();
};

#endif //CHAINMINER_PLAYER_H
