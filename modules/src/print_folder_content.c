#include "print_folder_content.h"
#include <stdio.h>
#include <sqlite3.h>

void print_folder_content(sqlite3* db, const int folder_id) {
    const char* sql = "SELECT * FROM notes WHERE folder_id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    if (sqlite3_bind_int(stmt, 1, folder_id) != SQLITE_OK) {
        printf("Failed to bind folder_id: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return;
    }

    printf("Notes in folder ID %d:\n", folder_id);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int note_id = sqlite3_column_int(stmt, 0);
        const unsigned char* title = sqlite3_column_text(stmt, 1);
        const unsigned char* content = sqlite3_column_text(stmt, 2);

        printf("Note ID: %d, Title: %s, Content: %s\n", note_id, title, content);
    }

    sqlite3_finalize(stmt);
}