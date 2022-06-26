#include "OrderBook.h"
#include "CSVReader.h"
#include <algorithm>
#include <map>
#include <algorithm>
#include <iostream>
#include <numeric>

/** construct, reading a csv data file */
OrderBook::OrderBook(std::string filename)
{
    orders = CSVReader::readCSV(filename);
}

/** return vector of all know products in the dataset*/
std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;

    std::map<std::string,bool> prodMap;

    for (OrderBookEntry& e : orders)
    {
        prodMap[e.product] = true;
    }
    
    // now flatten the map to a vector of strings
    for (auto const& e : prodMap)
    {
        products.push_back(e.first);
    }

    return products;
}
/** return vector of Orders according to the sent filters*/
std::vector<OrderBookEntry> OrderBook::getOrders(const OrderBookType& type, 
                                                const std::string& product, 
                                                const std::string& timestamp)
{
    std::vector<OrderBookEntry> orders_sub;



    for (const OrderBookEntry& e : orders)
    {
        if (e.orderType == type && 
            e.product == product && 
            e.timestamp == timestamp )
            {
                orders_sub.push_back(e);
            }
    }
    return orders_sub;
}


double OrderBook::getHighPrice(const std::vector<OrderBookEntry>& orders)
{
    double max = orders[0].price;
    for (const OrderBookEntry& e : orders)
    {
        if (e.price > max)max = e.price;
    }
    return max;
}

double OrderBook::getAvg( const std::string& product, const std::string& currenTime, const  int& steps, const OrderBookType& orderType  )
{
    int timeSteps = steps;
    std::vector<std::string> timestamp;
    double sum = 0;
    double  length = 0;
    std::map<std::string,bool> stampMap;
    std::vector<std::string> timeStamps_steps;

    for (OrderBookEntry& e : orders)
    {
        stampMap[e.timestamp] = true;
    }
    for (auto const& e : stampMap)
    {
        if ( e.first <= currenTime)
        {
            timestamp.push_back(e.first);
        }
        
    }
    std::sort(timestamp.begin(), timestamp.end(), OrderBookEntry::reverseCompare);

    for ( int k = 0; k < timestamp.size() ; ++k)
    {
        if ( timeSteps < 0)
            break;
        
        timeStamps_steps.push_back(timestamp[k]);
        -- timeSteps;
    }
    for (int i = 0; i < orders.size(); ++i){
        for (int j = 0; j < timeStamps_steps.size(); ++j){
            if (orders[i].timestamp == timeStamps_steps[j]){
                if (orders[i].orderType == orderType){
                    if (orders[i].product == product){
                        sum+= orders[i].price * orders[i].amount  ;
                        length+= orders[i].amount ;
                    }
                }
            }
        }
    }
std::cout << "advisorbot> average is: "<< sum / length<<std::endl;  
return 0;
}

double OrderBook::predict(const std::string& product, const std::string& currenTime, const OrderBookType& orderType, const std::string& minOrMax )
{
    int timeSteps = 10;
    std::vector<std::string> timestamp;
    double sum = 0;
    double  length = 0;
    std::map<std::string,bool> stampMap;
    std::vector<std::string> timeStamps_steps;
   

    for (OrderBookEntry& e : orders)
    {
        stampMap[e.timestamp] = true;
    }
    for (auto const& e : stampMap)
    {
        if ( e.first <= currenTime)
        {
            timestamp.push_back(e.first);
        }
        
    }
    std::sort(timestamp.begin(), timestamp.end(), OrderBookEntry::reverseCompare);

    for ( int k = 0; k < timestamp.size() ; ++k)
    {
        if ( timeSteps < 0)
            break;
        
        timeStamps_steps.push_back(timestamp[k]);
        -- timeSteps;
    }
    for (int j = 0; j < timeStamps_steps.size(); ++j){
                        if (minOrMax == "max" )
                        sum+= OrderBook::getHighPrice(OrderBook::getOrders(orderType, product, timeStamps_steps[j])) ;
                        if (minOrMax == "min")
                        sum+= OrderBook::getLowPrice(OrderBook::getOrders(orderType, product, timeStamps_steps[j])) ;
                        ++length ;
        }

std::cout << "advisorbot> predicted price is  "<< sum / length << " based on the last " << length << " steps" <<std::endl;  
return 0;
}
double OrderBook::recordEntry(const std::string& product, 
                              const std::string& currenTime, 
                              const int& steps,
                              const OrderBookType& orderType, 
                              const std::string& minOrMax)
{
    int timeSteps = steps;
    double minMax = 0;
    double temp = 0;
    std::vector<std::string> timestamp;
    double sum = 0;
    double  length = 0;
    std::map<std::string,bool> stampMap;
    std::vector<std::string> timeStamps_steps;

    for (OrderBookEntry& e : orders)
    {
        stampMap[e.timestamp] = true;
    }
    for (auto const& e : stampMap)
    {
        if ( e.first <= currenTime)
        {
            timestamp.push_back(e.first);
        }
        
    }
    std::sort(timestamp.begin(), timestamp.end(), OrderBookEntry::reverseCompare);

    for ( int k = 0; k < timestamp.size() ; ++k)
    {
        if ( timeSteps < 0)
            break;
        
        timeStamps_steps.push_back(timestamp[k]);
        -- timeSteps;
    }

    if (minOrMax == "max" )
        minMax = OrderBook::getHighPrice(OrderBook::getOrders(orderType, product, currenTime));
    
    if (minOrMax == "min" )
        minMax = OrderBook::getLowPrice(OrderBook::getOrders(orderType, product, currenTime));


    for (int j = 0; j < timeStamps_steps.size(); ++j){
                        if (minOrMax == "max" ){
                            temp = OrderBook::getHighPrice(OrderBook::getOrders(orderType, product, timeStamps_steps[j]));
                            if (temp > minMax ) 
                            minMax = temp;
                              
                        }
                        
                        if (minOrMax == "min" ){
                            temp = OrderBook::getLowPrice(OrderBook::getOrders(orderType, product, timeStamps_steps[j]));
                            if (temp < minMax ) 
                            minMax = temp;
                              
                        }
        }
    std::cout << "advisorbot> the record  " << minOrMax << " price is: "<< minMax<<std::endl;
        return 0;
}

double OrderBook::getLowPrice(const std::vector<OrderBookEntry>& orders)
{
    double min = orders[0].price;
    for (const OrderBookEntry& e : orders)
    {
        if (e.price < min)min = e.price;
    }
    return min;
}

std::string OrderBook::getEarliestTime()
{
    return orders[0].timestamp;
}

std::string OrderBook::getNextTime(std::string timestamp)
{
    std::string next_timestamp = "";
    for (OrderBookEntry& e : orders)
    {
        if (e.timestamp > timestamp) 
        {
            next_timestamp = e.timestamp;
            break;
        }
    }
    if (next_timestamp == "")
    {
        next_timestamp = orders[0].timestamp;
    }
    return next_timestamp;
}

