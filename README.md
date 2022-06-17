# # ChainMiner - 连锁采集

一个新手写的基于LiteLoaderBDS（[MineBBS](https://www.minebbs.com/liteloader/) [Github](https://github.com/LiteLDev/LiteLoaderBDS)）的插件

这个插件旨在帮助玩家更快地采集方块

由于本人是编程初学者，插件难免存在不足，恳请各位指正。

## 特性 - Feature

- 兼容耐久、时运魔咒
- 工具耐久耗尽保护
- 兼容领地插件
- 可设置指定工具触发连锁
- 允许玩家自由开关
- 仅在生存模式下可使用连锁
- 支持LLMoney（[MineBBS](https://www.minebbs.com/resources/llmoney-ll.2385/) [Github](https://github.com/LiteLDev/LiteLoaderPlugins)）、记分板经济

## 指令 - Command

- `/hcm reload`
重载部分配置（op及以上）
- `/hcm on [target]`
开启连锁采集（op及控制台可使用目标选择器target）
- `/hcm off [target]`
关闭连锁采集（op及控制台可使用目标选择器target）

## 配置文件 - Config

### `config.json` - 插件设置

- `cost` 每连锁一个该方块消耗的金钱
- `limit` 最大连锁采集数量
- `tools` 触发连锁采集必须使用的工具
  - 注意: 空字符串""表示徒手

- `similar` 可以一同连锁的同类方块
- `SilkTouch` 连锁采集（注意S和T要大写）
  - `0` 为默认值，表示附有精准采集的工具无法触发连锁（适用于矿物等）
  - `1` 表示当且仅当工具附有精准采集时才能触发连锁（适用于蓝冰等）
  - `2` 表示无论工具是否附有精准采集都能触发连锁（适用于原木等）

#### 配置文件样例

```json
{
    "command": "hcm", // plugin's command name
    "money": "llmoney", // llmoney 或 scoreboard
    "money.name": "金币", // money's name
    "msg": {
        //成功采集的提示,%Count% - 成功采集的方块数量
        "mine.success": "§a连锁采集 §e%Count% §a个方块.",
        //消耗金钱的提示,%Cost% - 消耗的金钱,%Remain% - 剩余的金钱,%Name% - 金钱名称
        "money.use": "§b使用了 §e%Cost% §b个金币§c,§b剩余 §e%Remain% §b金币.",
        //执行指令/hcm off的提示
        "switch.off": "§c[§6连§e锁§a采§b集§c] §a关闭成功！",
        //执行指令/hcm on的提示
        "switch.on": "§c[§6连§e锁§a采§b集§c] §a开启成功！"
    },
    "switch": {
        //连锁采集默认开关,true 或 false
        "default": true,
        "mine.success": true
    },
    "blocks": {
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
        //煤矿
        "minecraft:coal_ore": {
            "cost": 0,
            "limit": 256,
            "similar": [
                "minecraft:deepslate_coal_ore"
            ]
        },
        "minecraft:deepslate_coal_ore": {
            "cost": 0,
            "limit": 256,
            "similar": [
                "minecraft:coal_ore"
            ]
        },
        //红石矿(必须使用点燃的红石矿来触发)
        "minecraft:lit_redstone_ore": {
            "cost": 0,
            "limit": 256,
            "similar": [
                "minecraft:lit_deepslate_redstone_ore",
                "minecraft:redstone_ore",
                "minecraft:deepslate_redstone_ore"
            ]
        },
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

## 开源 - OpenSource

[Github](https://github.com/HJH201314/ChainMiner)
