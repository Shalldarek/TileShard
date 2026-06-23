#include <iostream>
#include <cstdlib>
#include "../include/DbManager.h"

const std::string GREEN = "\033[32m";
const std::string RED = "\033[31m";
const std::string RESET = "\033[0m";

extern "C" {
    #include "../modules/include/echo.h"
    #include "../modules/include/getfolders.h"
    #include "../modules/include/addfolder.h"
    #include "../modules/include/updatefolder.h"
    #include "../modules/include/allcommands.h"
    #include "../modules/include/deletefolder.h"
    #include "../modules/include/getnotes.h"
    #include "../modules/include/addnote.h"
    #include "../modules/include/updatenote.h"
    #include "../modules/include/deletenote.h"
    #include "../modules/include/print_folder_content.h"
}

int main() {
    DbManager dbManager("tiles.db");
    bool run = true;

    if (dbManager.createTable()) {
        std::cout << "Table created successfully." << std::endl;
    } else {
        std::cerr << "Failed to create table." << std::endl;
    }

    std::system("figlet -f standard 'TILE SHARD'");

    while (run) {
        std::string input;
        std::cout << "§ ";
        std::getline(std::cin, input);

        if (input.empty()) {
            continue;
        }

        size_t spacePos = input.find(' ');
        std::string command = (spacePos == std::string::npos) ? input : input.substr(0, spacePos);
        std::string args = (spacePos == std::string::npos) ? "" : input.substr(spacePos + 1);

        if (command == "exit") {
            run = false;
        } 
        else if (command == "echo") {
            std::cout << GREEN << "✓ " << RESET;
            echo(args.c_str());
        } 
        else if (command == "getf") {
            std::cout << GREEN << "✓ " << RESET;
            getFolders(dbManager.getDb());
        } 
        else if (command == "addf") {
            if (args.empty()) {
                std::cout << "Error: Folder name required. Usage: addf <folder_name>" << std::endl;
            } else {
                std::cout << GREEN << "✓ " << RESET;
                addFolder(dbManager.getDb(), args.c_str());
            }
        } 
        else if (command == "help") {
            std::cout << GREEN << "✓ " << RESET;
            allCommands();
        }
        else if (command == "delf") {
            if (args.empty()) {
                std::cout << "Error: Folder ID required. Usage: delf <folder_id>" << std::endl;
            } else {
                try {
                    int folder_id = std::stoi(args);
                    std::cout << GREEN << "✓ " << RESET;
                    deleteFolder(dbManager.getDb(), folder_id);
                } catch (const std::invalid_argument&) {
                    std::cout << "Error: Invalid folder ID. Please provide a valid integer." << std::endl;
                }
            }
        }
        else if (command == "updf") {
            size_t folderNamePos = args.find(' ');

            if (folderNamePos == std::string::npos) {
                std::cout << "Error: Folder ID and new folder name required. Usage: updf <folder_id> <new_folder_name>" << std::endl;
            } else {
                std::string folderIdStr = args.substr(0, folderNamePos);
                std::string newFolderName = args.substr(folderNamePos + 1);

                if (newFolderName.empty()) {
                    std::cout << "Error: New folder name required. Usage: updf <folder_id> <new_folder_name>" << std::endl;
                } else {
                    try {
                        int folder_id = std::stoi(folderIdStr);
                        std::cout << GREEN << "✓ " << RESET;
                        updateFolder(dbManager.getDb(), folder_id, newFolderName.c_str());
                    } catch (const std::invalid_argument&) {
                        std::cout << "Error: Invalid folder ID. Please provide a valid integer." << std::endl;
                    }
                }
            }
        }
        else if (command == "getn") {
            std::cout << GREEN << "✓ " << RESET;
            getNotes(dbManager.getDb());
        }
        else if (command == "addn") {
            size_t folderIdEnd = args.find(' ');

            if (folderIdEnd == std::string::npos) {
                std::cout << "Error: Folder ID, title, and content required. Usage: addn <folder_id> <title> <content>" << std::endl;
            } else {
                std::string folderIdStr = args.substr(0, folderIdEnd);
                std::string noteArgs = args.substr(folderIdEnd + 1);
                size_t titleEnd = noteArgs.find(' ');

                if (titleEnd == std::string::npos) {
                    std::cout << "Error: Title and content required. Usage: addn <folder_id> <title> <content>" << std::endl;
                } else {
                    std::string title = noteArgs.substr(0, titleEnd);
                    std::string content = noteArgs.substr(titleEnd + 1);

                    if (content.empty()) {
                        std::cout << "Error: Content required. Usage: addn <folder_id> <title> <content>" << std::endl;
                    } else {
                        try {
                            int folder_id = std::stoi(folderIdStr);
                            std::cout << GREEN << "✓ " << RESET;
                            addNote(dbManager.getDb(), folder_id, title.c_str(), content.c_str());
                        } catch (const std::invalid_argument&) {
                            std::cout << "Error: Invalid folder ID. Please provide a valid integer." << std::endl;
                        }
                    }
                }
            }
        }
        else if (command == "updn") {
            size_t noteIdEnd = args.find(' ');

            if (noteIdEnd == std::string::npos) {
                std::cout << "Error: Note ID, title, and content required. Usage: updn <note_id> <new_title> <new_content>" << std::endl;
            } else {
                std::string noteIdStr = args.substr(0, noteIdEnd);
                std::string noteArgs = args.substr(noteIdEnd + 1);
                size_t titleEnd = noteArgs.find(' ');

                if (titleEnd == std::string::npos) {
                    std::cout << "Error: Title and content required. Usage: updn <note_id> <new_title> <new_content>" << std::endl;
                } else {
                    std::string newTitle = noteArgs.substr(0, titleEnd);
                    std::string newContent = noteArgs.substr(titleEnd + 1);

                    if (newContent.empty()) {
                        std::cout << "Error: Content required. Usage: updn <note_id> <new_title> <new_content>" << std::endl;
                    } else {
                        try {
                            int note_id = std::stoi(noteIdStr);
                            std::cout << GREEN << "✓ " << RESET;
                            updateNote(dbManager.getDb(), note_id, newTitle.c_str(), newContent.c_str());
                        } catch (const std::invalid_argument&) {
                            std::cout << "Error: Invalid note ID. Please provide a valid integer." << std::endl;
                        }
                    }
                }
            }
        }
        else if (command == "deln") {
            if (args.empty()) {
                std::cout << "Error: Note ID required. Usage: deln <note_id>" << std::endl;
            } else {
                try {
                    int note_id = std::stoi(args);
                    std::cout << GREEN << "✓ " << RESET;
                    deleteNote(dbManager.getDb(), note_id);
                } catch (const std::invalid_argument&) {
                    std::cout << "Error: Invalid note ID. Please provide a valid integer." << std::endl;
                }
            }
        }
        else if (command == "printf") {
            if (args.empty()) {
                std::cout << "Error: Folder ID required. Usage: printf <folder_id>" << std::endl;
            } else {
                try {
                    int folder_id = std::stoi(args);
                    std::cout << GREEN << "✓ " << RESET;
                    print_folder_content(dbManager.getDb(), folder_id);
                } catch (const std::invalid_argument&) {
                    std::cout << "Error: Invalid folder ID. Please provide a valid integer." << std::endl;
                }
            }
        }
        else {
            std::cout << RED << "✗ Unknown command: " << input << RESET << std::endl;
        }
    }

    return 0;
}