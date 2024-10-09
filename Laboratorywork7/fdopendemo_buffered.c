#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096  // Размер буфера

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    // Открываем файл с правами на чтение
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Преобразуем файловый дескриптор в поток данных
    FILE *file = fdopen(fd, "r");
    if (file == NULL) {
        perror("fdopen");
        close(fd);
        return 1;
    }

    // Буфер для чтения данных
    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    // Чтение данных из файла и вывод в стандартный поток вывода (stdout)
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }

    // Закрываем поток и дескриптор файла
    fclose(file);  // Закрывает и поток, и файловый дескриптор
    return 0;
}

