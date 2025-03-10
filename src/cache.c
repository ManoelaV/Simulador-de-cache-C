#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cache.h"

typedef struct {
    unsigned int *tags;
    int *valid;
    int hits;
    int misses;
    int compulsory_misses;
    int capacity_misses;
    int conflict_misses;
    int total_accesses;
} Cache;

Cache* init_cache(int nsets, int assoc) {
    Cache *cache = malloc(sizeof(Cache));
    cache->tags = malloc(nsets * assoc * sizeof(unsigned int));
    cache->valid = malloc(nsets * assoc * sizeof(int));
    for (int i = 0; i < nsets * assoc; i++) {
        cache->valid[i] = 0; // Initialize all entries as invalid
    }
    cache->hits = 0;
    cache->misses = 0;
    cache->compulsory_misses = 0;
    cache->capacity_misses = 0;
    cache->conflict_misses = 0;
    cache->total_accesses = 0;
    return cache;
}

void free_cache(Cache *cache) {
    free(cache->tags);
    free(cache->valid);
    free(cache);
}

void access_cache(Cache *cache, unsigned int address, int nsets, int bsize, int assoc, char *replacement_policy) {
    int n_bits_offset = log2(bsize);
    int n_bits_index = log2(nsets);
    unsigned int tag = address >> (n_bits_offset + n_bits_index);
    int index = (address >> n_bits_offset) & ((1 << n_bits_index) - 1);
    
    int hit = 0;
    for (int i = 0; i < assoc; i++) {
        if (cache->valid[index * assoc + i] && cache->tags[index * assoc + i] == tag) {
            hit = 1;
            cache->hits++;
            break;
        }
    }

    cache->total_accesses++;

    if (hit) {
        return;
    }

    cache->misses++;
    if (cache->valid[index * assoc] == 0) {
        cache->compulsory_misses++;
        cache->valid[index * assoc] = 1;
        cache->tags[index * assoc] = tag;
    } else {
        // Handle capacity and conflict misses
        int empty_slot = -1;
        for (int i = 0; i < assoc; i++) {
            if (cache->valid[index * assoc + i] == 0) {
                empty_slot = i;
                break;
            }
        }

        if (empty_slot != -1) {
            cache->valid[index * assoc + empty_slot] = 1;
            cache->tags[index * assoc + empty_slot] = tag;
        } else {
            // Implement replacement policy
            if (strcmp(replacement_policy, "R") == 0) {
                // Random replacement
                int replace_index = rand() % assoc;
                cache->tags[index * assoc + replace_index] = tag;
                cache->conflict_misses++;
            } else if (strcmp(replacement_policy, "F") == 0) {
                // FIFO replacement
                // For simplicity, we will replace the first entry
                cache->tags[index * assoc] = tag;
                cache->conflict_misses++;
            } else if (strcmp(replacement_policy, "L") == 0) {
                // LRU replacement
                // Implement LRU logic here
                // For simplicity, we will replace the first entry
                cache->tags[index * assoc] = tag;
                cache->conflict_misses++;
            }
        }
    }
}