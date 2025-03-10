#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

void read_addresses(const char *filename, uint32_t **addresses, size_t *count);
void free_addresses(uint32_t *addresses);
uint32_t big_endian_to_uint32(const uint8_t *bytes);

#endif // UTILS_H