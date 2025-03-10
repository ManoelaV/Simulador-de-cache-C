#ifndef CACHE_H
#define CACHE_H

#include <stdint.h>

// Estruturas para a simulação da cache
typedef struct {
    uint32_t tag;
    int valid;
} CacheLine;

typedef struct {
    CacheLine *lines;
    int n_sets;
    int bsize;
    int assoc;
    char replacement_policy; // 'R' para Random, 'F' para FIFO, 'L' para LRU
    int hits;
    int misses;
    int compulsory_misses;
    int capacity_misses;
    int conflict_misses;
} Cache;

// Funções para manipulação da cache
Cache* create_cache(int n_sets, int bsize, int assoc, char replacement_policy);
void access_cache(Cache *cache, uint32_t address);
void free_cache(Cache *cache);
void print_cache_stats(Cache *cache, int total_accesses, int flag_saida);

#endif // CACHE_H