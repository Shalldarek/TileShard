#ifndef PRINT_FOLDER_CONTENT_H
#define PRINT_FOLDER_CONTENT_H
#include <sqlite3.h>


void print_folder_content(sqlite3* db, const int folder_id);

#endif