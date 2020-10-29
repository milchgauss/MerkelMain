#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "Wallet.h"
#include "OrderBook.h"


class MerkelMain
{
public:

MerkelMain();
void init();

private:
void loadOrderBook();
void printMenu();
void printHelp();
void printMarketStats();
void enterAsk();
void enterBid();
void printWallet();
void goToNextTimeFrame();
int getUserOption();
void processUserOption(int userOption);

 OrderBook orderBook{"20200317.csv"};

std::string currentTime;
std::vector<OrderBookEntry> orders;
Wallet wallet;


};
