#ifndef DELETEFOLDER_H
#define DELETEFOLDER_H
#include <sqlite3.h>

void deleteFolder(sqlite3 *db, const int folder_id);

#endif 