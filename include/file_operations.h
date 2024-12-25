#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <sys/types.h>

int create_file(const char *filename);
int delete_file(const char *filename);
int read_file(const char *filename);
int write_file(const char *filename, const char *content);
int move_file_or_directory(const char *source, const char *destination);
int get_file_info(const char *filename);
int copy_file(const char *source, const char *destination);

#endif // FILE_OPERATIONS_H
