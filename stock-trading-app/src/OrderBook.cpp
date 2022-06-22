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
    std::cout << "time steps before: "<<timeSteps << std::endl;

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
std::cout << "average is: "<< sum / length << " length "<< length<<std::endl;  
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
    std::cout << "time steps before: "<<timeSteps << std::endl;

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
    // for (int i = 0; i < orders.size(); ++i){
    //     for (int j = 0; j < timeStamps_steps.size(); ++j){
    //         if (orders[i].timestamp == timeStamps_steps[j]){
    //             if (orders[i].orderType == orderType){
    //                 if (orders[i].product == product){
    //                     sum+= OrderBook::getHighPrice(OrderBook::getOrders(orderType, product, timeStamps_steps[j]))* orders[i].amount  ;
    //                     length+= orders[i].amount ;
    //                 }
    //             }
    //         }
    //     }
    // }

    for (int j = 0; j < timeStamps_steps.size(); ++j){
                        if (minOrMax == "max" )
                        sum+= OrderBook::getHighPrice(OrderBook::getOrders(orderType, product, timeStamps_steps[j])) ;
                        if (minOrMax == "min")
                        sum+= OrderBook::getLowPrice(OrderBook::getOrders(orderType, product, timeStamps_steps[j])) ;
                        ++length ;
                    
                
            
        }

std::cout << "predicted price is  "<< sum / length << " based on the last "<< length<<std::endl;  
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

void OrderBook::insertOrder(OrderBookEntry& order)
{
    orders.push_back(order);
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp)
{
// asks = orderbook.asks
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, 
                                                 product, 
                                                 timestamp);
// bids = orderbook.bids
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, 
                                                 product, 
                                                    timestamp);

    // sales = []
    std::vector<OrderBookEntry> sales; 

    // I put in a little check to ensure we have bids and asks
    // to process.
    if (asks.size() == 0 || bids.size() == 0)
    {
        std::cout << " OrderBook::matchAsksToBids no bids or asks" << std::endl;
        return sales;
    }

    // sort asks lowest first
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
    // sort bids highest first
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);
    // for ask in asks:
    std::cout << "max ask " << asks[asks.size()-1].price << std::endl;
    std::cout << "min ask " << asks[0].price << std::endl;
    std::cout << "max bid " << bids[0].price << std::endl;
    std::cout << "min bid " << bids[bids.size()-1].price << std::endl;
    
    for (OrderBookEntry& ask : asks)
    {
    //     for bid in bids:
        for (OrderBookEntry& bid : bids)
        {
    //         if bid.price >= ask.price # we have a match
            if (bid.price >= ask.price)
            {
    //             sale = new order()
    //             sale.price = ask.price
            OrderBookEntry sale{ask.price, 0, timestamp, 
                product, 
                OrderBookType::asksale};

                if (bid.username == "simuser")
                {
                    sale.username = "simuser";
                    sale.orderType = OrderBookType::bidsale;
                }
                if (ask.username == "simuser")
                {
                    sale.username = "simuser";
                    sale.orderType =  OrderBookType::asksale;
                }
            
    //             # now work out how much was sold and 
    //             # create new bids and asks covering 
    //             # anything that was not sold
    //             if bid.amount == ask.amount: # bid completely clears ask
                if (bid.amount == ask.amount)
                {
    //                 sale.amount = ask.amount
                    sale.amount = ask.amount;
    //                 sales.append(sale)
                    sales.push_back(sale);
    //                 bid.amount = 0 # make sure the bid is not processed again
                    bid.amount = 0;
    //                 # can do no more with this ask
    //                 # go onto the next ask
    //                 break
                    break;
                }
    //           if bid.amount > ask.amount:  # ask is completely gone slice the bid
                if (bid.amount > ask.amount)
                {
    //                 sale.amount = ask.amount
                    sale.amount = ask.amount;
    //                 sales.append(sale)
                    sales.push_back(sale);
    //                 # we adjust the bid in place
    //                 # so it can be used to process the next ask
    //                 bid.amount = bid.amount - ask.amount
                    bid.amount =  bid.amount - ask.amount;
    //                 # ask is completely gone, so go to next ask                
    //                 break
                    break;
                }


    //             if bid.amount < ask.amount # bid is completely gone, slice the ask
                if (bid.amount < ask.amount && 
                   bid.amount > 0)
                {
    //                 sale.amount = bid.amount
                    sale.amount = bid.amount;
    //                 sales.append(sale)
                    sales.push_back(sale);
    //                 # update the ask
    //                 # and allow further bids to process the remaining amount
    //                 ask.amount = ask.amount - bid.amount
                    ask.amount = ask.amount - bid.amount;
    //                 bid.amount = 0 # make sure the bid is not processed again
                    bid.amount = 0;
    //                 # some ask remains so go to the next bid
    //                 continue
                    continue;
                }
            }
        }
    }
    return sales;             
}
