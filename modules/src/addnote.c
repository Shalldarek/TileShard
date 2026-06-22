#include "addnote.h"
#include <stdio.h>
#include <sqlite3.h>

void addNote(sqlite3 *db, const int folder_id, const char *title, const char *content) {
    const char *sql = "INSERT INTO notes (folder_id, title, content) VALUES (?, ?, ?);";
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error while preparing query: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_int(stmt, 1, folder_id);
    sqlite3_bind_text(stmt, 2, title, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, content, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Error while executing query: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Note '%s' added successfully.\n", title);
    }

    sqlite3_finalize(stmt);
}