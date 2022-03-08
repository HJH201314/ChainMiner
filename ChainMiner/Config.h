#pragma once

#ifndef CONFIG_H
#define CONFIG_H

void initConfig();
void readConfig();
void updateConfig();
void writeDefaultConfig();

nlohmann::json getDefaultConfig();

typedef struct BlockInfo_type {
    int limit;//最大值
    int cost;//每个所需
    std::vector<string> tools;//可用工具（由于数量较少，vector比set快）
} BlockInfo;

#endif //CONFIG_H