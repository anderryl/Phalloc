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

typedef struct {
    bool before;
    bool after;
    short length;
} EdgeState;

void msinit(MemorySpace* space);

short mslength(MemorySpace* space, short x, short y);

EdgeState msopen(MemorySpace* space, short x, short y);

EdgeState msclose(MemorySpace* space, short x, short y, short length);

bool msget(MemorySpace* space, short x, short y);

void msprint(MemorySpace* space);

short msnext(MemorySpace* space, short x, short y);

short msprev(MemorySpace* space, short x, short y);

#endif //PHALLOCATE_MSPACE_H
