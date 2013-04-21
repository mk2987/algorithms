#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define NUM_ELTS 100
#define MAX_ELT_VALUE 100
#define FILENAME "unsorted_array.h"

int main()
{
    int i;
    FILE *file;

    file = fopen(FILENAME, "w");
    if (!file) {
        perror("Failed to open file to write unsorted array\n");
        exit(1);
    }

    fprintf(file, "#ifndef __UNSORTED_ARRAY_H_\n");
    fprintf(file, "#define __UNSORTED_ARRAY_H_\n");
    fprintf(file, "\n");

    fprintf(file, "int unsorted_array = [ ");

    srand(42);

    for (i = 0; i < NUM_ELTS; i++) {
        fprintf(file, "%d, ", (int)((float)rand() / RAND_MAX * MAX_ELT_VALUE));
    }

    fprintf(file, "]\n\n");

    fprintf(file, "#endif /* __UNSORTED_ARRAY_H_ */\n");
    fclose(file);

    return 0;
}
