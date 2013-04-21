#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "main.h"

int main()
{
    int i;
    FILE *file;

    file = fopen(FILENAME, "w");
    if (!file) {
        perror("Failed to open file to write unsorted array\n");
        exit(1);
    }

    fprintf(file, "int g_unsorted_array[] = { ");

    srand(42);

    for (i = 0; i < NUM_ELTS; i++) {
        fprintf(file, "%d, ", (int)((float)rand() / RAND_MAX * MAX_ELT_VALUE));
    }

    fprintf(file, "};\n");

    fclose(file);

    return 0;
}
