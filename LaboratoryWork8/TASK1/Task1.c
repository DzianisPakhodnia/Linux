#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define NUM_ITERATIONS 5

int main() {
    pid_t pid;

    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pid = fork(); // Создаем дочерний процесс

        if (pid < 0) {
            // Ошибка при fork
            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // Дочерний процесс
            sleep(1); // Задержка перед выполнением команды
            execlp("ps", "ps", NULL); // Выполняем команду ps
            perror("execlp failed"); // Если execlp не сработал
            exit(EXIT_FAILURE);
        } else {
            // Родительский процесс
            wait(NULL); // Ждем завершения дочернего процесса
        }
    }

    sleep(5); // Родительский процесс ждет 5 секунд перед завершением
    printf("Родительский процесс завершился.\n");
    return 0;
}
