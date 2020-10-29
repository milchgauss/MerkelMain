#include <string>
#include <map>
#include "OrderBookEntry.h"

class Wallet
{
    public:
    Wallet();
    
    // Insert currency in to the wallet
    void insertCurrency(std::string type, double amount);
    //Check if the wallet contains this much currency  or more.
    bool containsCurrency(std::string type, double amount);

    bool removeCurrency(std::string type, double amount);
    //Generates a string representation
    std::string toString();

    //Use this function to analyse whether or not you can fulfill the order
    bool canFulfillOrder (OrderBookEntry order);

    void processSale(OrderBookEntry&sale);




    private:

     std::map<std::string,double>currencies;


};