#include <iostream>
#include <cstdlib>
#include "../include/DbManager.h"

extern "C" {
    #include "../modules/include/echo.h"
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

        if (input == "exit") {
            run = false;
        } else if (input.substr(0, 5) == "echo ") {
            echo(input.substr(5).c_str());;
        } else {
            std::cout << "Unknown command: " << input << std::endl;
        }
    }

    return 0;
}