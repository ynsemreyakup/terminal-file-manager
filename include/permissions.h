#ifndef PERMISSIONS_H
#define PERMISSIONS_H

#include <sys/stat.h>  // mode_t için gerekli

// İzin değiştirme fonksiyonunun prototipi
int change_permissions(const char *path, mode_t mode);

#endif // PERMISSIONS_H
