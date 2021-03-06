#include "pch.h"
#include "Utils.hpp"
#include "Global.h"
#include "Config.h"
#include "Plugin.h"
#include <RegCommandAPI.h>
#include <MC/ItemStack.hpp>
#include <MC/CompoundTag.hpp>
#include <MC/Player.hpp>
#include <third-party/FMT/core.h>

extern nlohmann::json config_j;


//ChainMiner指令类
class ChainMinerCommand : public Command {
private:
    enum CMOP : int {
        reload = 1,
        help = 2,
        op = 100,
        deop = 101,
        edit = 501,
        on = 200,
        off = 201,
        menu = 500,
        test = 999
	} opn;
    CommandSelector<Player> player;
    bool player_isSet;
public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const {
		switch (opn) {
            case CMOP::reload: {
                if(ori.getPermissionsLevel() > 0) {
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
                if(player_isSet) {//选择器
                    for(auto el : player.results(ori))
                        if(el->isPlayer())
                            if(ori.getPermissionsLevel() > 0 || pl->getXuid() == el->getXuid())
                                playerSetting.turnOn(el->getXuid());
                    outp.success(config_j["msg"]["switch.on"]);
                } else {
                    playerSetting.turnOn(pl->getXuid());
                    pl->sendTextPacket(config_j["msg"]["switch.on"]);
                }
                return;
            }
            case CMOP::off: {
                Player* pl = getPlayerFromOrigin(ori);
                if(player_isSet) {//选择器
                    for(auto el : player.results(ori))
                        if(el->isPlayer())
                            if(ori.getPermissionsLevel() > 0 || pl->getXuid() == el->getXuid())
                                playerSetting.turnOff(el->getXuid());
                    outp.success(config_j["msg"]["switch.off"]);
                } else {
                    playerSetting.turnOff(pl->getXuid());
                    pl->sendTextPacket(config_j["msg"]["switch.off"]);
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
                return;
            }
            case CMOP::menu: {
                Player* pl = getPlayerFromOrigin(ori);
                if (pl->isPlayer()) {
                    sendNormalMenu(pl);
                }
                return;
            }
            case CMOP::edit: {
                return;
            }
            case CMOP::test: {
                if (ori.getPermissionsLevel() > 0) {
                    outp.success(fmt::format("{} {}", countTaskList()/*, countPos2Id()*/, countChainingBlocks()));
                }
                return;
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
        //1 param, operator
		registry->addEnum<CMOP>("OP1",
            { {"reload", CMOP::reload}, {"test", CMOP::test}, {"menu", CMOP::menu}, {"edit", CMOP::edit}, {"help", CMOP::help}});
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
              {"deop", CMOP::deop} });
        registry->registerOverload<ChainMinerCommand>(
            config_j["command"],
            makeMandatory<CommandParameterDataType::ENUM>(&ChainMinerCommand::opn, "optional", "OP3"),
            makeMandatory(&ChainMinerCommand::player, "player", &ChainMinerCommand::player_isSet));
	}
    /*
    * @pl 玩家对象
    * @page 页码，-1为全部，页码从0开始
    */
    void sendNormalMenu(Player* pl, int page = -1) const;
};

//订阅指令注册事件并初始化指令
void registerCommand() {
	Event::RegCmdEvent::subscribe([](Event::RegCmdEvent e) {
		ChainMinerCommand::setup(e.mCommandRegistry);
		return true;
	});
}

#include <FormUI.h>

//C:\Program Files\WindowsApps\Microsoft.MinecraftUWP_1.18.3004.0_x64__8wekyb3d8bbwe\data\resource_packs\vanilla\textures\blocks

void ChainMinerCommand::sendNormalMenu(Player* pl, int page) const {
    //第一页的page=0
    using namespace Form;
    extern std::unordered_map<string, BlockInfo> block_list;//可连锁方块列表

    int count_per_page = config_j["menu.count_per_page"];
    int max_page = (block_list.size() - 1) / count_per_page;
    page = (page < max_page ? page : max_page);//取更小的页码->避免空页
    if (count_per_page != -1 && page == -1) page = 0;//当每页数量不为-1时->访问第一页
    //logger.debug("{} {} {} {}", page, max_page, count_per_page, block_list.size());
    SimpleForm form("连锁采集 - ChainMiner", "选择一项进行开关");

    auto it = block_list.begin();
    advance(it, (page == -1 ? 0 : page * count_per_page));//
    for (it; (page == -1 || count_per_page) && it != block_list.end(); ++it, --count_per_page) {
        //logger.debug("{} {} {}", page, count_per_page, it->first);
        string name = it->first.substr(10);
        string nsid = "minecraft:" + name;
        bool onoff = playerSetting.getSwitch(pl->getXuid(), nsid);
        form.addButton(string(name + "§f(" + (onoff ? "§a开启" : "§c关闭") + "§f)"), (it->second.texture == "" ? string("textures/blocks/" + name) : it->second.texture), [=](Player* p_pl) {
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
            sendNormalMenu(p_pl, page);//一直重复发送菜单
            });
    }
    if (page >= 1)
        form.addButton("上一页", "", [=](Player* p_pl) {
        sendNormalMenu(p_pl, page - 1);//发送上一页的菜单
            });
    if (page >= 0 && page < max_page)
        form.addButton("下一页", "", [=](Player* p_pl) {
        sendNormalMenu(p_pl, page + 1);
            });
    form.addButton("关闭");
    form.sendTo(pl);
}