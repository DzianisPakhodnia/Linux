#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return EXIT_FAILURE;
    }
    fprintf(file, "Привет из процесса записи!\n");
    fclose(file);
    return EXIT_SUCCESS;
}
