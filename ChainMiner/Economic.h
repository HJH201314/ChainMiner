#pragma once
#include <string>
#include "LLMoney.h"
using std::string;

typedef long long money_t;
typedef string xuid_t;

class Economic
{
public:
    int mode = 0;
    string sbname = "money";
    LLMoneyAPI llmoney;
    bool init();

    money_t getMoney(xuid_t player);
    bool setMoney(xuid_t player, money_t money);
    bool addMoney(xuid_t player, money_t money);
    bool reduceMoney(xuid_t player, money_t money);
    bool transMoney(xuid_t player1, xuid_t player2, money_t money, string const& notes);
    std::string getMoneyHist(xuid_t player, int time);
    bool clearMoneyHist(int time);

    money_t getMoney(Player* pl);
    bool setMoney(Player* pl, money_t money);
    bool addMoney(Player* pl, money_t money);
    bool reduceMoney(Player* pl, money_t money);
};