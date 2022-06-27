#include "AdvisorBotMain.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "HelpCommands.h"

//constructer function
AdvisorBotMain::AdvisorBotMain()
{
std::cout << " #### Welcome to advisorbot app, your simple analytic app #### " << std::endl;
}

//this will initialise the interface.
void AdvisorBotMain::init()
{
    std::string input;
    currentTime = orderBook.getEarliestTime();

    while(true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

//this function will run after each process.
void AdvisorBotMain::printMenu()
{

   // to add an empty line before the execution
   std::cout<< " " <<std::endl;

   //this will output after each input/output cycle
   std::cout << "advisorbot> Please enter a command, or help for a list of commands"<<std::endl;
}


 // process input and return string
std::string AdvisorBotMain::getUserOption()
{
    std::string line;
    std::getline(std::cin, line);
    return line;
}

// this is the parsing function that will take user input string and processes it.
void AdvisorBotMain::processUserOption(const std::string& userOption)
{
    try{
        // tokenising function 
        std::vector<std::string> tokens = CSVReader::tokenise( userOption , ' ');

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
                         std::cout << p;
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
                std::cout<< "advisorbot> Current time is: "<<currentTime << std::endl;
            }
             if(tokens[0] == "step")
            {
                currentTime = orderBook.getNextTime(currentTime);
                 std::cout<< "advisorbot> Current time moved to: "<<currentTime << std::endl;
            }
            
        }
         if (tokens.size() == 2 && tokens[0]=="help")
        {
            HelpCommands::helpMenuHandler(tokens[0],tokens[1]);
        }
         if ((tokens.size() == 3 &&  (tokens[0] == "min" ||tokens[0] == "max")) &&
            (AdvisorBotMain::productValidator(orderBook.getKnownProducts(), tokens[1])) &&
           ( tokens[2] == "bid" || tokens[2] ==  "ask"))
        {
                if (tokens[0] == "min")
                {
                    double min = OrderBook::getLowPrice(orderBook.getOrders(OrderBookEntry::stringToOrderBookType(tokens[2]), tokens[1], currentTime));
                    std::cout << "advisorbot> lowest " << tokens[2] <<  " value in the current time: "<< min << std::endl;
                }
                 if (tokens[0] == "max")
                {
                     double max = OrderBook::getHighPrice(orderBook.getOrders(OrderBookEntry::stringToOrderBookType(tokens[2]), tokens[1], currentTime));
                    std::cout << "advisorbot> highest " << tokens[2] <<  " value in the current time: " << max << std::endl;
                }   
        }
         if ( tokens.size() == 4)
        {
            if (tokens[0] == "avg" &&
             (AdvisorBotMain::productValidator(orderBook.getKnownProducts(), tokens[1]) )&&
                (tokens[2] == "bid" || tokens[2] ==  "ask"))
            {
                orderBook.getAvg(tokens[1],currentTime,0, OrderBookEntry::stringToOrderBookType(tokens[2]));
            }
             if (tokens[0] == "predict" && 
                (tokens[1] == "min" || tokens [1]== "max") && 
                (AdvisorBotMain::productValidator(orderBook.getKnownProducts(), tokens[2]) )&&
                (tokens[3] == "bid" || tokens[3] ==  "ask"))
                {
                    orderBook.predict(tokens[2], currentTime, OrderBookEntry::stringToOrderBookType(tokens[3]), tokens[1]);
                }
            }
        if (tokens.size()== 5){
            if (tokens[0] == "record" &&
             (tokens[1] == "min"  || tokens[1] == "max") &&
             (AdvisorBotMain::productValidator(orderBook.getKnownProducts(), tokens[2]) ) &&
             (tokens[3] == "bid" || tokens[3] ==  "ask")
            )
            {
                orderBook.recordEntry(tokens[2],currentTime, std::stoi(tokens[4]),OrderBookEntry::stringToOrderBookType(tokens[3]), tokens[1] );
            }
        }
        
    }
    catch(const std::exception& e){
        std::cout << "invalid input try help" << std::endl;
    }
        
}
//this function will validate the currency-pair product
bool AdvisorBotMain::productValidator(const std::vector<std::string>& entries, const std::string& tokenInput)
{

    // borrowed this line of code from stackoverflow, it finds if an item exists in a victor in a sufficient way.
    if (std::find(entries.begin(), entries.end(), tokenInput) != entries.end())
        return true;
    
    else
        return false;
    
}
