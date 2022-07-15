#include "pch.h"
#include "Economic.h"
#include <LLAPI.h>
#include <LoggerAPI.h>
#include <MC/Scoreboard.hpp>
#include <MC/Player.hpp>
#include <MC/Level.hpp>
#include <string>
#include <LLMoney.h>

extern Logger logger;

//LLMoney不存在返回false,其余返回true
bool Economic::init()
{
    auto llmoney = LL::getPlugin("LLMoney");
    if (!llmoney)
    {
        return false;
    }

    return true;
}

money_t Economic::getMoney(xuid_t player)
{
    return LLMoneyGet(player);
}

money_t Economic::getMoney(Player* pl)
{
    if (Economic::mode == 1) {
        return getMoney(pl->getXuid());
    }
    else if (Economic::mode == 2) {
        return Scoreboard::getScore(pl, Economic::sbname);
    }
    return 0;
}

bool Economic::setMoney(xuid_t player, money_t money)
{
    return LLMoneySet(player, money);
}

bool Economic::setMoney(Player* pl, money_t money)
{
    if (Economic::mode == 1) {
        return setMoney(pl->getXuid(), money);
    }
    else if (Economic::mode == 2) {
        return Scoreboard::setScore(pl, Economic::sbname, int(money));
    }
    return false;
}

bool Economic::addMoney(xuid_t player, money_t money)
{
    return LLMoneyAdd(player, money);
}

bool Economic::addMoney(Player* pl, money_t money)
{
    if (Economic::mode == 1) {
        return addMoney(pl->getXuid(), money);
    }
    else if (Economic::mode == 2) {
        return Scoreboard::addScore(pl, Economic::sbname, int(money));
    }
    return false;
}

bool Economic::reduceMoney(xuid_t player, money_t money)
{
    return LLMoneyReduce(player, money);
}

bool Economic::reduceMoney(Player* pl, money_t money)
{
    if (Economic::mode == 1) {
        return reduceMoney(pl->getXuid(), money);
    }
    else if (Economic::mode == 2) {
        return Scoreboard::reduceScore(pl, Economic::sbname, int(money));
    }
    return false;
}

bool Economic::transMoney(xuid_t player1, xuid_t player2, money_t money, string const& notes)
{
    return LLMoneyTrans(player1, player2, money, notes);
}

bool Economic::clearMoneyHist(int time)
{
    LLMoneyClearHist(time);
    return true;
}

int Economic::mode = 0;
string Economic::sbname = "money";