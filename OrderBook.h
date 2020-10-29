#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>


class OrderBook{
public:

    OrderBook(std::string filename);
    std::vector<std::string> getKnownProducts();
    std::vector<OrderBookEntry> getOrders(OrderBookType type,
                                         std::string product,
                                         std::string timestamp);

void insertOrder(OrderBookEntry &order);
//Orderbook should also have the ability to take orders, process, and match them

std::vector<OrderBookEntry> matchAskToBids(std::string orders, std::string product);


static double getHighPrice(std::vector<OrderBookEntry>& orders);
static double getLowPrice(std::vector<OrderBookEntry>& orders);

std::string getEarliestTime();
std::string getNextTime(std::string timestamp);

private:
std::vector<OrderBookEntry> orders;
};
