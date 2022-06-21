#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook
{
    public:
    /** construct, reading a csv data file */
        OrderBook(std::string filename);
    /** return vector of all know products in the dataset*/
        std::vector<std::string> getKnownProducts();
    /** return vector of Orders according to the sent filters*/
        std::vector<OrderBookEntry> getOrders(const OrderBookType& type, 
                                              const std::string& product, 
                                              const std::string& timestamp);

        /** returns the earliest time in the orderbook*/
        std::string getEarliestTime();
        /** returns the next time after the 
         * sent time in the orderbook  
         * If there is no next timestamp, wraps around to the start
         * */
        std::string getNextTime(std::string timestamp);

        void insertOrder(OrderBookEntry& order);

        std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

        static double getHighPrice(const std::vector<OrderBookEntry>& orders);
        static double getLowPrice(const std::vector<OrderBookEntry>& orders);
         double getAvg( const std::string& product, const std::string& currenTime,const  int& steps, const OrderBookType& orderType );

    private:
        std::vector<OrderBookEntry> orders;


};
