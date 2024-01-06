//
// Created by Rylie Anderson on 1/5/24.
//

#include "mspace.h"

void msinit(MemorySpace* space) {
    bsinit(&space->bins, false);
    bsinit(&space->flow, false);
}

short mslength(MemorySpace* space, short x, short y) {
    int len = bscontiguous(&space->bins, y * width + x, false);
    if (len > (short)~0) {
        return ~0;
    }
    return (short)len;
}

void msopen(MemorySpace* space, short x, short y) {
    int index = y * width + x;
    int len = bscontiguous(&space->flow, index, true);
    bsset(&space->flow, index, len, false);
    bsset(&space->bins, index, len + 1, false);
}

void msclose(MemorySpace* space, short x, short y, short length) {
    int index = y * width + x;
    bsset(&space->flow, index, length - 1, true);
    bsset(&space->bins, index, length, true);
}