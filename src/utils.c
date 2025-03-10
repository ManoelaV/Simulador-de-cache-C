#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void read_addresses(const char *filename, unsigned int **addresses, size_t *count) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    *count = ftell(file) / sizeof(unsigned int);
    fseek(file, 0, SEEK_SET);

    *addresses = malloc(*count * sizeof(unsigned int));
    if (*addresses == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(*addresses, sizeof(unsigned int), *count, file);
    fclose(file);
}

void free_addresses(unsigned int *addresses) {
    free(addresses);
}