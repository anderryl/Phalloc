//
// Created by Rylie Anderson on 12/27/23.
//

#ifndef PHALLOCATE_MSPACECHARS_H
#define PHALLOCATE_MSPACECHARS_H

#include "constants.h"
#include <string.h>

#define wall ((width / 2) + (width % 2))
#define mssize (wall * depth)

typedef struct {
    char bins[wall * depth];
} MemorySpace;

void msinit(MemorySpace* space);

short mslength(MemorySpace* space, short x, short y);

void msopen(MemorySpace* space, short x, short y, short length);

void msclose(MemorySpace* space, short x, short y, short length);

#endif //PHALLOCATE_MSPACECHARS_H
