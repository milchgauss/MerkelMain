
#include "OrderBook.h"
#include "CSVReader.h"
#include <string>
#include <vector>
#include <map>
#include <algorithm>

    OrderBook::OrderBook(std::string filename){
        
       orders= CSVReader::readCSV(filename);

    }
    std::vector<std::string> OrderBook:: getKnownProducts(){

        std::vector<std::string> products;
        std::map<std::string,bool> prodMap;

        for (OrderBookEntry& e: orders){

            //Goes through the different kinds of products and prevents repetition by setting to true
            //Every time it matches the product type.
            prodMap[e.product]=true;
        }

    //Pulls out each as an iterator. Gets e -> Key first = Key= product
    //name and p
        for (auto const&e: prodMap){
            
            products.push_back(e.first);

        }

        return products;

    }
    std::vector<OrderBookEntry> OrderBook:: getOrders(OrderBookType type,
                                         std::string product,
                                         std::string timestamp){

        std::vector<OrderBookEntry> orders_sub;

        for (OrderBookEntry& e: orders){
            if (e.orderType==type && e.product==product&&e.timestamp==timestamp)
            {
                orders_sub.push_back(e);

            }

        }
        return orders_sub;
        }

        double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders){

            double max=orders[0].price;

            for (OrderBookEntry& e:orders)
            { if (e.price>max)

            max=e.price;
            
            }
            return max;
        }

       double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders){

           double min=orders[0].price;
           for(OrderBookEntry& e: orders)
            {
                if (e.price<min)
                min=e.price;

            }
            return min;

       }

       std::string OrderBook::getEarliestTime(){
        
        return orders[0].timestamp;

       }

       std::string OrderBook::getNextTime(std::string timestamp){

            std::string next_timestamp="";
              for(OrderBookEntry& e: orders)
            {
                if (e.timestamp>timestamp)
               
               {
                  next_timestamp=e.timestamp;
                  break;
               }
            }
        if(next_timestamp==""){
            next_timestamp=orders[0].timestamp;
        }
    return next_timestamp;
       }



    void OrderBook::insertOrder(OrderBookEntry &order){

        orders.push_back(order);
    //If argument returns true on the last argument, it swaps!
    //Sort algorithm will deal with the comparisonsn and swaps.
        std::sort(orders.begin(),orders.end(), OrderBookEntry::compareByTimeStamp);

    }

//---------
    //Takes a set of asks and bids so they can exchange currencies on the platform

    // Use this to log sales.
    std::vector<OrderBookEntry> OrderBook::matchAskToBids(std::string orders, std::string timestamp){
        //Work out all the successful sales and place it 
        // in to a separate file

    //Wanting to buy a certain amount
     std::vector<OrderBookEntry>  asks = getOrders(OrderBookType::ask,orders,timestamp);
    //Wanting to sell a certain amount
    std::vector<OrderBookEntry>  bids = getOrders(OrderBookType::bid,orders,timestamp);

    //Set up an empty sales 

    std::vector<OrderBookEntry> sales; 

    //Sort the asks by the lowest price
    std::sort(asks.begin(),asks.end(),OrderBookEntry::comparebyAsc);

    //Sort the bids by the highest - Priority for people who are offering the most money
    std::sort(bids.begin(),bids.end(),OrderBookEntry::compareByDesc);
    //Iterate all ofthe asks

    for (OrderBookEntry&ask:asks){

        for (OrderBookEntry&bid:bids) {

            if (bid.price>=ask.price){

                OrderBookEntry sale{
                    ask.price,
                    0,
                    timestamp,
                    ask.product,
                    OrderBookType::asksale

                  };

                if (bid.username=="simuser"){

                    sale.username="simuser";
                    sale.orderType=OrderBookType::bidsale;


                }

                if(ask.username=="simuser"){

                   
                    sale.username="simuser";
                    sale.orderType=OrderBookType::asksale;


                }


                

            if( bid.amount==ask.amount){
             
                sale.amount=ask.amount;
                sales.push_back(sale);
                bid.amount=0;
                break;
            }

            if(bid.amount>ask.amount){

                sale.amount=ask.amount;
                sales.push_back(sale);
                bid.amount=bid.amount-ask.amount;
                break;


            }
           
        
            if(bid.amount<ask.amount && bid.amount>0){

                sale.amount=bid.amount;
                sales.push_back(sale);
                ask.amount=ask.amount-bid.amount;
                bid.amount=0;
                continue;

             }

            }


    }
        // Iterate all of the bids
            // If it finds a bid that higher than the asking price, then we have found a match
            //Set the price of the sale to the ask.


            //Work out how much was sold and creates new bids and asks covering anything that was not sold

            // If bid amount is equal to ask amount
            // If 100 coin for 50 othercoin is OK
            //Then we can append the individual sale amount to the sales list
            // Set the bid amount to 0 again to make sure it is not processed again
            //Then go on to the next ask

            // If the bid amount (willing to sell) is greater than  then ask amount.
            // The ask is taken up by the bid. They just won't be able to buy as much as they wantd to.
            // Bid 100 (selling) and someone asks for 10 of those 100.
                    // Bid gets reduced by 10. So, 90 left.
                    // But ask is reduced to 0.


            // If the bid amount is less than the ask amount.
            // If someone is selling 10, but someone is asking for 100. 
            // Can still sell those 10, but they would want 90 more.
                // Bid is also reduced to 0
                //Ask gets reduced to bid-ask (100-10=90)
    }


    return sales;

    }