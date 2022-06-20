#pragma once
#include <string>



class HelpCommands
{
    public: 
       /** a constructor, takes no arguments  */
     HelpCommands();

       /** a function that outputs in the console help cmd commands
        *  takes the cmd  argument that comes after help  */
     static void helpMenuHandler( std::string cmd);
    
};


