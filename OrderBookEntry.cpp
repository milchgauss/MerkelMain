#include "OrderBookEntry.h"


OrderBookEntry::OrderBookEntry(

double _price, //(tokens[3])
double _amount,//(tokens[4]);
std::string _timestamp, // The timestamp
std::string _product, // Product type ETH/BTC
OrderBookType _orderType, // Whether it is a bid, ask, or sale
std::string _username
)
: price(_price),
amount(_amount),
timestamp(_timestamp),
product(_product),
orderType(_orderType),
username(_username)

{

}


  OrderBookType OrderBookEntry::stringToOrderBookType(std::string s){
    if (s=="ask"){return OrderBookType::ask;}
    

    if (s=="bid") {return OrderBookType::bid;}
 
    return OrderBookType::unknown;

    }