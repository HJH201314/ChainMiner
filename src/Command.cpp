#include "pch.h"
#include "Utils.hpp"
#include "Global.h"
#include "Config.h"
#include "Plugin.h"
#include <llapi/RegCommandAPI.h>
#include <llapi/mc/ItemStack.hpp>
#include <llapi/mc/CompoundTag.hpp>
#include <llapi/mc/Player.hpp>
#include <FMT/core.h>

extern nlohmann::json config_j;


//ChainMiner指令类
class ChainMinerCommand : public Command {
private:
    enum CMOP : int {
        reload = 1,
        help = 2,
        op = 100,
        deop = 101,
        ban = 102,
        forgive = 103,
        edit = 301,
        on = 200,
        off = 201,
        menu = 500,
        block = 501,
        test = 999,
        damage = 1000
	} opn;
    CommandSelector<Player> player;
    bool player_isSet;
    int int_val;
    bool int_val_isSet;
public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const {
		switch (opn) {
            case CMOP::reload: {
                if(ori.getPermissionsLevel() >= CommandPermissionLevel::Admin) {
                    readConfig();
                    outp.success("§e重载成功!");
                }
                return;
            }
            case CMOP::help: {
                outp.success("Not finished yet.");
                return;
            }
            case CMOP::on: {
                Player* pl = getPlayerFromOrigin(ori);
                if (player_isSet) {//选择器
                    for (auto el : player.results(ori))
                        if (el->isPlayer())
                            if (ori.getPermissionsLevel() >= CommandPermissionLevel::Admin || pl->getXuid() == el->getXuid())
                                playerSetting.turnOn(el->getXuid());
                    outp.success(config_j["msg"]["switch.on"]);
                }
                else if (pl) {
                    playerSetting.turnOn(pl->getXuid());
                    pl->sendTextPacket(config_j["msg"]["switch.on"]);
                }
                else {
                    outp.error("Do not use this in console.");
                }
                return;
            }
            case CMOP::off: {
                Player* pl = getPlayerFromOrigin(ori);
                if (player_isSet) {//选择器
                    for (auto el : player.results(ori))
                        if (el->isPlayer())
                            if (ori.getPermissionsLevel() >= CommandPermissionLevel::Admin || pl->getXuid() == el->getXuid())
                                playerSetting.turnOff(el->getXuid());
                    outp.success(config_j["msg"]["switch.off"]);
                }
                else if (pl) {
                    playerSetting.turnOff(pl->getXuid());
                    pl->sendTextPacket(config_j["msg"]["switch.off"]);
                }
                else {
                    outp.error("Do not use this in console.");
                }
                return;
            }
            extern vector<string> op_list;
            case CMOP::op: {
                //OP3是必须输入目标选择的
                if (ori.getPermissionsLevel() >= CommandPermissionLevel::Console) {
                    for (auto el : player.results(ori))
                        if (el->isPlayer())
                            if (!v_contains(op_list, el->getXuid())) {
                                playerSetting.setOP(el->getXuid());
                                outp.success("成功添加<"+el->getName()+">为连锁采集管理.");
                            }
                            else {
                                outp.success("<" + el->getName() + ">已经是连锁采集管理.");
                            }
                }
                else {
                    outp.error("Permission Denied.");
                }
                return;
            }
            case CMOP::deop: {
                //OP3是必须输入目标选择的
                if (ori.getPermissionsLevel() >= CommandPermissionLevel::Console) {
                    for (auto el : player.results(ori))
                        if (el->isPlayer())
                            if (v_contains(op_list, el->getXuid())) {
                                playerSetting.delOP(el->getXuid());
                                outp.success("成功移除<" + el->getName() + ">的连锁采集管理.");
                            }
                            else {
                                outp.success("<" + el->getName() + ">不是连锁采集管理.");
                            }
                }
                else {
                    outp.error("Permission Denied.");
                }
                return;
            }
            case CMOP::ban: {

                return;
            }
            case CMOP::forgive: {

                return;
            }
            case 0:
            case menu: {
                Player* pl = getPlayerFromOrigin(ori);
                if (pl->isPlayer()) {
                    sendPlayerMenu(pl);
                }
                else {
                    outp.error("Please use in game.");
                }
                return;
            }
            case CMOP::block: {
                Player* pl = getPlayerFromOrigin(ori);
                if (pl->isPlayer()) {
                    sendBlockSwitchMenu(pl);
                }
                else {
                    outp.error("Please use in game.");
                }
                return;
            }
            case CMOP::edit: {
                return;
            }
            case CMOP::test: {
                if (ori.getPermissionsLevel() >= CommandPermissionLevel::Admin) {
                    outp.success(fmt::format("{} {}", countTaskList()/*, countPos2Id()*/, countChainingBlocks()));
                }
                return;
            }
            case CMOP::damage: {
                auto pl = ori.getPlayer();
                if (pl && int_val_isSet) {
                    ItemStack item = pl->getSelectedItem();
#include "Plugin.h"
                    toolDamage(item, int_val);
                    pl->setSelectedItem(item);
                    pl->refreshInventory();
                }
            }
		default:
			break;
		}
	}
	static void setup(CommandRegistry* registry) {
		using RegisterCommandHelper::makeMandatory;
		using RegisterCommandHelper::makeOptional;
		registry->registerCommand(config_j["command"],
                                  "ChainMiner连锁采集",
                                  CommandPermissionLevel::Any,
                                  { (CommandFlagValue)0 }, { (CommandFlagValue)0x80 });
        //0 param, open menu
        registry->registerOverload<ChainMinerCommand>(config_j["command"]);
        //1 param, operator
		registry->addEnum<CMOP>("OP1",
            { {"reload", CMOP::reload}, {"test", CMOP::test}, {"menu", CMOP::block}, {"block", CMOP::block}, {"edit", CMOP::edit}, {"help", CMOP::help}});
		registry->registerOverload<ChainMinerCommand>(
                config_j["command"],
                makeMandatory<CommandParameterDataType::ENUM>(&ChainMinerCommand::opn, "optional","OP1"));
        //1-2 params, operator (& player)
        registry->addEnum<CMOP>("OP2",
                                { {"on", CMOP::on},
                                  {"off", CMOP::off} });
        registry->registerOverload<ChainMinerCommand>(
                config_j["command"],
                makeMandatory<CommandParameterDataType::ENUM>(&ChainMinerCommand::opn, "optional","OP2"),
                makeOptional(&ChainMinerCommand::player,"player",&ChainMinerCommand::player_isSet));
        //2 params, operator & player
        registry->addEnum<CMOP>("OP3",
            { {"op", CMOP::op},
              {"deop", CMOP::deop},
              {"ban", CMOP::ban}, 
              {"forgive", CMOP::forgive} });
        registry->registerOverload<ChainMinerCommand>(
            config_j["command"],
            makeMandatory<CommandParameterDataType::ENUM>(&ChainMinerCommand::opn, "optional", "OP3"),
            makeMandatory(&ChainMinerCommand::player, "player", &ChainMinerCommand::player_isSet));
        //2 params, operator & number
        registry->addEnum<CMOP>("OP4",
            { {"damage", CMOP::damage} });
        registry->registerOverload<ChainMinerCommand>(
            config_j["command"],
            makeMandatory<CommandParameterDataType::ENUM>(&ChainMinerCommand::opn, "optional", "OP4"),
            makeMandatory(&ChainMinerCommand::int_val, "count", &ChainMinerCommand::int_val_isSet)
            );
	}
    /* 
    * 方块独立设置
    * @pl 玩家对象
    * @page 页码，-1为全部，页码从0开始
    */
    void sendBlockSwitchMenu(Player* pl, int page = -1) const;
    //发送菜单
    void sendPlayerMenu(Player* pl) const;
    //基础设置
    void sendBasicSettingMenu(Player* pl) const;
};

//订阅指令注册事件并初始化指令
void registerCommand() {
	Event::RegCmdEvent::subscribe([](Event::RegCmdEvent e) {
		ChainMinerCommand::setup(e.mCommandRegistry);
		return true;
	});
}

#include <llapi/FormUI.h>
using namespace Form;
//C:\Program Files\WindowsApps\Microsoft.MinecraftUWP_1.18.3004.0_x64__8wekyb3d8bbwe\data\resource_packs\vanilla\textures\blocks

void ChainMinerCommand::sendPlayerMenu(Player* pl) const {
    SimpleForm form("连锁采集 - ChainMiner", "");
    form.addButton("基础设置", "", [=](Player* p_pl) { sendBasicSettingMenu(p_pl); })
        .addButton("方块开关", "", [=](Player* p_pl) { sendBlockSwitchMenu(p_pl); })
        .addButton("关闭", "");
    form.sendTo(pl);
}

void ChainMinerCommand::sendBasicSettingMenu(Player* pl) const {
    CustomForm form("连锁采集 - 基础设置");
    form.addLabel("tip1", "修改后点击提交即可保存");
    form.addToggle("chain", "连锁采集开关", playerSetting.getSwitch(pl->getXuid()));
    form.addToggle("sneak", "仅在下蹲时连锁", playerSetting.getSwitch(pl->getXuid(), "chain_while_sneaking_only"));
    form.sendTo(pl, [=](Player* p_pl, std::map<string, std::shared_ptr<CustomFormElement>> elems) {
        //为0大概率说明叉掉了
        if (elems.size() > 0) {
            if (playerSetting.getSwitch(p_pl->getXuid()) != elems["chain"]->getBool()) {
                playerSetting.setSwitch(p_pl->getXuid(), "switch", elems["chain"]->getBool());
            }
            else if (playerSetting.getSwitch(p_pl->getXuid(), "chain_while_sneaking_only") != elems["sneak"]->getBool()) {
                playerSetting.setSwitch(p_pl->getXuid(), "chain_while_sneaking_only", elems["sneak"]->getBool());
            }
            p_pl->sendText("§c[§6连§e锁§a采§b集§c] §a设置成功");
        }
        sendPlayerMenu(p_pl);
    });
}

void ChainMinerCommand::sendBlockSwitchMenu(Player* pl, int page) const {
    //第一页的page=0
    extern std::unordered_map<string, BlockInfo> block_list;//可连锁方块列表

    int count_per_page = config_j["menu.count_per_page"];
    int max_page = (block_list.size() - 1) / count_per_page;
    page = (page < max_page ? page : max_page);//取更小的页码->避免空页
    if (count_per_page != -1 && page == -1) page = 0;//当每页数量不为-1时->访问第一页
    //logger.debug("{} {} {} {}", page, max_page, count_per_page, block_list.size());
    SimpleForm form("连锁采集 - 方块开关", "选择一项进行开关");

    auto it = block_list.begin();
    advance(it, (page == -1 ? 0 : page * count_per_page));//
    for (it; (page == -1 || count_per_page) && it != block_list.end(); ++it, --count_per_page) {
        //logger.debug("{} {} {}", page, count_per_page, it->first);
        string name = it->first.substr(10);
        string nsid = "minecraft:" + name;
        bool onoff = playerSetting.getSwitch(pl->getXuid(), nsid);
        form.addButton(string((it->second.name == "" ? name : it->second.name) + "§f(" + (onoff ? "§a开启" : "§c关闭") + "§f)"), (it->second.texture == "" ? string("textures/blocks/" + name) : it->second.texture), [=](Player* p_pl) {
            if (playerSetting.getSwitch(p_pl->getXuid(), nsid)) {
                playerSetting.turnOff(p_pl->getXuid(), nsid);
                string msg = config_j["msg"]["switch.block.off"];
                msg = s_replace(msg, "%Block%", nsid);
                p_pl->sendTextPacket(msg);
            }
            else {
                playerSetting.turnOn(p_pl->getXuid(), nsid);
                string msg = config_j["msg"]["switch.block.on"];
                msg = s_replace(msg, "%Block%", nsid);
                p_pl->sendTextPacket(msg);
            }
            sendBlockSwitchMenu(p_pl, page);//一直重复发送菜单
            });
    }
    if (page >= 1)
        form.addButton("上一页", "", [=](Player* p_pl) {
        sendBlockSwitchMenu(p_pl, page - 1);//发送上一页的菜单
            });
    if (page >= 0 && page < max_page)
        form.addButton("下一页", "", [=](Player* p_pl) {
        sendBlockSwitchMenu(p_pl, page + 1);
            });
    form.addButton("关闭");
    form.sendTo(pl);
}