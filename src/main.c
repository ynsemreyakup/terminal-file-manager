#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "directory_ops.h"
#include "file_operations.h"
#include "logger.h"  // logger.h header'ını ekleyin, .c dosyasını değil.
#include "permissions.h"  // permissions.h header'ını ekleyin, .c dosyasını değil.

void show_menu() {
    printf("\n----- File and Directory Operations -----\n");
    printf("1. List Directory\n");
    printf("2. Create Directory\n");
    printf("3. Delete Directory\n");
    printf("4. Create File\n");
    printf("5. Delete File\n");
    printf("6. Read File\n");
    printf("7. Write to File\n");
    printf("8. Move File or Directory\n");
    printf("9. Get File Info\n");
    printf("10. Copy File\n");
    printf("11. Change Permissions\n");
    printf("0. Exit\n");
    printf("-----------------------------------------\n");
}

int main() {
    int choice;
    char path[1024], filename[1024], content[1024], destination[1024];
    mode_t mode;

    while (1) {
        show_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // to consume newline left by scanf

        switch (choice) {
            case 1:
                printf("Enter directory path: ");
                fgets(path, sizeof(path), stdin);
                path[strcspn(path, "\n")] = 0;  // Remove newline character
                list_directory(path);
                log_to_file("List Directory", path);
                break;
            
            case 2:
                printf("Enter directory name to create: ");
                fgets(path, sizeof(path), stdin);
                path[strcspn(path, "\n")] = 0;  // Remove newline character
                create_directory(path);
                log_to_file("Create Directory", path);
                break;

            case 3:
                printf("Enter directory name to delete: ");
                fgets(path, sizeof(path), stdin);
                path[strcspn(path, "\n")] = 0;  // Remove newline character
                delete_directory(path);
                log_to_file("Delete Directory", path);
                break;

            case 4:
                printf("Enter file name to create: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0;  // Remove newline character
                create_file(filename);
                log_to_file("Create File", filename);
                break;

            case 5:
                printf("Enter file name to delete: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0;  // Remove newline character
                delete_file(filename);
                log_to_file("Delete File", filename);
                break;

            case 6:
                printf("Enter file name to read: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0;  // Remove newline character
                read_file(filename);
                log_to_file("Read File", filename);
                break;

            case 7:
                printf("Enter file name to write to: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0;  // Remove newline character
                printf("Enter content to write: ");
                fgets(content, sizeof(content), stdin);
                content[strcspn(content, "\n")] = 0;  // Remove newline character
                write_file(filename, content);
                log_to_file("Write to File", filename);
                break;

            case 8:
                printf("Enter source file or directory: ");
                fgets(path, sizeof(path), stdin);
                path[strcspn(path, "\n")] = 0;  // Remove newline character
                printf("Enter destination: ");
                fgets(destination, sizeof(destination), stdin);
                destination[strcspn(destination, "\n")] = 0;  // Remove newline character
                move_file_or_directory(path, destination);
                log_to_file("Move File/Directory", path);
                break;

            case 9:
                printf("Enter file name to get info: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0;  // Remove newline character
                get_file_info(filename);
                log_to_file("Get File Info", filename);
                break;

            case 10:
                printf("Enter source file: ");
                fgets(path, sizeof(path), stdin);
                path[strcspn(path, "\n")] = 0;  // Remove newline character
                printf("Enter destination file: ");
                fgets(destination, sizeof(destination), stdin);
                destination[strcspn(destination, "\n")] = 0;  // Remove newline character
                copy_file(path, destination);
                log_to_file("Copy File", path);
                break;

            case 11:
                printf("Enter file or directory path to change permissions: ");
                fgets(path, sizeof(path), stdin);
                path[strcspn(path, "\n")] = 0;  // Remove newline character
                printf("Enter new permissions (e.g., 755): ");
                scanf("%o", &mode); // Use %o for octal input
                change_permissions(path, mode);
                log_to_file("Change Permissions", path);
                break;

            case 0:
                printf("Exiting program...\n");
                log_to_file("Exit", "User exited the program");
                return 0;

            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}
