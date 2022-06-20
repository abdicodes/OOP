#include "Wallet.h"
#include <iostream>
#include "MerkelMain.h"
#include "CSVReader.h"
#include "HelpCommands.h"

int main()
{   
    // MerkelMain app{};
    // app.init();
       std::vector<std::string> tokens = CSVReader::tokenise( "help avg" , ' ');
        // if ( tokens[0] == "help" && tokens.size() == 2){
        //     // do something! 
        //     HelpCommands::helpMenuHandler(tokens[1]);
        //     // std::string temp = HelpCommands::helpMenuHandler( tokens[1]);
        
        //     std::cout << tokens[1]<<std::endl;
        // }

      HelpCommands::helpMenuHandler("avg");
     return 0;
}
