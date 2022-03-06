#include "pch.h"
#include "Utils.h"
#include "Config.h"
#include "PlayerSetting.h"
#include "Plugin.h"
#include <RegCommandAPI.h>
#include <MC/ItemStack.hpp>
#include <MC/CompoundTag.hpp>
#include <MC/Player.hpp>
#include <third-party/FMT/core.h>

extern nlohmann::json config_j;

//ChainMiner指令类
class ChainMinerCommand : public Command {
	enum CMOP : int {
		reload = 1,
        on = 200,
        off = 201,
        test = 999
	} op;
    CommandSelector<Player> player;
    bool player_isSet;
public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const {
		switch (op) {
            case CMOP::reload: {
                if(ori.getPermissionsLevel() > 0) {
                    readConfig();
                    outp.success("§e重载成功!");
                }
                return;
            }
            extern PlayerSetting playerSetting;
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
            case CMOP::test: {
                if (ori.getPermissionsLevel() > 0) {
                    outp.success(fmt::format("{} {}", countTaskList(), countPos2Id()));
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
		registry->addEnum<CMOP>("OP1",
            { {"reload", CMOP::reload}, {"test", CMOP::test}});
        registry->addEnum<CMOP>("OP2",
                                { {"on", CMOP::on},
                                  {"off", CMOP::off} });
		registry->registerOverload<ChainMinerCommand>(
                config_j["command"],
                makeMandatory<CommandParameterDataType::ENUM>(&ChainMinerCommand::op, "optional","OP1"));
        registry->registerOverload<ChainMinerCommand>(
                config_j["command"],
                makeMandatory<CommandParameterDataType::ENUM>(&ChainMinerCommand::op, "optional","OP2"),
                makeOptional(&ChainMinerCommand::player,"player",&ChainMinerCommand::player_isSet));
	}
};

//订阅指令注册事件并初始化指令
void registerCommand() {
	Event::RegCmdEvent::subscribe([](Event::RegCmdEvent e) {
		ChainMinerCommand::setup(e.mCommandRegistry);
		return true;
	});
}