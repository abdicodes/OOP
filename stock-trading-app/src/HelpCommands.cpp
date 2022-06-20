#include <string>
#include <iostream>
#include "HelpCommands.h"



HelpCommands::HelpCommands ()
{

}
void HelpCommands::helpMenuHandler( std::string help)
{
std::cout << "The available commands are help, help <cmd>, avg, time, step, min, max, prod, predict" << std::endl;
}
 void HelpCommands::helpMenuHandler( std::string help ,std::string cmd) 

 
                                      
{
    // to add an empty line before the execution
    std::cout<< " " <<std::endl;

    if ( cmd == "prod")
    {
        std::cout << "advisorbot> Enter prod to list all available products for trading " <<std::endl;      
    }
    else if (cmd == "min")
    {
        std::cout << "advisorbot> Enter min prodcut <order type> e.g. min ETH/BTC ask " <<std::endl;
        std::cout <<  "advisorbot> Purpose: find minimum bid or ask for product in current time step" <<std::endl; 
    }
    else if (cmd == "max")
    {
        std::cout << "advisorbot> Enter min prodcut <order type> e.g. max ETH/BTC ask " <<std::endl;
        std::cout <<  "advisorbot> Purpose: find maximum bid or ask for product in current time step" <<std::endl;
    }
    else if (cmd == "avg")
    {
        std::cout << "advisorbot> Enter avg prodcut <order type> <time steps> e.g. avg ETH/BTC ask 10" <<std::endl;
        std::cout <<  "advisorbot> compute average ask or bid for the sent product over the sent number of time steps" <<std::endl;
    }
    else if (cmd == "predict")
    {
        std::cout << "advisorbot> Enter predict <max/min> product <order type> e.g. predcit max ETH/BTC ask" <<std::endl;
        std::cout <<  "advisorbot> Purpose: predict max or min ask or bid for the sent product for the next timestep" <<std::endl;
    }
     else if (cmd == "time")
    {
        std::cout << "advisorbot> Enter time to view current time in dataset, i.e. which timeframe are we looking at" <<std::endl;
    }
      else if (cmd == "step")
    {
        std::cout << "advisorbot> Enter step to move to next time step" <<std::endl;
    }
    else 
        std::cout << "advisorbot> Command is not found Enter help to list all available commands" << std::endl;
}