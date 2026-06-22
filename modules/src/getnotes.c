#include <stdio.h>
#include "getnotes.h"
#include <sqlite3.h>

void getNotes(sqlite3 *db) {
    const char *sql = "SELECT id, folder_id, title, content, created_at, updated_at FROM notes;";
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error while preparing query: %s\n", sqlite3_errmsg(db));
        return;
    }

    printf("\n-------------------- All notes --------------------\n\n");

    int rowCount = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        int folder_id = sqlite3_column_type(stmt, 1) == SQLITE_NULL ? -1 : sqlite3_column_int(stmt, 1);
        const unsigned char *title = sqlite3_column_text(stmt, 2);
        const unsigned char *content = sqlite3_column_text(stmt, 3);
        const unsigned char *created_at = sqlite3_column_text(stmt, 4);
        const unsigned char *updated_at = sqlite3_column_text(stmt, 5);

        if (folder_id == -1) {
            printf("ID: %d, Folder ID: NULL, Title: %s, Content: %s, Created: %s, Updated: %s\n", id, title, content, created_at, updated_at);
        } else {
            printf("ID: %d, Folder ID: %d, Title: %s, Content: %s, Created: %s, Updated: %s\n", id, folder_id, title, content, created_at, updated_at);
        }
        rowCount++;
    }

    if (rowCount == 0) {
        printf("No notes found.\n");
    }

    printf("\n");

    sqlite3_finalize(stmt);
}