#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "HelpCommands.h"

MerkelMain::MerkelMain()
{

}

void MerkelMain::init()
{
    std::string input;
    currentTime = orderBook.getEarliestTime();

    // wallet.insertCurrency("BTC", 10);

    while(true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}


void MerkelMain::printMenu()
{

   // to add an empty line before the execution
   std::cout<< " " <<std::endl;

   std::cout << "advisorbot> Please enter a command, or help for a list of commands"<<std::endl;
    // // 1 print help
    // std::cout << "1: Print help " << std::endl;
    // // 2 print exchange stats
    // std::cout << "2: Print exchange stats" << std::endl;
    // // 3 make an offer
    // std::cout << "3: Make an offer " << std::endl;
    // // 4 make a bid 
    // std::cout << "4: Make a bid " << std::endl;
    // // 5 print wallet
    // std::cout << "5: Print wallet " << std::endl;
    // // 6 continue   
    // std::cout << "6: Continue " << std::endl;

    // std::cout << "============== " << std::endl;

    // std::cout << "Current time is: " << currentTime << std::endl;
}

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << std::endl;
}

void MerkelMain::printMarketStats()
{
    for (std::string const& p : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, 
                                                                p, currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;

    }
    
}

void MerkelMain::enterAsk()
{
    std::cout << "Make an ask - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterAsk Bad input! " << input << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2], 
                currentTime, 
                tokens[0], 
                OrderBookType::ask 
            );
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Wallet has insufficient funds . " << std::endl;
            }
        }catch (const std::exception& e)
        {
            std::cout << " MerkelMain::enterAsk Bad input " << std::endl;
        }   
    }
}

void MerkelMain::enterBid()
{
    std::cout << "Make an bid - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterBid Bad input! " << input << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2], 
                currentTime, 
                tokens[0], 
                OrderBookType::bid 
            );
            obe.username = "simuser";

            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Wallet has insufficient funds . " << std::endl;
            }
        }catch (const std::exception& e)
        {
            std::cout << " MerkelMain::enterBid Bad input " << std::endl;
        }   
    }
}

void MerkelMain::printWallet()
{
    std::cout << wallet.toString() << std::endl;
}
        
void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;
    for (std::string p : orderBook.getKnownProducts())
    {
        std::cout << "matching " << p << std::endl;
        std::vector<OrderBookEntry> sales =  orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry& sale : sales)
        {
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl; 
            if (sale.username == "simuser")
            {
                // update the wallet
                wallet.processSale(sale);
            }
        }
        
    }

    currentTime = orderBook.getNextTime(currentTime);
}
 
std::string MerkelMain::getUserOption()
{
    // int userOption = 0;
    std::string line;
    // // std::cout << "Type in 1-6" << std::endl;
     std::getline(std::cin, line);
    // try{
    //     userOption = std::stoi(line);
    // }catch(const std::exception& e)
    // {
    //     // 
    // }
    // std::cout << "You chose: " << userOption << std::endl;
    // return userOption;
    return line;
}

void MerkelMain::processUserOption(const std::string& userOption)
{
    std::vector<std::string> tokens = CSVReader::tokenise( userOption , ' ');

    try{
        if (tokens.size() == 1){
            if (tokens[0]== "prod")
            {
                // this forloop will list all available products from orderBook object
                 std::cout << "advisorbot> Available products: "  << std::endl;
                 std::cout << "advisorbot> ";
                 for (std::string const& p : orderBook.getKnownProducts())
        {
            // this condition to parse comma correctly between products so the first product does not require comma infront.
                if ( p ==  orderBook.getKnownProducts().at(0))
                     std::cout << p  ;
            
                 else 
                     std::cout << ", " << p ;
        }
                 std::cout << std::endl;
            }

            if (tokens[0]== "help")
            {   
                //this will send input to helpMenuHandler class to display appropriate message.
                HelpCommands::helpMenuHandler(tokens[0]);  
            }
            if(tokens[0] == "time")
            {
                std::cout<< currentTime << std::endl;
            }
        }
        if (tokens.size() == 2)
        {
            
        }
    }
    catch(const std::exception& e){

    }
    // if (userOption == "help"){
        
    //      std::cout << "The available commands are help, help <cmd>, avg, time, step, min, max, prod, predict" << std::endl;

    // }

     if (userOption =="prod"){
        
    }
    try{
        std::vector<std::string> tokens = CSVReader::tokenise( userOption , ' ');
        if ( tokens[0] == "help") {
            if (tokens.size() == 2){

            }
        } {
          
            HelpCommands::helpMenuHandler(tokens[1]);

          

        };
    }
    catch(const std::exception& e){
        std::cout << "Bad input boy!" << std::endl;
    }
    // if (CSVReader::tokenise(const userOption &, " ")
// )

    // if (userOption == 0) // bad input
    // {
    //     std::cout << "Invalid choice. Choose 1-6" << std::endl;
    // }
    // if (userOption == 1) 
    // {
    //     printHelp();
    // }
    // if (userOption == 2) 
    // {
    //     printMarketStats();
    // }
    // if (userOption == 3) 
    // {
    //     enterAsk();
    // }
    // if (userOption == 4) 
    // {
    //     enterBid();
    // }
    // if (userOption == 5) 
    // {
    //     printWallet();
    // }
    // if (userOption == 6) 
    // {
    //     gotoNextTimeframe();
    // }       
}
