#include "Wallet.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <iostream>


Wallet::Wallet(){}


    void Wallet::processSale(OrderBookEntry&sale){
         
 std::vector<std::string> currs=CSVReader::tokenise(sale.product,'/');

    if (sale.orderType==OrderBookType::asksale){
    double outgoingamount= sale.amount;
    std::string outgoingcurrency= currs[0];
     double incomingamount= sale.amount *sale.price;
    std::string incomingcurrency= currs[1];



    currencies[incomingcurrency]+=incomingamount;
    currencies[outgoingcurrency]-=outgoingamount;

    

 }
     if (sale.orderType==OrderBookType::bidsale){
    
    double incomingamount= sale.amount;
    std::string incomingcurrency= currs[0];
     double outgoingamount= sale.amount *sale.price;
    std::string outgoingcurrency= currs[1];



    currencies[incomingcurrency]+=incomingamount;
    currencies[outgoingcurrency]-=outgoingamount;

 }
 
    }

 
    void Wallet::insertCurrency(std::string type, double amount){

        double balance;

        if (amount<0){

            throw std::exception{};
        }
        if(currencies.count(type)==0) {
            balance=0;
           
        }// Not there yet. Doesn't check value.Checks if "type" exists.

        else{
            balance=currencies[type];
        }
         balance+=amount;
        currencies[type]=balance;
    }
   
    bool Wallet:: containsCurrency(std::string type, double amount){

        if (currencies.count(type)==0)
            return false;
        
        else

            return currencies[type]>=amount;

    }


      bool Wallet::removeCurrency(std::string type, double amount){

        if (amount<0){

            throw std::exception{};
        }

          if(currencies.count(type)==0){

              return false;
          }

          else{

              if (containsCurrency(type,amount))
            {
              currencies[type]-=amount;
              return true;
            }
            else
                return false;  
            
          }
          
      }


std::string Wallet::toString(){

    //Convert the double in to a string using a standard function

    std:: string s;
    for (std::pair<std::string,double> pair:currencies){

        std::string currency= pair.first;

        double amount=pair.second;
        s+=currency+ ":" + std::to_string(amount);

    }
    return s;

}

  bool Wallet::canFulfillOrder (OrderBookEntry order){
 
 std::vector<std::string> currs=CSVReader::tokenise(order.product,'/');

    if (order.orderType==OrderBookType::ask){
    double amount= order.amount;
    std::string currency= currs[0];
    return containsCurrency(currency,amount);

 }
     if (order.orderType==OrderBookType::bid){
         
    double amount= order.amount *order.price;
    std::string currency= currs[1];
    return containsCurrency(currency,amount);

 }
 


return false;
  }