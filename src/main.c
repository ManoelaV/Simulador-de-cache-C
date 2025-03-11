#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"
#include "utils.h"

void print_usage()
{
    printf("Uso: cache_simulator <nsets> <bsize> <assoc> <substituição> <flag_saida> <arquivo_de_entrada>\n");
}

void process_addresses(FILE *file, Cache *cache)
{
    uint32_t address;
    uint8_t buffer[4];
    while (fread(buffer, sizeof(uint8_t), 4, file) == 4)
    {
        // Converte de big-endian para little-endian
        address = (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];
        access_cache(cache, address);
    }
}

void print_statistics(Cache *cache, int flag_saida)
{
    if (flag_saida == 0)
    {
        printf("Total de acessos: %d\n", cache->total_accesses);
        printf("Taxa de hits: %.2f\n", (double)cache->hits / cache->total_accesses);
        printf("Taxa de misses: %.2f\n", (double)cache->misses / cache->total_accesses);
        printf("Taxa de misses compulsórios: %.2f\n", (double)cache->compulsory_misses / cache->misses);
        printf("Taxa de misses de capacidade: %.2f\n", (double)cache->capacity_misses / cache->misses);
        printf("Taxa de misses de conflito: %.2f\n", (double)cache->conflict_misses / cache->misses);
    }
    else if (flag_saida == 1)
    {
        printf("%d, %.2f, %.2f, %.2f, %.2f, %.2f\n", cache->total_accesses,
               (double)cache->hits / cache->total_accesses,
               (double)cache->misses / cache->total_accesses,
               (double)cache->compulsory_misses / cache->misses,
               (double)cache->capacity_misses / cache->misses,
               (double)cache->conflict_misses / cache->misses);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 7)
    {
        print_usage();
        return EXIT_FAILURE;
    }

    int nsets = atoi(argv[1]);
    int bsize = atoi(argv[2]);
    int assoc = atoi(argv[3]);
    char *substituicao = argv[4];
    int flag_saida = atoi(argv[5]);
    char *arquivo_de_entrada = argv[6];

    if (nsets <= 0 || bsize <= 0 || assoc <= 0 || (strcmp(substituicao, "R") != 0 && strcmp(substituicao, "F") != 0 && strcmp(substituicao, "L") != 0))
    {
        print_usage();
        return EXIT_FAILURE;
    }

    Cache *cache = create_cache(nsets, bsize, assoc, substituicao[0]);
    ;
    if (cache == NULL)
    {
        fprintf(stderr, "Erro ao inicializar a cache.\n");
        return EXIT_FAILURE;
    }

    printf("Tentando abrir o arquivo: %s\n", arquivo_de_entrada); // Adicionando verificação do caminho do arquivo
    FILE *file = fopen(arquivo_de_entrada, "rb");
    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo de entrada");
        free_cache(cache);
        return EXIT_FAILURE;
    }

    process_addresses(file, cache);
    fclose(file);

    print_statistics(cache, flag_saida);
    free_cache(cache);

    return EXIT_SUCCESS;
}