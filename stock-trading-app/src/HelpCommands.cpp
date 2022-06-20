#include <string>
#include <iostream>
#include "HelpCommands.h"



HelpCommands::HelpCommands ()
{

}

 void HelpCommands::helpMenuHandler(  std::string cmd) 
                                        
{
    if ( cmd == "prod")
    {
        std::cout << "Enter prod to list all available products for trading " <<std::endl;
         
    }
   else if (cmd == "min")
    {
        std::cout << "Enter min prodcut <order type> e.g. min ETH/BTC ask " <<std::endl;
        std::cout <<  "Purpose: find minimum bid or ask for product in current time step" <<std::endl;
        
    }
    else if (cmd == "max ")
    {
        std::cout << "Enter min prodcut <order type> e.g. max ETH/BTC ask " <<std::endl;
        std::cout <<  "Purpose: find maximum bid or ask for product in current time step" <<std::endl;
    }
    else if (cmd == "avg")
    {
        std::cout << "Enter avg prodcut <order type> <time steps> e.g. avg ETH/BTC ask 10" <<std::endl;
        std::cout <<  "compute average ask or bid for the sent product over the sent number of time steps" <<std::endl;
    }
 else if (cmd == "predict ")
    {
        std::cout << "Enter  predict <max/min> product <order type> e.g. predcit max  ETH/BTC ask" <<std::endl;
         std::cout <<  " Purpose: predict max or min ask or bid for the sent product for the next timestep" <<std::endl;
        
     
    }
else 
 std::cout << "Command is not found Enter help to list all available commands" << std::endl;
}