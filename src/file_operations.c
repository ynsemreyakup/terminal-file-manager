#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

// Dosya oluşturma
int create_file(const char *filename) {
    int fd = creat(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        perror("creat");
        return -1;
    }

    printf("File '%s' created successfully.\n", filename);
    close(fd);
    return 0;
}

// Dosya silme
int delete_file(const char *filename) {
    if (unlink(filename) == -1) {
        perror("unlink");
        return -1;
    }

    printf("File '%s' deleted successfully.\n", filename);
    return 0;
}

// Dosya okuma
int read_file(const char *filename) {
    char buffer[1024];
    int fd = open(filename, O_RDONLY);

    if (fd == -1) {
        perror("open");
        return -1;
    }

    printf("Contents of '%s':\n", filename);
    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        printf("%s", buffer);
    }

    if (bytes_read == -1) {
        perror("read");
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}

// Dosya yazma
int write_file(const char *filename, const char *content) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    if (fd == -1) {
        perror("open");
        return -1;
    }

    if (write(fd, content, strlen(content)) == -1) {
        perror("write");
        close(fd);
        return -1;
    }

    printf("Content written to '%s' successfully.\n", filename);
    close(fd);
    return 0;
}

// Dosya yeniden adlandırma (veya taşıma)
int move_file_or_directory(const char *source, const char *destination) {
    if (rename(source, destination) == -1) {
        perror("rename");
        return -1;
    }

    printf("Successfully moved '%s' to '%s'.\n", source, destination);
    return 0;
}

// Dosya bilgilerini alma
int get_file_info(const char *filename) {
    struct stat file_info;

    if (stat(filename, &file_info) == -1) {
        perror("stat");
        return -1;
    }

    printf("\nFile: %s\n", filename);
    printf("Size: %ld bytes\n", file_info.st_size);
    printf("Permissions: ");
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
    printf("Last modified: %s", ctime(&file_info.st_mtime));

    return 0;
}

// Dosya kopyalama
int copy_file(const char *source, const char *destination) {
    int src_fd = open(source, O_RDONLY);
    if (src_fd == -1) {
        perror("open source");
        return -1;
    }

    int dest_fd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (dest_fd == -1) {
        perror("open destination");
        close(src_fd);
        return -1;
    }

    char buffer[4096];
    ssize_t bytes_read;
    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
        if (write(dest_fd, buffer, bytes_read) == -1) {
            perror("write");
            close(src_fd);
            close(dest_fd);
            return -1;
        }
    }

    if (bytes_read == -1) {
        perror("read");
    }

    close(src_fd);
    close(dest_fd);
    printf("File '%s' copied to '%s' successfully.\n", source, destination);
    return 0;
}
