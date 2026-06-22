#ifndef ADDFOLDER_H
#define ADDFOLDER_H
#include <sqlite3.h>
 
void addFolder(sqlite3 *db, const char *folderName);

#endif