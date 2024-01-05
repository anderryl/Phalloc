//
// Created by Rylie Anderson on 12/28/23.
//
/*
#include "mspace.h"

#define woffset (width % 2)
#define get(space, x, y)        ((space->bins[(x / 2) + y * wall] >> (4 * !(x % 2))) & 0x0F)
#define set(space, x, y, val)   char* spot = &space->bins[(x / 2) + wall * y];\
                                char offset = (4 * (x % 2));\
                                *spot &= 0xF0 >> offset;\
                                *spot |= (val) << offset

void msinit(MemorySpace* space) {
    memset(space->bins, 0, mssize * sizeof(char));
}

short mslength(MemorySpace* space, short x, short y) {
    short xi = x;
    short yi = y;
    char i = get(space, x, y);
    while (i == 0x0F) {
        x += i;
        if (x >= width) {
            x -= width;
            y ++;
        }

        i = get(space, x, y);
    }

    i += get(space, x, y);
    if (x >= width) {
        x -= width;
        y ++;
    }

    return (x - xi) + (y - yi) * width;
}

void msopen(MemorySpace* space, short x, short y, short length) {

}

void msclose(MemorySpace* space, short x, short y, short length) {
    short current = x / 2 + wall * y;
    short backtrack = current - 1;
    short count = 0x21;

    if (x % 2) {
        space->bins[current] = 0x01;
        length--;
        current++;
        count = 0x32;
    }

    short threshold = current + length / 2;
    while (current < threshold) {
        space->bins[current] = 0;
        current++;
    }

    if (length % 2 != x % 2) {
        space->bins[current] &= 0x0F;
    }

    for (; backtrack >= 0 && count <= 0xFE; count += 0x22) {
        if (!(space->bins[backtrack] & 0x0F)) {
            return;
        }
        else if (!(space->bins[backtrack] & 0xF0)) {
            space->bins[backtrack] = count & 0x0F;
            return;
        }

        space->bins[backtrack] = count;
        backtrack--;
    }

    if (backtrack >= 0 && count != 0xFE + 0x22 && space->bins[backtrack] & 0x0F) {
        space->bins[backtrack] = 0x0F;
    }
}
 */