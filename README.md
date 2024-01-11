<!--lint disable awesome-heading awesome-github awesome-toc double-link -->

<h2 align='center'>连锁采集 | ChainMiner</h2>

<p align='center'>
A plugin helps players gather blocks faster.

<!--lint ignore-->

<p align='center'>

<img src="https://img.shields.io/badge/LiteLoaderBDS-Plugin-teal?style=flat-square&color=26a69a" alt="Based On LL">
<img src="https://img.shields.io/github/license/HJH201314/openai-front?logo=dependabot&style=flat-square&color=8bc34a" alt="Github License">
<img src="https://img.shields.io/badge/Runs on-BDS-orange?logo=microsoftedge&style=flat-square&color=ffc107" alt="Runs On BDS">
<img src="https://img.shields.io/github/stars/HJH201314/ChainMiner?logo=github&style=flat-square&color=ff5722" alt="Github Repo Stars">

</p>

## 前置

- LiteLoaderBDS
- LLMoney (可选)

## 介绍

基于LiteLoaderBDS（[MineBBS](https://www.minebbs.com/liteloader/) [Github](https://github.com/LiteLDev/LiteLoaderBDS)）的插件

这个插件旨在帮助玩家更快地采集方块

## 特性

- 下蹲连锁开关
- 兼容领地插件
- 兼容假矿插件
- 仅生存模式下可用
- 工具耐久耗尽保护
- 工具耐久倍率扣除
- 允许玩家自由开关
- 支持耐久、时运魔咒
- 可设置指定工具触发连锁
- 支持LLMoney（[MineBBS](https://www.minebbs.com/resources/llmoney-ll.2385/) [Github](https://github.com/LiteLDev/LiteLoaderPlugins)）、记分板经济

## 指令

默认指令为`hcm`，可编辑`config.json`的`command`进行修改，更改后需重启服务器生效。

- `/hcm reload`
重载部分配置（op及以上）
- `/hcm on [target]`
开启连锁采集（op及控制台可使用目标选择器target）
- `/hcm off [target]`
关闭连锁采集（op及控制台可使用目标选择器target）
- `/hcm` 或 `/hcm menu`
打开连锁采集菜单
- `/hcm block`
直接打开单个方块设置菜单

## 配置

插件预设了原木和矿物的连锁，可开箱即用。

### `config.json` - 插件设置

#### `blocks` - 方块设置
- `name` 在列表中展示的方块名称
- `enabled` 是否启用该方块（默认为true）
- `cost` 每连锁一个该方块消耗的金钱
- `limit` 最大连锁采集数量
- `tools` 触发连锁采集必须使用的工具
  - 注意: 空字符串""表示徒手

- `similar` 可以一同连锁的同类方块
- `name` 方块名称（在方块开关UI中展示
- `texture` 方块材质路径（在方块开关UI中展示）
- `SilkTouch` 精准采集设置（注意S和T要大写）
  - `0` 为默认值，表示附有精准采集的工具无法触发连锁（适用于矿物等）
  - `1` 表示当且仅当工具附有精准采集时才能触发连锁（适用于蓝冰等）
  - `2` 表示无论工具是否附有精准采集都能触发连锁（适用于原木等）
- `detect_mode` 方块探测方式
  - `abut` 为默认值，仅探测被挖掘方块的相邻方块
  - `cube` 表示探测以挖掘方块为中心的3\*3\*3正方体盒子区域

#### `multiply_damage` - 耐久扣除倍率范围
形如`[1, 1]`、`[1.1, 1.2]`，左侧值≤右侧值，真正扣除的耐久为在此范围内生成的随机数乘以原本需要的耐久值并取整。

插件在执行工具耐久耗尽保护时会参考此范围的最大值，确保玩家的工具不会因为连锁采集而损坏。

### `player.json` - 玩家数据

**不建议**手动修改

## TODO
- [ ] 一键配置所有木材的连锁采集
- [ ] 使用RemoteCallAPI重写LLMoney的调用
- [x] 支持其它连锁检测方式，优化对金合欢木等的连锁
- [ ] 游戏内菜单修改插件设置（OP模块）

## Build
1. Clone this repository using `git clone`
2. Run `generate_lib.bat` and select the .pdb file of BDS to generate library
3. Open solution `ChainMiner.sln`, use `Ctrl+B` to build `ChainMiner.dll` file

### Notice
You might need to modify some attributes in the solution file for correct output path.

## Repository

[Github](https://github.com/HJH201314/ChainMiner)

## 附录

### 兼容性

[看这里](./docs/zh-CN/compatibility.md)

### 配置文件样例

```json
//本样例为方便说明添加了注释，请勿直接复制粘贴全文，否则插件无法解析。
{
    "command": "hcm", // 插件指令名
    "money": "llmoney", // llmoney 或 scoreboard
    "money.name": "金币", // 货币的名称
    //方块开关UI中每页展示的数量, -1表示全部
    "menu.count_per_page": -1,
    //耐久倍率扣除范围, 左边的值<=右边的值
    "multiply_damage": [1.1, 1.2],
    "msg": {
        //成功采集的提示, %Count% - 成功采集的方块数量
        "mine.success": "§a连锁采集 §e%Count% §a个方块.",
        //扣除耐久的提示, %Damage% - 扣除的耐久数值
        "mine.damage": "§c消耗 §6%Damage% §c点耐久.",
        //消耗金钱的提示, %Cost% - 消耗的金钱, %Remain% - 剩余的金钱, %Name% - 金钱名称
        "money.use": "§b使用了 §e%Cost% §b个金币§c,§b剩余 §e%Remain% §b金币.",
        //执行指令/hcm off的提示
        "switch.off": "§c[§6连§e锁§a采§b集§c] §a关闭成功！",
        //执行指令/hcm on的提示
        "switch.on": "§c[§6连§e锁§a采§b集§c] §a开启成功！"
    },
    "switch": {
        //连锁采集默认开关
        "default": true,
        "mine.success": true,
        "mine.damage": true,
        //潜行时采集默认开关
        "chain_while_sneaking_only": false
    },
    "blocks": {
        //橡木
        "minecraft:oak_log": {
            "cost": 0,
            "limit": 256,
            "tools": [
                "minecraft:wooden_axe",
                "minecraft:stone_axe",
                "minecraft:iron_axe",
                "minecraft:diamond_axe",
                "minecraft:golden_axe",
                "minecraft:netherite_axe"
            ]
        },
        //煤矿
        "minecraft:coal_ore": {
            "cost": 0,
            "limit": 256,
            "similar": [
                "minecraft:deepslate_coal_ore"
            ]
        },
        //深层煤矿
        "minecraft:deepslate_coal_ore": {
            "cost": 0,
            "limit": 256,
            "similar": [
                "minecraft:coal_ore"
            ]
        },
        //点燃的红石矿(必须使用点燃的红石矿来触发)
        "minecraft:lit_redstone_ore": {
            "cost": 0,
            "limit": 256,
            "similar": [
                "minecraft:lit_deepslate_redstone_ore",
                "minecraft:redstone_ore",
                "minecraft:deepslate_redstone_ore"
            ]
        },
        //点燃的深层红石矿
        "minecraft:lit_deepslate_redstone_ore": {
            "cost": 0,
            "limit": 256,
            "similar": [
                "minecraft:lit_redstone_ore",
                "minecraft:redstone_ore",
                "minecraft:deepslate_redstone_ore"
            ]
        },
        //蓝冰
        "minecraft:blue_ice": {
            "cost": 0,
            "limit": 256,
            "SilkTouch": 1
        }
    }
}
```
