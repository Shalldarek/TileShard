#include <iostream>
#include <cstdlib>
#include "../include/DbManager.h"

extern "C" {
    #include "../modules/include/echo.h"
    #include "../modules/include/getfolders.h"
    #include "../modules/include/addfolder.h"
    #include "../modules/include/allcommands.h"
}

int main() {
    DbManager dbManager("tiles.db");
    bool run = true;

    if (dbManager.createTable()) {
        std::cout << "Table created successfully." << std::endl;
    } else {
        std::cerr << "Failed to create table." << std::endl;
    }

    std::system("figlet -f standard 'TILE SHARD'");

    while (run) {
        std::string input;
        std::cout << "§ ";
        std::getline(std::cin, input);

        if (input.empty()) {
            continue;
        }

        size_t spacePos = input.find(' ');
        std::string command = (spacePos == std::string::npos) ? input : input.substr(0, spacePos);
        std::string args = (spacePos == std::string::npos) ? "" : input.substr(spacePos + 1);

        if (command == "exit") {
            run = false;
        } 
        else if (command == "echo") {
            echo(args.c_str());
        } 
        else if (command == "getf") {
            getFolders(dbManager.getDb());
        } 
        else if (command == "addf") {
            if (args.empty()) {
                std::cout << "Error: Folder name required. Usage: addf <folder_name>" << std::endl;
            } else {
                addFolder(dbManager.getDb(), args.c_str());
            }
        } 
        else if (command == "help") {
            allCommands();
        }
        else {
            std::cout << "Unknown command: " << input << std::endl;
        }
    }

    return 0;
}