#include <iostream>
#include "../include/DbManager.h"

extern "C" {
    #include "../modules/echo.h"
}

int main() {
    DbManager dbManager("tiles.db");

    if (dbManager.createTable()) {
        std::cout << "Table created successfully." << std::endl;
    } else {
        std::cerr << "Failed to create table." << std::endl;
    }

    echo("Modules are working!");

    return 0;
}