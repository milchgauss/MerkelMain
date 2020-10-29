#pragma once

#include "OrderBookEntry.h"
#include <string>
#include <vector>

 class CSVReader{
public:

CSVReader();
static std::vector<std::string> tokenise(std::string csvLine, char separator);
static std::vector<OrderBookEntry> readCSV(std::string csvFile);

static OrderBookEntry stringstoOBE (std::string price,
                                    std::string amount,
                                    std::string timestamp,
                                    std::string product, 
                                    OrderBookType OrderBookType);


private:

static OrderBookEntry stringsToOBE(std::vector <std::string> strings);
//Conversion tool to convert strings from the user in put in to an ask.




 };
