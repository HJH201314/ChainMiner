#pragma once
#include <string>
using std::string;

typedef long long money_t;
typedef string xuid_t;

enum LLMoneyEvent
{
    Set, Add, Reduce, Trans
};
typedef bool (*LLMoneyCallback)(LLMoneyEvent type, xuid_t from, xuid_t to, money_t value);


class Economic
{
public:
    static int mode;
    static string sbname;
    static bool init();

    static money_t getMoney(xuid_t player);
    static bool setMoney(xuid_t player, money_t money);
    static bool addMoney(xuid_t player, money_t money);
    static bool reduceMoney(xuid_t player, money_t money);
    static bool transMoney(xuid_t player1, xuid_t player2, money_t money, string const& notes);
    static std::string getMoneyHist(xuid_t player, int time);
    static bool clearMoneyHist(int time);

    static money_t getMoney(Player* pl);
    static bool setMoney(Player* pl, money_t money);
    static bool addMoney(Player* pl, money_t money);
    static bool reduceMoney(Player* pl, money_t money);
};