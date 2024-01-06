//
// Created by Rylie Anderson on 12/13/23.
//

#ifndef PHALLOC_PHALLOC_H
#define PHALLOC_PHALLOC_H

#include "constants.h"
#include "bitset.h"
#include <sys/mman.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * Allocates a cache aligned memory block of the specified size from the heap
 * @param size size in bytes
 * @return void pointer to beginning of memory block
 */
void* phalloc(size_t size);

/**
 * De-Allocates a memory block previously allocated by phalloc
 * @param ptr pointer to the beginning of the block to be freed
 */
void phree(void* ptr);

#endif //PHALLOC_PHALLOC_H
