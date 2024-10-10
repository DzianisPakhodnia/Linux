#include <stdio.h>
#include <unistd.h>

extern char **environ;

int main(void) {
    char *uname_args[] = {"uname", "-a", NULL}; // Аргументы для execve
    execve("/bin/uname", uname_args, environ); // Выполнение команды

    // Если execve вернется, значит произошла ошибка
    perror("execve failed"); // Сообщение об ошибке
    return 1; // Код завершения с ошибкой
}
