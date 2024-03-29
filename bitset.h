//
// Created by Rylie Anderson on 12/21/23.
//

#ifndef PHALLOC_BITSET_H
#define PHALLOC_BITSET_H

#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "constants.h"

#define setbase int
#define setbits 32
#define setcount (width * depth) / setbits + ((width * depth) % setbits > 0 ? 1 : 0)

typedef struct {
    setbase sets[setcount];
} Bitset;

void bsset(Bitset* bitset, int index, int len, bool value);

bool bsget(Bitset* bitset, int index);

int bscontiguous(Bitset* bitset, int index, bool state);

int bscontiguousreverse(Bitset* bitset, int index, bool state);

void bsinit(Bitset * ptr, bool value);

#endif //PHALLOC_BITSET_H
