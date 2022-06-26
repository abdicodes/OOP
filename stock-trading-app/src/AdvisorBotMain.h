#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"



class AdvisorBotMain
{
    public:
        AdvisorBotMain();
        /** Call this to start the advisor app */
        void init();
    private: 
        void printMenu();
        void printHelp();
        void printMarketStats();
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotoNextTimeframe();
        std::string getUserOption();
        void processUserOption(const std::string& userOption);
        std::string currentTime;
        static bool productValidator(const std::vector<std::string>& entries,const std::string& tokenInput);

//      OrderBook orderBook{"20200317.csv"};
	    OrderBook orderBook{"20200601.csv"};

};
