#include "deletenote.h"
#include <stdio.h>
#include <sqlite3.h>

void deleteNote(sqlite3 *db, const int note_id) {
    const char *sql = "DELETE FROM notes WHERE id = ?;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    if (sqlite3_bind_int(stmt, 1, note_id) != SQLITE_OK) {
        fprintf(stderr, "Failed to bind note_id: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return;
    }

    if (sqlite3_changes(db) == 0) {
        printf("No note found with ID %d.\n", note_id);
    } else {
        printf("Note %d deleted successfully.\n", note_id);
    }

    sqlite3_finalize(stmt);
}