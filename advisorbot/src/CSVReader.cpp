#include "CSVReader.h"
#include <iostream>
#include <fstream>


CSVReader::CSVReader()
{

}
//this function will read the CVS file, parse the data to DataBookEntry vector.
std::vector<OrderBookEntry> CSVReader::readCSV(const std::string& csvFilename)
{
    std::vector<OrderBookEntry> entries;

    std::ifstream csvFile{csvFilename};
    std::string line;
    if (csvFile.is_open())
    {
        while(std::getline(csvFile, line))
        {
            try {
                OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
                entries.push_back(obe);
            }catch(const std::exception& e)
            {
                std::cout << "CSVReader::readCSV bad data"  << std::endl;
            }
        }// end of while
    }    

    std::cout << "CSVReader::readCSV read " << entries.size() << " entries"  << std::endl;
    return entries; 
}
//this function will take a strings vector and return a vector
std::vector<std::string> CSVReader::tokenise( const std::string& csvLine ,  const char& separator)
{
   std::vector<std::string> tokens;
   signed int start, end;
   std::string token;
    start = csvLine.find_first_not_of(separator, 0);
    do{
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end) break;
        if (end >= 0) token = csvLine.substr(start, end - start);
        else token = csvLine.substr(start, csvLine.length() - start);
        tokens.push_back(token);
    start = end + 1;
    }while(end > 0);

   return tokens; 
}
// static function that will parse a single line and return a dataBookEntry object
OrderBookEntry CSVReader::stringsToOBE(const std::vector<std::string>& tokens)
{
    double price, amount;

    if (tokens.size() != 5) // bad
    {
        std::cout << "Bad line " << std::endl;
        throw std::exception{};
    }
    // we have 5 tokens
    try {
         price = std::stod(tokens[3]);
         amount = std::stod(tokens[4]);
    }catch(const std::exception& e){
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[3]<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[4]<< std::endl; 
        throw;        
    }

    OrderBookEntry obe{price, 
                        amount, 
                        tokens[0],
                        tokens[1], 
                        OrderBookEntry::stringToOrderBookType(tokens[2])};

    return obe; 
} 