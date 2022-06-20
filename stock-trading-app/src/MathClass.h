#pragma once
#include <string>

 enum class MinMax{min, max};
 enum class BidAsk{bid, ask};



class MathClass
{
    public:
     MathClass();
     static void minCal( const std::string& product, const std::string& time, BidAsk orderType);
     static void maxCal( const std::string& product, const std::string& time, BidAsk orderType);
    
};