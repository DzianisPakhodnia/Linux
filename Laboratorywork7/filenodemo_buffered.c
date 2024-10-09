#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Too few arguments\n");
        return 1;
    }

    FILE *ifile = fopen(argv[1], "rb");
    if (ifile == NULL) {
        fprintf(stderr, "Cannot open file: %s\n", argv[1]);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    size_t nbytes;

    while ((nbytes = fread(buffer, 1, BUFFER_SIZE, ifile)) > 0) {
        fwrite(buffer, 1, nbytes, stdout);
    }

    fclose(ifile);
    return 0;
}

