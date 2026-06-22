#include <stdio.h>
#include "getfolders.h"
#include <sqlite3.h>

void getFolders(sqlite3 *db) {
    const char *sql = "SELECT * FROM folders;";
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error while preparing query: %s\n", sqlite3_errmsg(db));
        return;
    }

    printf("\n-------------------- All folders --------------------\n\n");
    
    int rowCount = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *name = sqlite3_column_text(stmt, 1);
        const unsigned char *date = sqlite3_column_text(stmt, 2);

        printf("ID: %d, Name: %s, Date: %s\n", id, name, date);
        rowCount++;
    }
    
    if (rowCount == 0) {
        printf("No folders found.\n");
    }
    
    printf("\n");

    sqlite3_finalize(stmt);
}