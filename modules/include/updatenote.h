#ifndef UPDATENOTE_H
#define UPDATENOTE_H

#include <sqlite3.h>

void updateNote(sqlite3 *db, const int note_id, const char *new_title, const char *new_content);

#endif