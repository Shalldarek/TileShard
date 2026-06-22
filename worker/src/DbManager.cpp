#include "../include/DbManager.h" 
#include <iostream>
#include <fstream>

DbManager::DbManager(const std::string& db_name) {
    dbName = db_name;
    db = nullptr; 

    int rc = sqlite3_open(dbName.c_str(), &db);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << "\n";
    } else {
        std::cout << "Database '" << dbName << "' opened successfully.\n";
    }
}

DbManager::~DbManager() {
    if (db) {
        sqlite3_close(db); 
        std::cout << "Connection to database closed.\n";
    }
}

bool DbManager::createTable() {
    std::string sql = R"(

    CREATE TABLE IF NOT EXISTS folders (
        id          INTEGER PRIMARY KEY AUTOINCREMENT,
        name        TEXT NOT NULL UNIQUE,
        created_at  TEXT NOT NULL DEFAULT (datetime('now'))
    );

    CREATE TABLE IF NOT EXISTS notes (
        id          INTEGER PRIMARY KEY AUTOINCREMENT,
        folder_id   INTEGER,
        title       TEXT NOT NULL,
        content     TEXT NOT NULL DEFAULT '',
        created_at  TEXT NOT NULL DEFAULT (datetime('now')),
        updated_at  TEXT NOT NULL DEFAULT (datetime('now')),

        FOREIGN KEY (folder_id) REFERENCES folders(id)
            ON DELETE SET NULL
    );

    CREATE TABLE IF NOT EXISTS links (
        id          INTEGER PRIMARY KEY AUTOINCREMENT,
        source_id   INTEGER NOT NULL,
        target_id   INTEGER NOT NULL,
        created_at  TEXT NOT NULL DEFAULT (datetime('now')),

        FOREIGN KEY (source_id) REFERENCES notes(id)
            ON DELETE CASCADE,

        FOREIGN KEY (target_id) REFERENCES notes(id)
            ON DELETE CASCADE,

        UNIQUE(source_id, target_id)
    );

    CREATE INDEX IF NOT EXISTS idx_notes_folder_id
    ON notes(folder_id);

    CREATE INDEX IF NOT EXISTS idx_notes_title
    ON notes(title);

    )";

    char* errMsg = nullptr;

    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "Error creating table: " << errMsg << "\n";
        sqlite3_free(errMsg); 
        return false;
    }
    
    return true;
}