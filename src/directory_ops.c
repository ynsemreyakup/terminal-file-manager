#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

// Klasör içeriğini listeleme
void list_directory(const char *path) {
    struct dirent *entry;
    DIR *dp = opendir(path);

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    printf("Contents of directory '%s':\n", path);
    printf("------------------------------------------------------------\n");
    printf("%-25s %-10s %-10s\n", "Name", "Size (bytes)", "Permissions");

    while ((entry = readdir(dp)) != NULL) {
        char full_path[1024];
        struct stat file_info;

        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (stat(full_path, &file_info) == -1) {
            perror("stat");
            continue;
        }

        printf("%-25s ", entry->d_name);
        printf("%-10ld ", file_info.st_size);
        printf((S_ISDIR(file_info.st_mode)) ? "d" : "-");
        printf((file_info.st_mode & S_IRUSR) ? "r" : "-");
        printf((file_info.st_mode & S_IWUSR) ? "w" : "-");
        printf((file_info.st_mode & S_IXUSR) ? "x" : "-");
        printf((file_info.st_mode & S_IRGRP) ? "r" : "-");
        printf((file_info.st_mode & S_IWGRP) ? "w" : "-");
        printf((file_info.st_mode & S_IXGRP) ? "x" : "-");
        printf((file_info.st_mode & S_IROTH) ? "r" : "-");
        printf((file_info.st_mode & S_IWOTH) ? "w" : "-");
        printf((file_info.st_mode & S_IXOTH) ? "x" : "-");
        printf("\n");
    }

    closedir(dp);
}

// Klasör oluşturma
int create_directory(const char *dirname) {
    if (mkdir(dirname, 0755) == -1) {
        perror("mkdir");
        return -1;
    }

    printf("Directory '%s' created successfully.\n", dirname);
    return 0;
}

// Klasör silme
int delete_directory(const char *dirname) {
    if (rmdir(dirname) == -1) {
        perror("rmdir");
        return -1;
    }

    printf("Directory '%s' deleted successfully.\n", dirname);
    return 0;
}
