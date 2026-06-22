#pragma once
#include <string>
#include <sqlite3.h>

class DbManager {
private:
    sqlite3* db;
    std::string dbName;

public:
    DbManager(const std::string& db_name);
    ~DbManager();

    bool createTable();
    sqlite3* getDb();
};