#include "updatenote.h"
#include <stdio.h>
#include <sqlite3.h>

void updateNote(sqlite3 *db, const int note_id, const char *new_title, const char *new_content) {
    const char *sql = "UPDATE notes SET title = ?, content = ?, updated_at = datetime('now') WHERE id = ?;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    if (sqlite3_bind_text(stmt, 1, new_title, -1, SQLITE_STATIC) != SQLITE_OK) {
        fprintf(stderr, "Failed to bind new_title: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return;
    }

    if (sqlite3_bind_text(stmt, 2, new_content, -1, SQLITE_STATIC) != SQLITE_OK) {
        fprintf(stderr, "Failed to bind new_content: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return;
    }

    if (sqlite3_bind_int(stmt, 3, note_id) != SQLITE_OK) {
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
        printf("Note %d updated successfully.\n", note_id);
    }

    sqlite3_finalize(stmt);
}