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

EdgeState msopen(MemorySpace* space, short x, short y) {
    int index = y * width + x;
    int len = bscontiguous(&space->flow, index, true) + 1;
    bsset(&space->flow, index, len - 1, false);
    bsset(&space->bins, index, len, false);
    return (EdgeState){
            index > 0 ? bsget(&space->bins, index - 1) : false,
            index + len < bcount - 1 ? bsget(&space->bins, index + len) : false,
            len
    };
}

EdgeState msclose(MemorySpace* space, short x, short y, short length) {
    int index = y * width + x;
    bsset(&space->flow, index, length - 1, true);
    bsset(&space->bins, index, length, true);
    return (EdgeState){
        index > 0 ? bsget(&space->bins, index - 1) : false,
        index + length < bcount - 1 ? bsget(&space->bins, index + length) : false,
        length
    };
}

void msprint(MemorySpace* space) {
    printf("\\\t");
    int sects = width / setbits + (width % setbits != 0 ? 1 : 0);
    for (int x = sects - 1; x >= 0; x--) {
        printf(setbits * x < 1000 ? "%d\t\t\t" : "%d\t\t", setbits * x);
    }

    printf("\n");

    for (int y = 0; y < depth; y++) {
        printf("%d\t", y);
        for (int x = sects - 1; x >= 0; x--) {
            printf("%08x\t", space->bins.sets[x + y * sects]);
        }
        printf("\n");
    }
}

bool msget(MemorySpace* space, short x, short y) {
    return bsget(&space->bins, x + y * width);
}

short msnext(MemorySpace* space, short x, short y) {
    int index = x + y * width;
    int len = bscontiguous(&space->flow, index, true) + 1;
    int newindex = len + index;
    return (short)(newindex + bscontiguous(&space->bins, newindex, false));
}

short msprev(MemorySpace* space, short x, short y) {
    int index = x + y * width;
    int len = bscontiguousreverse(&space->bins, index, false);
    return (short)(index - len);
}