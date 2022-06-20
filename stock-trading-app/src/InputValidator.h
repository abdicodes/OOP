#pragma once
#include <string>
#include "CSVReader.h"
#include "OrderBookEntry.h"

class InputValidator
{
    public:
    
     /** a constructor, takes no arguments  */
     InputValidator();

      /** takes string input from BotAdvisor class , parses it and returns a string value
       * that can be used in the appropriate function to further process it
       */
     static OrderBookEntry:: processOrderType( std::string input);

};