#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "MerkelMain.h"
#include "CSVReader.h"


MerkelMain::MerkelMain(){
    
}


void MerkelMain::init(){

    //loadOrderBook();
    wallet.insertCurrency("BTC",10);

int input;

currentTime=orderBook.getEarliestTime();

while (true){

    printMenu();
    input=getUserOption();
    processUserOption(input);
}
}

//void MerkelMain::loadOrderBook(){

    //Store all of the orders in the reader class

//orders=CSVReader::readCSV("20200317.csv");

    
     

// orders.push_back(OrderBookEntry  
// {1000,
// 0.02,
// "2020/03/17 17:01:24.884492",
//s "BTC/USDT",
// OrderBookType::bid});


// orders.push_back(OrderBookEntry 
// {2000,
// 0.02,
// "2020/03/17 17:01:24.884492",
// "BTC/USDT",
// OrderBookType::ask});


// std::cout<<"The first item"<<std::endl;
// std::cout<< "The price is " <<orders[0].price<<std::endl;
// std::cout<<"The priceB is " << orders[0].amount<<std::endl;
// std::cout<<"The  product is " << orders[0].product<<std::endl;
// std::cout<<"the timestamp is " <<orders[0].timestamp<<std::endl;
 
// for (OrderBookEntry& order: orders) {
//  std::cout <<"The price is"<< order.price<<std::endl;

// } 
// for (unsigned int i=0;i<orders.size();++i){

// std::cout<<"The price is Array style:"<<orders[i].price<<std::endl;

// }


void MerkelMain::printMenu(){

//1  print help
std::cout<<"1: Help"<<std::endl;
//2 print exchange stats
std::cout<<"2: Print exchange stats "<<std::endl;
//3 make an offer
std::cout<<"3: Make an offer"<<std::endl;
//4 make a bid
std::cout<<"4: Make a bid"<<std::endl;
//5 print wallet
std::cout<<"5: Print wallet"<<std::endl;
// 6 continue
std::cout<<"6 Continue"<<std::endl;
std::cout<<"============"<<std::endl;
std::cout<<"Type in 1-6"<<std::endl;

std::cout<<"Current time is"<<currentTime<<std::endl;

}

int MerkelMain::getUserOption(){

int userOption=0;
std::string line;

std::cout<<"Type in 1-6"<<std::endl;
std::getline(std::cin,line);

try{
    userOption=std::stoi(line);
}

catch(const std::exception& e){
//
}

//std::cin>>userOption;
std::cout<<"You chose:"<<userOption<<std::endl;

return userOption;

}

void  MerkelMain::printHelp(){std::cout<<"Help - your aim is to make money"<<std::endl;}

void  MerkelMain::printMarketStats(){

    for (std::string const p: orderBook.getKnownProducts()){

        //Outputs string of all matching products

        std::cout<<"Product:" << p << std::endl;


        std::vector<OrderBookEntry> entries=orderBook.getOrders(OrderBookType::ask,p,currentTime);
        //Grabs all the data from the "Eth/BTC file"
        std::vector<OrderBookEntry> entriesTwo=orderBook.getOrders(OrderBookType::ask,"ETH/BTC","2020/03/17 17:01:24.884492");

        std::cout<<"Asks seen:"<<entries.size()<<std::endl;


        //Outputs all the specific asks of that product type below: Comment out for later analysis.

        // if (p=="BTC/USDT"){
        //  for (unsigned int i=0;i<entriesTwo.size();++i){

        //  std::cout<<"The prices for BTC/USDT are:"<<entriesTwo[i].amount<<std::endl;

        // }
        // }

            // if (p=="DOGE/BTC"){
        //  for (unsigned int i=0;i<entriesTwo.size();++i){

        //  std::cout<<"The prices for DOGE/BTC are:"<<entriesTwo[i].amount<<std::endl;

        // }
        // }

    // if (p=="DOGE/USDT"){
        //  for (unsigned int i=0;i<entriesTwo.size();++i){

        //  std::cout<<"The prices for DOGE/USDT are:"<<entriesTwo[i].amount<<std::endl;

        // }
        // }

    // if (p=="ETH/BTC"){
        //  for (unsigned int i=0;i<entriesTwo.size();++i){

        //  std::cout<<"The prices for ETH/BTC are:"<<entriesTwo[i].amount<<std::endl;

        // }
        // }

    // if (p=="ETH/USDT"){
        //  for (unsigned int i=0;i<entriesTwo.size();++i){

        //  std::cout<<"The prices for ETH/USDT are:"<<entriesTwo[i].amount<<std::endl;

        // }
        // }

    }
    
    // std::cout<<"Orderbook contains:"<<orders.size()<<std::endl;
    
    // unsigned int bids=0;
    // unsigned int asks=0;

    // for (OrderBookEntry& e: orders){

    //     if (e.orderType==OrderBookType::ask){
    //         asks++;
    //     }
    //      if (e.orderType==OrderBookType::bid){
    //          bids++;
    //      
    // }

    // std::cout<<"Amount of bids are:"<< bids<<"Amount of asks are:"<<asks<<std::endl;
    
    
    }
    
void  MerkelMain::enterAsk(){

    std::cout<<"Mark and offer - enter the amount: product, price, amount. eg. ETH/BTC,200,0.5"<<std::endl;
    std::string input;

    //Getline function parses files.
    //Reading from cin, putting in input


        std::getline(std::cin,input);
    
    std::cout<< "You typed"<<input <<std::endl;
    std::vector<std::string> tokens= CSVReader::tokenise(input,',');

    if (tokens.size()!=3){

        std::cout<<"Bad input!"<<input<<std::endl;
    }
    else{

        try{
                OrderBookEntry obe= CSVReader::stringstoOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0], //Timestamp
                OrderBookType::ask
        );

        obe.username="simuser";

        if (wallet.canFulfillOrder(obe))
        {
            orderBook.insertOrder(obe);
            std::cout<<"Wallet looks good!"<<std::endl;


        }

        else{

            std::cout<<"Insufficient funds"<<std::endl;
        }
        //orderBook.insertOrder(obe); //Sorts the order whenever data is input with the function we implemented in
        //OrderBookEntry

        }
        catch(const std::exception&e){
            std::cout<<"MerkeLMain:: enterAsk bad input"<<std::endl;
            throw;

        }

    }

    }
void  MerkelMain::enterBid(){
    
    std::cout<<"Make a bid - enter the amount"<<std::endl;
    
    
    std::cout<<"Mark and offer - enter the amount: product, price, amount. eg. ETH/BTC,200,0.5"<<std::endl;
    std::string input;

    //Getline function parses files.
    //Reading from cin, putting in input


        std::getline(std::cin,input);
    
    std::cout<< "You typed"<<input <<std::endl;
    std::vector<std::string> tokens= CSVReader::tokenise(input,',');

    if (tokens.size()!=3){

        std::cout<<"Bad input!"<<input<<std::endl;
    }
    else{

        try{
                OrderBookEntry obe= CSVReader::stringstoOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0], //Timestamp
                OrderBookType::bid
        );

         obe.username="simuser";

        if (wallet.canFulfillOrder(obe))
        {
            orderBook.insertOrder(obe);
            std::cout<<"Wallet looks good!"<<std::endl;


        }

        else{

            std::cout<<"Insufficient funds"<<std::endl;
        }
        //orderBook.insertOrder(obe); //Sorts the order whenever data is input with the function we implemented in
        //OrderBookEntry

        }
        catch(const std::exception&e){
            std::cout<<"MerkeLMain:: enterAsk bad input"<<std::endl;
            throw;

        }

    }

    
    
    }
void  MerkelMain::printWallet(){
    
    std::cout<<wallet.toString()<<std::endl;

}
void  MerkelMain::goToNextTimeFrame(){
    std::cout<<"Going to next time frame."<<std::endl;
    for(std::string p:orderBook.getKnownProducts()){
        std::cout<<"matching"<< p <<std::endl;
        std::vector<OrderBookEntry> sales= orderBook.matchAskToBids(p,currentTime);
        std::cout<<"Sales:"<<sales.size()<<std::endl;
        
    
    for(OrderBookEntry& sale: sales){

        std::cout<<"Sale price" <<sale.price<<"amount"<<sale.amount<<std::endl;
        if (sale.username=="simuser"){

            wallet.processSale(sale);

        }
    }


    }




    currentTime=orderBook.getNextTime(currentTime);




    
    }

void  MerkelMain::processUserOption(int userOption){

    
if (userOption==0){
std::cout<<"Invalid input"<<std::endl;

}
else if (userOption==1){
printHelp();

}
else if(userOption==2){
printMarketStats();

}
else if(userOption==3){
enterAsk();
    
}
else if (userOption==4){
enterBid();
}
else if(userOption==5){

printWallet();

}
else if(userOption==6){
goToNextTimeFrame();

}
}

