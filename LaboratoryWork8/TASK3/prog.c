#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>  // Добавлено для wait()

void launch_browser() {
    char *args[] = {"xdg-open", "http://www.example.com", NULL};
    execvp(args[0], args);
}

void launch_editor() {
    char *args[] = {"gnome-calendar", NULL};  // Используйте ваш редактор
    execvp(args[0], args);
}

void launch_explorer() {
    char *args[] = {"nautilus", ".", NULL};  // Проводник Nautilus
    execvp(args[0], args);
}

int main() {
    int choice;
    pid_t pid;

    printf("Выберите действие:\n");
    printf("1. Открыть браузер\n");
    printf("2. Открыть текстовый редактор\n");
    printf("3. Открыть проводник\n");
    
    printf("Введите номер действия (1/2/3): ");
    scanf("%d", &choice);

    pid = fork();  // Создание нового процесса

    if (pid == 0) {  // Дочерний процесс
        switch (choice) {
            case 1:
                launch_browser();
                break;
            case 2:
                launch_editor();
                break;
            case 3:
                launch_explorer();
                break;
            default:
                printf("Неверный выбор\n");
                exit(1);
        }
    } else if (pid > 0) {  // Родительский процесс
        wait(NULL);  // Ожидание завершения дочернего процесса
    } else {
        perror("fork failed");
        exit(1);
    }

    return 0;
}
