#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"
#include "utils.h"

void print_usage() {
    printf("Uso: cache_simulator <nsets> <bsize> <assoc> <substituição> <flag_saida> <arquivo_de_entrada>\n");
}

int main(int argc, char *argv[]) {
    if (argc != 7) {
        print_usage();
        return EXIT_FAILURE;
    }

    int nsets = atoi(argv[1]);
    int bsize = atoi(argv[2]);
    int assoc = atoi(argv[3]);
    char *substituicao = argv[4];
    int flag_saida = atoi(argv[5]);
    char *arquivo_de_entrada = argv[6];

    if (nsets <= 0 || bsize <= 0 || assoc <= 0 || (strcmp(substituicao, "R") != 0 && strcmp(substituicao, "F") != 0 && strcmp(substituicao, "L") != 0)) {
        print_usage();
        return EXIT_FAILURE;
    }

    Cache *cache = init_cache(nsets, bsize, assoc, substituicao);
    if (cache == NULL) {
        fprintf(stderr, "Erro ao inicializar a cache.\n");
        return EXIT_FAILURE;
    }

    FILE *file = fopen(arquivo_de_entrada, "rb");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo de entrada.\n");
        free_cache(cache);
        return EXIT_FAILURE;
    }

    process_addresses(file, cache);
    fclose(file);

    print_statistics(cache, flag_saida);
    free_cache(cache);

    return EXIT_SUCCESS;
}