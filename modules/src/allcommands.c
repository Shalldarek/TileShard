#include "allcommands.h"
#include <stdio.h>

void allCommands() {
    printf("Available commands:\n");
    printf("echo <message> - Echoes the provided message.\n");
    printf("getf - Retrieves and displays all folders from the database.\n");
    printf("addf <folder_name> - Adds a new folder with the specified name to the database.\n");
    printf("updf <folder_id> <new_folder_name> - Updates the folder name for the specified folder ID.\n");
    printf("getn - Retrieves and displays all notes from the database.\n");
    printf("addn <folder_id> <title> <content> - Adds a new note to the database.\n");
    printf("updn <note_id> <new_title> <new_content> - Updates the note for the specified note ID.\n");
    printf("deln <note_id> - Deletes the note for the specified note ID.\n");
    printf("exit - Exits the application.\n");
}
