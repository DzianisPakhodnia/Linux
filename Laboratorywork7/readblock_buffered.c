#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096  // Размер буфера для чтения/записи

int main(int argc, char **argv) {
    FILE *ifile, *ofile;
    char buffer[BUFFER_SIZE];  // Буфер для данных
    size_t bytesRead;
    long pos = 0;             // Позиция для чтения
    size_t count = 0;         // Количество байт для чтения
    int newlineFlag = 0;      // Флаг для добавления новой строки
    char *inputFile = NULL;   // Входной файл
    char *outputFile = NULL;  // Выходной файл (если указан)

    // Параметры командной строки
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input file> <count> [-o <output file>] [-p <position>] [-n]\n", argv[0]);
        return 1;
    }

    inputFile = argv[1];
    count = abs(atoi(argv[2]));  // Количество байт для чтения

    // Открытие входного файла
    ifile = fopen(inputFile, "rb");
    if (ifile == NULL) {
        fprintf(stderr, "Cannot open input file: %s\n", inputFile);
        return 1;
    }

    // Обработка параметров -o, -p, -n
    for (int i = 3; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            outputFile = argv[++i];
        } else if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            pos = atol(argv[++i]);
        } else if (strcmp(argv[i], "-n") == 0) {
            newlineFlag = 1;
        }
    }

    // Открытие выходного файла (если указан)
    if (outputFile != NULL) {
        ofile = fopen(outputFile, "wb");
        if (ofile == NULL) {
            fprintf(stderr, "Cannot open output file: %s\n", outputFile);
            fclose(ifile);
            return 1;
        }
    } else {
        ofile = stdout;  // По умолчанию вывод в стандартный поток (экран)
    }

    // Установка позиции чтения
    fseek(ifile, pos, SEEK_SET);

    // Чтение данных из входного файла и запись в выходной
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, ifile)) > 0 && count > 0) {
        size_t bytesToWrite = (bytesRead > count) ? count : bytesRead;
        fwrite(buffer, 1, bytesToWrite, ofile);
        count -= bytesToWrite;
    }

    // Добавление новой строки, если флаг установлен
    if (newlineFlag) {
        fputc('\n', ofile);
    }

    // Закрытие файлов
    fclose(ifile);
    if (ofile != stdout) {
        fclose(ofile);
    }

    return 0;
}

