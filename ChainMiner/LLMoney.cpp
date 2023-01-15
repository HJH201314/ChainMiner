#include "pch.h"
#include "LLMoney.h"

#include <llapi/LLAPI.h>
#include <llapi/LoggerAPI.h>
#include <string>

extern Logger logger;

typedef money_t(*LLMoneyGet_T)(xuid_t);
typedef string(*LLMoneyGetHist_T)(xuid_t, int);
typedef bool (*LLMoneyTrans_T)(xuid_t, xuid_t, money_t, string const&);
typedef bool (*LLMoneySet_T)(xuid_t, money_t);
typedef bool (*LLMoneyAdd_T)(xuid_t, money_t);
typedef bool (*LLMoneyReduce_T)(xuid_t, money_t);
typedef void (*LLMoneyClearHist_T)(int);

struct dynamicSymbolsMap_type
{
    LLMoneyGet_T LLMoneyGet = nullptr;
    LLMoneySet_T LLMoneySet = nullptr;
    LLMoneyAdd_T LLMoneyAdd = nullptr;
    LLMoneyReduce_T LLMoneyReduce = nullptr;
    LLMoneyTrans_T LLMoneyTrans = nullptr;
    LLMoneyGetHist_T LLMoneyGetHist = nullptr;
    LLMoneyClearHist_T LLMoneyClearHist = nullptr;
} dynamicSymbolsMap;

bool LLMoneyAPI::init()
{
    auto llmoney = ll::getPlugin("LLMoney");
    if (!llmoney) return false;

    HMODULE h = llmoney->handle;

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

    return true;
}

money_t LLMoneyAPI::getMoney(xuid_t player)
{
    if (dynamicSymbolsMap.LLMoneyGet)
        return dynamicSymbolsMap.LLMoneyGet(player);
    else
    {
        logger.error("API money.getMoney have not been loaded!");
        return 0;
    }
}

bool LLMoneyAPI::setMoney(xuid_t player, money_t money)
{
    if (dynamicSymbolsMap.LLMoneySet)
        return dynamicSymbolsMap.LLMoneySet(player, money);
    else
    {
        logger.error("API money.setMoney have not been loaded!");
        return false;
    }
}

bool LLMoneyAPI::addMoney(xuid_t player, money_t money)
{
    if (dynamicSymbolsMap.LLMoneyAdd)
        return dynamicSymbolsMap.LLMoneyAdd(player, money);
    else
    {
        logger.error("API money.addMoney have not been loaded!");
        return false;
    }
}

bool LLMoneyAPI::reduceMoney(xuid_t player, money_t money)
{
    if (dynamicSymbolsMap.LLMoneyReduce)
        return dynamicSymbolsMap.LLMoneyReduce(player, money);
    else
    {
        logger.error("API money.reduceMoney have not been loaded!");
        return false;
    }
}

bool LLMoneyAPI::transMoney(xuid_t player1, xuid_t player2, money_t money, string const& notes)
{
    if (dynamicSymbolsMap.LLMoneyTrans)
        return dynamicSymbolsMap.LLMoneyTrans(player1, player2, money, notes);
    else
    {
        logger.error("API money.transMoney have not been loaded!");
        return false;
    }
}

std::string LLMoneyAPI::getMoneyHist(xuid_t player, int time)
{
    if (dynamicSymbolsMap.LLMoneyGetHist)
        return dynamicSymbolsMap.LLMoneyGetHist(player, time);
    else
    {
        logger.error("API money.getTransHist have not been loaded!");
        return "";
    }
}

bool LLMoneyAPI::clearMoneyHist(int time)
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