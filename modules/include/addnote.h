#ifndef ADDNOTE_H
#define ADDNOTE_H

#include <sqlite3.h>

void addNote(sqlite3 *db, const int folder_id, const char *title, const char *content);

#endif