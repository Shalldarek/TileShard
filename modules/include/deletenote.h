#ifndef DELETENOTE_H
#define DELETENOTE_H

#include <sqlite3.h>

void deleteNote(sqlite3 *db, const int note_id);

#endif