#include "pch.h"
#include "Config.h"
#include <RegCommandAPI.h>
#include <MC/ItemStack.hpp>
#include <MC/CompoundTag.hpp>
#include <MC/Player.hpp>

extern nlohmann::json config_j;

//ChainMiner指令类
class ChainMinerCommand : public Command {
	enum CMOP : int {
		reload = 1,
        on = 200,
        off = 201,
	} op;
public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const {
		switch (op) {
            case CMOP::reload: {
                readConfig();
                outp.success("§e重载成功!");
                return;
            }
            case CMOP::on: {
                return;
            }
            case CMOP::off: {
                return;
            }
		default:
			break;
		}
	}
	static void setup(CommandRegistry* registry) {
		using RegisterCommandHelper::makeMandatory;
		using RegisterCommandHelper::makeOptional;
		registry->registerCommand(config_j["command"], "ChainMiner连锁采集", CommandPermissionLevel::Any, { (CommandFlagValue)0 }, { (CommandFlagValue)0x80 });
		registry->addEnum<CMOP>("CMOP", { {"reload", CMOP::reload}, {"on", CMOP::on}, {"off", CMOP::off} });
		registry->registerOverload<ChainMinerCommand>(config_j["command"], makeMandatory<CommandParameterDataType::ENUM>(&ChainMinerCommand::op, "operator","操作"));
	}
};

//订阅指令注册事件并初始化指令
void registerCommand() {
	Event::RegCmdEvent::subscribe([](Event::RegCmdEvent e) {
		ChainMinerCommand::setup(e.mCommandRegistry);
		return true;
	});
}