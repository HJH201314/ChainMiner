#include "pch.h"
#include "Economic.h"
#include <llapi/LLAPI.h>
#include <llapi/LoggerAPI.h>
#include <llapi/mc/Scoreboard.hpp>
#include <llapi/mc/Player.hpp>
#include <llapi/mc/Level.hpp>
#include <string>

extern Logger logger;

//LLMoney不存在返回false,其余返回true
bool Economic::init()
{
    auto pl = ll::getPlugin("LLMoney");
    if (pl) {
        llmoney.init();
    }
    return !!pl;
}

money_t Economic::getMoney(Player* pl)
{
    if (Economic::mode == 1) {
        return llmoney.getMoney(pl->getXuid());
    }
    else if (Economic::mode == 2) {
        return Scoreboard::getScore(pl, Economic::sbname);
    }
    return 0;
}

bool Economic::setMoney(Player* pl, money_t money)
{
    if (Economic::mode == 1) {
        return llmoney.setMoney(pl->getXuid(), money);
    }
    else if (Economic::mode == 2) {
        return Scoreboard::setScore(pl, Economic::sbname, int(money));
    }
    return false;
}

bool Economic::addMoney(Player* pl, money_t money)
{
    if (Economic::mode == 1) {
        return llmoney.addMoney(pl->getXuid(), money);
    }
    else if (Economic::mode == 2) {
        return Scoreboard::addScore(pl, Economic::sbname, int(money));
    }
    return false;
}

bool Economic::reduceMoney(Player* pl, money_t money)
{
    if (Economic::mode == 1) {
        return llmoney.reduceMoney(pl->getXuid(), money);
    }
    else if (Economic::mode == 2) {
        return Scoreboard::reduceScore(pl, Economic::sbname, int(money));
    }
    return false;
}

bool Economic::clearMoneyHist(int time)
{
    return llmoney.clearMoneyHist(time);
}