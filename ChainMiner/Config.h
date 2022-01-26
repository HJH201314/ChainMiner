#pragma once

#ifndef CONFIG_H
#define CONFIG_H

void initConfig();
void readConfig();
void writeDefaultConfig();

typedef struct BlockInfo_type {
    int limit;//最大值
    int cost;//每个所需
} BlockInfo;

#endif //CONFIG_H