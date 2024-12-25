#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

// Dosya/dizin izinlerini değiştirme fonksiyonu
int change_permissions(const char *path, mode_t mode) {
    if (chmod(path, mode) == -1) {
        perror("Permission change failed");
        return -1;  // Hata durumunda -1 döner
    }
    return 0;  
}
