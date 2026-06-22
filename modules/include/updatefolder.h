#ifndef UPDATEFOLDER_H
#define UPDATEFOLDER_H

#include <sqlite3.h>

void updateFolder(sqlite3 *db, const int folder_id, const char *new_name);

#endif