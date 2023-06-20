#pragma once

#ifndef CONFIG_H
#define CONFIG_H

void initConfig();
void readConfig();
void saveConfig();
void updateConfig();
void writeDefaultConfig();

nlohmann::json getDefaultConfig();

struct BlockInfo {
    int limit{ 256 };//最大值
    int cost{ 0 };//每个所需
    int enchSilkTouch{ 0 };//精准采集(0-不允许,1-当且仅当有精准采集魔咒,2-有无精准采集都会挖掘)
    std::vector<string> tools;//可用工具（由于数量较少，vector比set快）
    std::vector<string> similar;//同类方块
    string texture;//纹理地址(为空则自动生成)
    string name;//展示的名称
    bool enabled{ true };//是否启用
};

class ConfigManager {
public:
    static bool multiply_damage_switch;
    static double multiply_damage_min;
    static double multiply_damage_max;
};

#endif //CONFIG_H