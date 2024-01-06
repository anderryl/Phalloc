//
// Created by Rylie Anderson on 12/28/23.
//

#ifndef PHALLOCATE_MSPACE_H
#define PHALLOCATE_MSPACE_H

#include "bitset.h"

typedef struct {
    Bitset bins;
    Bitset flow;
} MemorySpace;

void msinit(MemorySpace* space);

short mslength(MemorySpace* space, short x, short y);

void msopen(MemorySpace* space, short x, short y);

void msclose(MemorySpace* space, short x, short y, short length);

#endif //PHALLOCATE_MSPACE_H
