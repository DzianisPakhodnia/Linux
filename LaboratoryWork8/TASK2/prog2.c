#include <stdio.h>
#include <unistd.h>

int main(void) {
    char *newprog_args[] = { "Tee-hee!", "new-prog_arg1", "newprog_arg2", NULL };
    char *newprog_envp[] = { "USER=abrakadabra", "HOME=/home/abrakadabra", NULL };

    printf("Old PID: %d\n", getpid());

    // Исправлено имя массива окружения
    execve("./newprog", newprog_args, newprog_envp);

    // Если execve вернется, значит произошла ошибка
    perror("execve failed"); // Сообщение об ошибке
    return 1; // Код завершения с ошибкой
}
