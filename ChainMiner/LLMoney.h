#pragma once

#include <Windows.h>
typedef HMODULE MODULE_HANDLE;

typedef long long money_t;
#include <string>
typedef std::string xuid_t;

#include <vector>
class LLMoneyAPI {
public:
	bool init();
	money_t getMoney(xuid_t xuid);
	bool setMoney(xuid_t xuid, money_t money);
	bool transMoney(xuid_t from, xuid_t to, money_t val, std::string const& note = "");
	bool addMoney(xuid_t xuid, money_t money);
	bool reduceMoney(xuid_t xuid, money_t money);

	std::string getMoneyHist(xuid_t xuid, int timediff = 24 * 60 * 60);
	bool clearMoneyHist(int difftime = 0);
};