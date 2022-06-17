#include "pch.h"
#include "Economic.h"
#include <LLAPI.h>
#include <LoggerAPI.h>
#include <MC/Scoreboard.hpp>
#include <MC/Player.hpp>
#include <MC/Level.hpp>
#include <string>

extern Logger logger;

typedef money_t(*LLMoneyGet_T)(xuid_t);
typedef string(*LLMoneyGetHist_T)(xuid_t, int);
typedef bool (*LLMoneyTrans_T)(xuid_t, xuid_t, money_t, string const&);
typedef bool (*LLMoneySet_T)(xuid_t, money_t);
typedef bool (*LLMoneyAdd_T)(xuid_t, money_t);
typedef bool (*LLMoneyReduce_T)(xuid_t, money_t);
typedef void (*LLMoneyClearHist_T)(int);

typedef void (*LLMoneyListenBeforeEvent_T)(LLMoneyCallback callback);
typedef void (*LLMoneyListenAfterEvent_T)(LLMoneyCallback callback);

struct dynamicSymbolsMap_type
{
    LLMoneyGet_T LLMoneyGet = nullptr;
    LLMoneySet_T LLMoneySet = nullptr;
    LLMoneyAdd_T LLMoneyAdd = nullptr;
    LLMoneyReduce_T LLMoneyReduce = nullptr;
    LLMoneyTrans_T LLMoneyTrans = nullptr;
    LLMoneyGetHist_T LLMoneyGetHist = nullptr;
    LLMoneyClearHist_T LLMoneyClearHist = nullptr;

    LLMoneyListenBeforeEvent_T LLMoneyListenBeforeEvent = nullptr;
    LLMoneyListenAfterEvent_T LLMoneyListenAfterEvent = nullptr;
} dynamicSymbolsMap;

//LLMoney不存在返回false,其余返回true
bool Economic::init()
{
    auto llmoney = LL::getPlugin("LLMoney");
    if (!llmoney)
    {
        return false;
    }

    HMODULE h = llmoney->handler;

    dynamicSymbolsMap.LLMoneyGet = (LLMoneyGet_T)GetProcAddress(h, "LLMoneyGet");
    if (!dynamicSymbolsMap.LLMoneyGet)
        logger.warn("Fail to load API money.getMoney!");

    dynamicSymbolsMap.LLMoneySet = (LLMoneySet_T)GetProcAddress(h, "LLMoneySet");
    if (!dynamicSymbolsMap.LLMoneySet)
        logger.warn("Fail to load API money.setMoney!");

    dynamicSymbolsMap.LLMoneyAdd = (LLMoneyAdd_T)GetProcAddress(h, "LLMoneyAdd");
    if (!dynamicSymbolsMap.LLMoneyAdd)
        logger.warn("Fail to load API money.addMoney!");

    dynamicSymbolsMap.LLMoneyReduce = (LLMoneyReduce_T)GetProcAddress(h, "LLMoneyReduce");
    if (!dynamicSymbolsMap.LLMoneyReduce)
        logger.warn("Fail to load API money.reduceMoney!");

    dynamicSymbolsMap.LLMoneyTrans = (LLMoneyTrans_T)GetProcAddress(h, "LLMoneyTrans");
    if (!dynamicSymbolsMap.LLMoneyTrans)
        logger.warn("Fail to load API money.transMoney!");

    dynamicSymbolsMap.LLMoneyGetHist = (LLMoneyGetHist_T)GetProcAddress(h, "LLMoneyGetHist");
    if (!dynamicSymbolsMap.LLMoneyGetHist)
        logger.warn("Fail to load API money.getTransHist!");

    dynamicSymbolsMap.LLMoneyClearHist = (LLMoneyClearHist_T)GetProcAddress(h, "LLMoneyClearHist");
    if (!dynamicSymbolsMap.LLMoneyClearHist)
        logger.warn("Fail to load API money.clearHist!");

    dynamicSymbolsMap.LLMoneyListenBeforeEvent = (LLMoneyListenBeforeEvent_T)GetProcAddress(h, "LLMoneyListenBeforeEvent");

    return true;
}

money_t Economic::getMoney(xuid_t player)
{
    if (dynamicSymbolsMap.LLMoneyGet)
        return dynamicSymbolsMap.LLMoneyGet(player);
    else
    {
        logger.error("API money.getMoney have not been loaded!");
        return 0;
    }
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
    if (dynamicSymbolsMap.LLMoneySet)
        return dynamicSymbolsMap.LLMoneySet(player, money);
    else
    {
        logger.error("API money.setMoney have not been loaded!");
        return false;
    }
}

bool Economic::setMoney(Player* pl, money_t money)
{
    if (Economic::mode == 1) {
        return setMoney(pl->getXuid(), money);
    }
    else if (Economic::mode == 2) {
        return Scoreboard::setScore(pl, Economic::sbname, int(money));
    }
}

bool Economic::addMoney(xuid_t player, money_t money)
{
    if (dynamicSymbolsMap.LLMoneyAdd)
        return dynamicSymbolsMap.LLMoneyAdd(player, money);
    else
    {
        logger.error("API money.addMoney have not been loaded!");
        return false;
    }
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
    if (dynamicSymbolsMap.LLMoneyReduce)
        return dynamicSymbolsMap.LLMoneyReduce(player, money);
    else
    {
        logger.error("API money.reduceMoney have not been loaded!");
        return false;
    }
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
    if (dynamicSymbolsMap.LLMoneyTrans)
        return dynamicSymbolsMap.LLMoneyTrans(player1, player2, money, notes);
    else
    {
        logger.error("API money.transMoney have not been loaded!");
        return false;
    }
}

std::string Economic::getMoneyHist(xuid_t player, int time)
{
    if (dynamicSymbolsMap.LLMoneyGetHist)
        return dynamicSymbolsMap.LLMoneyGetHist(player, time);
    else
    {
        logger.error("API money.getTransHist have not been loaded!");
        return "";
    }
}

bool Economic::clearMoneyHist(int time)
{
    if (dynamicSymbolsMap.LLMoneyClearHist)
    {
        dynamicSymbolsMap.LLMoneyClearHist(time);
        return true;
    }
    else
    {
        logger.error("API money.clearHist have not been loaded!");
        return false;
    }
}

int Economic::mode = 0;
string Economic::sbname = "money";