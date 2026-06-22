#include "deletefolder.h"
#include <stdio.h>
#include <sqlite3.h>

void deleteFolder(sqlite3 *db, const int folder_id) {
    const char *sql = "DELETE FROM folders WHERE id = ?;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    if (sqlite3_bind_int(stmt, 1, folder_id) != SQLITE_OK) {
        fprintf(stderr, "Failed to bind folder_id: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
}