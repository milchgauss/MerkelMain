#include "CSVReader.h"
#include <iostream>
#include <fstream>
 
 //Reads and returns a CSV line with 5 elements (labelled 0,1,2,3,4 from the tokenise function)
CSVReader::CSVReader(){

}
 std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFilename){
     
     std::vector<OrderBookEntry> entries;
     std::ifstream csvFile{csvFilename};
     std::string line;

    if(csvFile.is_open())
    {
        while(std::getline(csvFile,line)){
            try{   
            OrderBookEntry obe= stringsToOBE(tokenise(line,','));
            entries.push_back(obe);
            
            
            }

            catch( std::exception& e){
                std::cout<<"bad data!"<<std::endl;
        } 
        }
    }
    std::cout<<"CSVReader: Is file open? "<<csvFile.is_open() <<std::endl;
    std::cout<<"CSVReader:readCSV read "<<entries.size()<<" entries "<<std::endl;
    std::cout<<"Entry 2 amount "<<entries[2].amount<<" entries "<<std::endl;

     return entries;

 }

//Takes a line and creates a token of 0,1,2,3,4 with the intended arguments ,separated by commas.
//A simplified version of a tokenise function, only taking commas in to account -> Without consideration of exceptions like
//commas existing in the line itself.

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator){

std::vector<std::string> tokens;
//signed can be positive or negative
signed int start, end;
std::string token;
//Start searching the string and find the first character that
//isn't a comma.
start=csvLine.find_first_not_of(separator,0);
do {
//Find the first comma , after a character
end=csvLine.find_first_of(separator,start);
if (start==csvLine.length() ||start==end) break;
if (end>=0) token=csvLine.substr(start,end-start);

else token=csvLine.substr(start,csvLine.length()-start);
tokens.push_back(token);
start=end+1;

}
while (end>0);
return tokens;
 }
OrderBookEntry CSVReader::stringsToOBE(std::vector <std::string> tokens){
    double price,amount;
    
    if (tokens.size()!=5){
         std::cout<<"Bad line"<<std::endl;
         throw std::exception{};

        }
        try{
        //Try the default.
        price= std::stod(tokens[3]);
        amount= std::stod(tokens[4]);

        }
        catch(const std::exception&e){

            std::cout<<"Badfault!"<< tokens[3]<<std::endl;
            std::cout<<"Badfault!"<< tokens[4]<<std::endl;
            throw;
        }
       
   
    
    OrderBookEntry obe{

        price,
        amount,tokens[0],tokens[1], 
        OrderBookEntry::stringToOrderBookType(tokens[2])

    };
    return obe;

}

  OrderBookEntry CSVReader::stringstoOBE (std::string priceString,
                                    std::string amountString,
                                    std::string timestampString,
                                    std::string productString, 
                                    OrderBookType OrderBookType){
                                    
                                    double price, amount;
                                        try{
                                        
                                            
                                            price= std::stod(priceString);
                                            amount= std::stod(amountString);
                                            
                                        }
                                        catch(std::exception& e){
                                            
                                        std::cout<<"Bad string"<<priceString<<std::endl;
                                        std::cout<<"Bad string"<<amountString<<std::endl;
                                        throw;

                                        }
                                     OrderBookEntry obe{
                                         price,
                                         amount,
                                         timestampString,
                                         productString,
                                         OrderBookType

                                     };
                                    return obe;
                                    }