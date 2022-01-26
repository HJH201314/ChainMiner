# ChainMiner - 连锁采集

A plugin for Bedrock Dedicated Server on LiteLoaderBDS.
一个新手写的基于LiteLoaderBDS的插件

## 配置文件

### config.json

```json5
{
    //blocks为可连锁采集的方块及其参数
    //cost为每连锁一个方块消耗的金钱
    //limit为连锁采集的最大方块数量
    "blocks": {
        "minecraft:ancient_debris": {
            "cost": 0,
            "limit": 256
        },
        "minecraft:coal_ore": {
            "cost": 0,
            "limit": 256
        },
        "minecraft:copper_ore": {
            "cost": 0,
            "limit": 256
        },
        "minecraft:deepslate_coal_ore": {
            "cost": 0,
            "limit": 256
        },
        "minecraft:deepslate_copper_ore": {
            "cost": 0,
            "limit": 256
        },
        "minecraft:deepslate_diamond_ore": {
            "cost": 0,
            "limit": 256
        },
        "minecraft:deepslate_emerald_ore": {
            "cost": 0,
            "limit": 256
        },
        "minecraft:deepslate_gold_ore": {
            "cost": 0,
            "limit": 256
        },
        "minecraft:deepslate_iron_ore": {
            "cost": 0,
            "limit": 256
        },
        "minecraft:deepslate_lapis_ore": {
            "cost": 0,
            "limit": 256
        },
        "minecraft:deepslate_redstone_ore": {
            "cost": 0,
            "limit": 256
        },
        "minecraft:diamond_ore": {
            "cost": 0,
            "limit": 256
        },
        "minecraft:emerald_ore": {
            "cost": 0,
            "limit": 256
        },
        "minecraft:gold_ore": {
            "cost": 0,
            "limit": 256
        },
        "minecraft:iron_ore": {
            "cost": 0,
            "limit": 256
        },
        "minecraft:lapis_ore": {
            "cost": 0,
            "limit": 256
        },
        "minecraft:log": {
            "cost": 0,
            "limit": 256
        },
        "minecraft:nether_gold_ore": {
            "cost": 0,
            "limit": 256
        },
        "minecraft:quartz_ore": {
            "cost": 0,
            "limit": 256
        },
        "minecraft:redstone_ore": {
            "cost": 0,
            "limit": 256
        }
    },
    //command为插件的指令名,使用reload无法重载
    "command": "hcm",
    //money决定了是否对接LLMoney
    "money": true,
    //msg为插件发送给玩家的消息
    "msg": {
        "mine.success": "§a连锁采集 §e%Count% §a个方块.",
        "money.use": "§b使用了 §e%Cost% §b个金币§c,§b剩余 §e%Remain% §b金币."
    },
    //version为配置文件版本,请勿随意修改
    "version": 1
}
```

## 默认指令

`/hcm reload` - 重载部分配置

`/hcm on` - 开启连锁采集

`/hcm off` - 关闭连锁采集
