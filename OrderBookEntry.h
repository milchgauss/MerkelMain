#pragma once

#include <iostream>
#include <string>
#include<vector>

enum class OrderBookType{bid,ask,unknown,sale,asksale,bidsale};

class OrderBookEntry{


public:

    OrderBookEntry( 
    double _price,
    double _amount,
    std::string _timestamp,
    std::string _product,
    OrderBookType _orderType,
    std::string username="dataset"
    );
    
    static OrderBookType stringToOrderBookType(std::string s);

    //Compares two entries to one another to sort the time stamps
    static bool compareByTimeStamp(OrderBookEntry& e1, OrderBookEntry& e2){
        return e1.timestamp<e2.timestamp;
        
    }

    static bool compareByDesc(OrderBookEntry&e1, OrderBookEntry&e2){

        return e2.price>e2.price;

    }
    static bool comparebyAsc(OrderBookEntry&e1,OrderBookEntry&e2){
            return e1.price<e2.price;

    }

   
   double price;
   double amount;
   std::string timestamp;
   std::string product;
   OrderBookType orderType;

    std::string username;

};