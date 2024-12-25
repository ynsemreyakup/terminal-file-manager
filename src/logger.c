#include <stdio.h>
#include <time.h>
#include <string.h>

// Log dosyasına yazma fonksiyonu
void log_to_file(const char *operation, const char *details) {
    FILE *log_file = fopen("operation_log.txt", "a");  // Log dosyasını ekleme modunda aç
    if (log_file == NULL) {
        perror("Failed to open log file");
        return;
    }

    // Şu anki zamanı al
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    char time_buffer[20];
    strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", tm_info);

    // Log bilgilerini dosyaya yaz
    fprintf(log_file, "[%s] %s: %s\n", time_buffer, operation, details);

    fclose(log_file);
}
