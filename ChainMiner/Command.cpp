#include "pch.h"
#include "Config.h"
#include <RegCommandAPI.h>

extern nlohmann::json config_j;

//ChainMiner指令类
class ChainMinerCommand : public Command {
	enum CMOP : int {
		reload = 1
	} op;
public:
	void execute(CommandOrigin const& ori, CommandOutput& outp) const {
		switch (op) {
		case CMOP::reload: {
			readConfig();
			outp.success("§e重载成功!");
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
		registry->addEnum<CMOP>("CMOP", { {"reload", CMOP::reload} });
		registry->registerOverload<ChainMinerCommand>(config_j["command"], makeMandatory<CommandParameterDataType::ENUM>(&ChainMinerCommand::op, "operator","CMOP"));
	}
};

//订阅指令注册事件并初始化指令
void registerCommand() {
	Event::RegCmdEvent::subscribe([](Event::RegCmdEvent e) {
		ChainMinerCommand::setup(e.mCommandRegistry);
		return true;
	});
}