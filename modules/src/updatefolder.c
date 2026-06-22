#include "updatefolder.h"
#include <stdio.h>
#include <sqlite3.h>

void updateFolder(sqlite3 *db, const int folder_id, const char *new_name) {
    const char *sql = "UPDATE folders SET name = ? WHERE id = ?;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    if (sqlite3_bind_text(stmt, 1, new_name, -1, SQLITE_STATIC) != SQLITE_OK) {
        fprintf(stderr, "Failed to bind new_name: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return;
    }

    if (sqlite3_bind_int(stmt, 2, folder_id) != SQLITE_OK) {
        fprintf(stderr, "Failed to bind folder_id: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return;
    }

    if (sqlite3_changes(db) == 0) {
        printf("No folder found with ID %d.\n", folder_id);
    } else {
        printf("Folder %d updated successfully to '%s'.\n", folder_id, new_name);
    }

    sqlite3_finalize(stmt);
}