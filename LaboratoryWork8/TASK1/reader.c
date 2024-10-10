#include <stdio.h>
#include <stdlib.h>

int main() {
    char buffer[256];
    FILE *file = fopen("output.txt", "r");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return EXIT_FAILURE;
    }
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    fclose(file);
    return EXIT_SUCCESS;
}
