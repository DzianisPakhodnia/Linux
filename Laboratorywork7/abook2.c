#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/uio.h>

#define NAME_LENGTH 50
#define PHONE_LENGTH 30
#define EMAIL_LENGTH 30
#define ABOOK_FNAME "abook"

// Буферы для хранения данных
char name_buffer[NAME_LENGTH];
char phone_buffer[PHONE_LENGTH];
char email_buffer[EMAIL_LENGTH];

// Структура для записи записей в адресную книгу
struct iovec ab_entry[3];

// Функция для добавления записи
void abook_add() {
    printf("Введите имя: ");
    scanf("%s", name_buffer);
    printf("Введите номер телефона: ");
    scanf("%s", phone_buffer);
    printf("Введите email: ");
    scanf("%s", email_buffer);

    ab_entry[0].iov_base = name_buffer;
    ab_entry[0].iov_len = NAME_LENGTH;
    ab_entry[1].iov_base = phone_buffer;
    ab_entry[1].iov_len = PHONE_LENGTH;
    ab_entry[2].iov_base = email_buffer;
    ab_entry[2].iov_len = EMAIL_LENGTH;

    int fd = open(ABOOK_FNAME, O_WRONLY | O_CREAT | O_APPEND, 0640);
    if (fd == -1) {
        perror("Не удалось открыть файл для записи");
        exit(1);
    }

    if (writev(fd, ab_entry, 3) == -1) {
        perror("Ошибка записи");
        close(fd);
        exit(1);
    }

    close(fd);
}

// Функция для удаления записи
void abook_delete() {
    char find_buffer[NAME_LENGTH];
    printf("Введите имя для удаления: ");
    scanf("%s", find_buffer);

    ab_entry[0].iov_base = name_buffer;
    ab_entry[0].iov_len = NAME_LENGTH;
    ab_entry[1].iov_base = phone_buffer;
    ab_entry[1].iov_len = PHONE_LENGTH;
    ab_entry[2].iov_base = email_buffer;
    ab_entry[2].iov_len = EMAIL_LENGTH;

    int fd = open(ABOOK_FNAME, O_RDONLY);
    if (fd == -1) {
        perror("Не удалось открыть файл для чтения");
        exit(1);
    }

    FILE *temp = fopen("abook_temp", "w");
    if (!temp) {
        perror("Ошибка создания временного файла");
        close(fd);
        exit(1);
    }

    while (readv(fd, ab_entry, 3) > 0) {
        if (strcmp(name_buffer, find_buffer) != 0) {
            fprintf(temp, "%s %s %s\n", name_buffer, phone_buffer, email_buffer);
        }
    }

    close(fd);
    fclose(temp);
    remove(ABOOK_FNAME);
    rename("abook_temp", ABOOK_FNAME);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Использование: %s [add|delete]\n", argv[0]);
        exit(1);
    }

    if (strcmp(argv[1], "add") == 0) {
        abook_add();
    } else if (strcmp(argv[1], "delete") == 0) {
        abook_delete();
    } else {
        fprintf(stderr, "Неизвестная команда: %s\n", argv[1]);
        exit(1);
    }

    return 0;
}

