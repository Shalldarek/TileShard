#include "addfolder.h"
#include <stdio.h>
#include <sqlite3.h>

void addFolder(sqlite3 *db, const char *name) {
    const char *sql = "INSERT INTO folders (name) VALUES (?);";
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error while preparing query: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Error while executing query: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Folder '%s' added successfully.\n", name);
    }

    sqlite3_finalize(stmt);
}