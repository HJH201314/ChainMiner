# # ChainMiner - 连锁采集

A plugin for Bedrock Dedicated Server on LiteLoaderBDS.
一个新手写的基于LiteLoaderBDS（[MineBBS](https://www.minebbs.com/liteloader/) [Github](https://github.com/LiteLDev/LiteLoaderBDS)）的插件

This plugin enables players to collect blocks quicker.
这个插件旨在帮助玩家更快地采集方块

Bugs are unavoidable because I'm a beginner, please forgive me.
由于本人是编程初学者，插件难免存在不足，恳请各位指正。

## 特性 - Feature

- 兼容耐久、时运魔咒
Compatible with unbreaking and fortune
- 工具耐久耗尽保护
Tool durability depletion protection
- 兼容领地插件
Compatible with any land plugin
- 可设置指定工具触发连锁
Specified tools trigger available
- 允许玩家自由开关
Allow players to switch freely
- 仅在生存模式下可使用连锁
Available in survival mode only
- 对接LLMoney（[MineBBS](https://www.minebbs.com/resources/llmoney-ll.2385/) [Github](https://github.com/LiteLDev/LiteLoaderPlugins)）
Interfacing to LLMoney

## 指令 - Command

- `/hcm reload`
重载部分配置（op及以上）
Reload part of config.json
- `/hcm on [target]`
开启连锁采集（op及控制台可使用目标选择器target）
Enable one's ChainMiner (op can use [target])
- `/hcm off [target]`
关闭连锁采集（op及控制台可使用目标选择器target）
Disable one's ChainMiner (op can use [target])

## 配置文件 - Config

### config.json - 插件设置

cost : 每连锁一个该方块消耗的金钱
limit : 最大连锁采集数量
tools : 触发连锁采集必须使用的工具
similar : 可以一同连锁的同类方块

```json
{
    "blocks": {
        "minecraft:ancient_debris": {
            "cost": 0,
            "limit": 256
        },
        "minecraft:coal_ore": {
            "cost": 0,
            "limit": 256,
            "similar": [
                "minecraft:deepslate_coal_ore"
            ]
        },
        "minecraft:copper_ore": {
            "cost": 0,
            "limit": 256,
            "similar": [
                "minecraft:deepslate_copper_ore"
            ]
        },
        //绯红菌柄
        "minecraft:crimson_stem": {
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
        "minecraft:deepslate_coal_ore": {
            "cost": 0,
            "limit": 256,
            "similar": [
                "minecraft:coal_ore"
            ]
        },
        "minecraft:deepslate_copper_ore": {
            "cost": 0,
            "limit": 256,
            "similar": [
                "minecraft:copper_ore"
            ]
        },
        "minecraft:deepslate_diamond_ore": {
            "cost": 0,
            "limit": 256,
            "similar": [
                "minecraft:diamond_ore"
            ]
        },
        "minecraft:deepslate_emerald_ore": {
            "cost": 0,
            "limit": 256,
            "similar": [
                "minecraft:emerald_ore"
            ]
        },
        "minecraft:deepslate_gold_ore": {
            "cost": 0,
            "limit": 256,
            "similar": [
                "minecraft:gold_ore"
            ]
        },
        "minecraft:deepslate_iron_ore": {
            "cost": 0,
            "limit": 256,
            "similar": [
                "minecraft:iron_ore"
            ]
        },
        "minecraft:deepslate_lapis_ore": {
            "cost": 0,
            "limit": 256,
            "similar": [
                "minecraft:lapis_ore"
            ]
        },
        "minecraft:diamond_ore": {
            "cost": 0,
            "limit": 256,
            "similar": [
                "minecraft:deepslate_diamond_ore"
            ]
        },
        "minecraft:emerald_ore": {
            "cost": 0,
            "limit": 256,
            "similar": [
                "minecraft:deepslate_emerald_ore"
            ]
        },
        "minecraft:gold_ore": {
            "cost": 0,
            "limit": 256,
            "similar": [
                "minecraft:deepslate_gold_ore"
            ]
        },
        "minecraft:iron_ore": {
            "cost": 0,
            "limit": 256,
            "similar": [
                "minecraft:deepslate_iron_ore"
            ]
        },
        "minecraft:lapis_ore": {
            "cost": 0,
            "limit": 256,
            "similar": [
                "minecraft:deepslate_lapis_ore"
            ]
        },
        //由于红石被挖掘时一定是点燃状态,故用lit_状态作触发方块
        "minecraft:lit_deepslate_redstone_ore": {
            "cost": 0,
            "limit": 256,
            "similar": [
                "minecraft:lit_redstone_ore",
                "minecraft:redstone_ore",
                "minecraft:deepslate_redstone_ore"
            ]
        },
        "minecraft:lit_redstone_ore": {
            "cost": 0,
            "limit": 256,
            "similar": [
                "minecraft:lit_deepslate_redstone_ore",
                "minecraft:redstone_ore",
                "minecraft:deepslate_redstone_ore"
            ]
        },
        //木头（橡木、云杉、白桦、丛林木）
        "minecraft:log": {
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
        //木头（金合欢、深色橡木）
        "minecraft:log2": {
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
        "minecraft:nether_gold_ore": {
            "cost": 0,
            "limit": 256
        },
        "minecraft:quartz_ore": {
            "cost": 0,
            "limit": 256
        },
        //诡异菌柄
        "minecraft:warped_stem": {
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
        }
    },
    "blocks注释1": "允许连锁采集的方块对应的命名空间ID,可按照样例自由添加.",
    "blocks注释2": "cost表示每连锁采集一个该种方块消耗的金钱,limit表示连锁采集的最大数值.",
    "blocks注释3": "最大数值几百已经很多了,调到几千玩家可以用来崩服.",
    "command": "hcm",
    "command注释": "插件的指令名,允许文本,reload无法重载该项",
    "money": true,
    "money注释": "是否对接LLMoney,允许布尔true/false",
    "msg": {
        "mine.success": "§a连锁采集 §e%Count% §a个方块.",
        "mine.success注释": "成功采集后的消息提示,%Count%表示成功采集的方块数量",
        "money.use": "§b使用了 §e%Cost% §b个金币§c,§b剩余 §e%Remain% §b金币.",
        "money.use注释": "消耗金钱后的消息提示,%Cost%表示消耗的金钱数量,%Remain%表示剩余的金钱数量",
        "switch.off": "§c[§6连§e锁§a采§b集§c] §a关闭成功！",
        "switch.off注释": "执行指令/hcm off后的提示",
        "switch.on": "§c[§6连§e锁§a采§b集§c] §a开启成功！",
        "switch.on注释": "执行指令/hcm on后的提示"
    },
    "switch": {
        "default": true,
        "switch.default注释": "玩家没有进行设置时的默认开关,允许布尔true/false"
    },
    "version": 6
}
```

### player.json - 玩家数据

```json
{
  "{xuid}": {
    "switch": true
  }
}
```

## 开源 - OpenSource

[Github](https://github.com/HJH201314/ChainMiner)
