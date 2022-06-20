#pragma once
#include <string>



class HelpCommands
{
    public: 
       /** a constructor, takes no arguments  */
     HelpCommands();

       /** a function that outputs in the console help cmd commands
        *  takes the cmd  argument that comes after help  */
     static void helpMenuHandler( const std::string& cmd);
      static void helpMenuHandler( const std::string& help, const std::string& cmd);
    
};


