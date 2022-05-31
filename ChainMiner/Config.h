#pragma once

#ifndef CONFIG_H
#define CONFIG_H

void initConfig();
void readConfig();
void saveConfig();
void updateConfig();
void writeDefaultConfig();

nlohmann::json getDefaultConfig();

typedef struct BlockInfo_type {
    int limit;//最大值
    int cost;//每个所需
    int enchSilkTouch;//精准采集(0-不允许,1-当且仅当有精准采集魔咒,2-有无精准采集都会挖掘)
    std::vector<string> tools;//可用工具（由于数量较少，vector比set快）
    std::vector<string> similar;//同类方块
    string texture;//纹理地址(为空则自动生成)
} BlockInfo;

#endif //CONFIG_H