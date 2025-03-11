#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "cache.h"

Cache *create_cache(int n_sets, int bsize, int assoc, char replacement_policy)
{
    Cache *cache = malloc(sizeof(Cache));
    cache->lines = malloc(n_sets * assoc * sizeof(CacheLine));
    for (int i = 0; i < n_sets * assoc; i++)
    {
        cache->lines[i].valid = 0;       // Initialize all entries as invalid
        cache->lines[i].last_access = 0; // Initialize last access time
    }
    cache->n_sets = n_sets;
    cache->bsize = bsize;
    cache->assoc = assoc;
    cache->replacement_policy = replacement_policy;
    cache->hits = 0;
    cache->misses = 0;
    cache->compulsory_misses = 0;
    cache->capacity_misses = 0;
    cache->conflict_misses = 0;
    cache->total_accesses = 0;
    cache->fifo_counters = malloc(n_sets * sizeof(int));
    for (int i = 0; i < n_sets; i++)
    {
        cache->fifo_counters[i] = 0;
    }
    return cache;
}

void free_cache(Cache *cache)
{
    free(cache->lines);
    free(cache->fifo_counters);
    free(cache);
}

void access_cache(Cache *cache, uint32_t address)
{
    int n_bits_offset = log2(cache->bsize);
    int n_bits_index = log2(cache->n_sets);
    uint32_t tag = address >> (n_bits_offset + n_bits_index);
    int index = (address >> n_bits_offset) & ((1 << n_bits_index) - 1);

    int hit = 0;
    for (int i = 0; i < cache->assoc; i++)
    {
        if (cache->lines[index * cache->assoc + i].valid && cache->lines[index * cache->assoc + i].tag == tag)
        {
            hit = 1;
            cache->hits++;
            cache->lines[index * cache->assoc + i].last_access = cache->total_accesses;
            break;
        }
    }

    cache->total_accesses++;

    if (hit)
    {
        return;
    }

    cache->misses++;
    int empty_slot = -1;
    for (int i = 0; i < cache->assoc; i++)
    {
        if (cache->lines[index * cache->assoc + i].valid == 0)
        {
            empty_slot = i;
            break;
        }
    }

    if (empty_slot != -1)
    {
        cache->compulsory_misses++;
        cache->lines[index * cache->assoc + empty_slot].valid = 1;
        cache->lines[index * cache->assoc + empty_slot].tag = tag;
        cache->lines[index * cache->assoc + empty_slot].last_access = cache->total_accesses;
    }
    else
    {
        if (cache->total_accesses <= cache->n_sets * cache->assoc)
        {
            cache->compulsory_misses++;
        }
        else
        {
            if (cache->n_sets == 1)
            {
                cache->capacity_misses++;
            }
            else
            {
                cache->conflict_misses++;
            }
        }

        if (cache->replacement_policy == 'R') // Comparação com 'R' (char)
        {
            int replace_index = rand() % cache->assoc;
            cache->lines[index * cache->assoc + replace_index].tag = tag;
            cache->lines[index * cache->assoc + replace_index].last_access = cache->total_accesses;
        }
        else if (cache->replacement_policy == 'F') // Comparação com 'F' (char)
        {
            int replace_index = cache->fifo_counters[index];
            cache->lines[index * cache->assoc + replace_index].tag = tag;
            cache->lines[index * cache->assoc + replace_index].last_access = cache->total_accesses;
            cache->fifo_counters[index] = (cache->fifo_counters[index] + 1) % cache->assoc;
        }
        else if (cache->replacement_policy == 'L') // Comparação com 'L' (char)
        {
            int lru_index = 0;
            int lru_time = cache->lines[index * cache->assoc].last_access;
            for (int i = 1; i < cache->assoc; i++)
            {
                if (cache->lines[index * cache->assoc + i].last_access < lru_time)
                {
                    lru_index = i;
                    lru_time = cache->lines[index * cache->assoc + i].last_access;
                }
            }
            cache->lines[index * cache->assoc + lru_index].tag = tag;
            cache->lines[index * cache->assoc + lru_index].last_access = cache->total_accesses;
        }
    }
}