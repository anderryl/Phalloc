//
// Created by Rylie Anderson on 12/21/23.
//

#include "bitset.h"

void bsinit(Bitset* ptr, bool value) {
    memset(ptr, value ? ~0 : 0, sizeof(Bitset));
}

void bsset(Bitset* bitset, int index, bool value) {
    int section = index / setbits;
    int mask = 1 << (index % setbits);

    if (!value) {
        bitset->sets[section] &= ~mask;
    }

    else {
        bitset->sets[section] |= mask;
    }
}

/// Todo: Optimize
void bssetsection(Bitset* bitset, int index, int len, bool value) {
    for (int i = index; i < index + len; i++) {
        bsset(bitset, i, value);
    }
}

bool bsget(Bitset* bitset, int index) {
    int section = index / setbits;
    int mask = 1 << (index % setbits);
    return bitset->sets[section] & mask;
}

int head(setbase seg, int min) {
    if (!~seg) {
        return setbits;
    }

    int mask;

    if (min) {
        mask = (~0 >> (setbits - min));
        if ((seg & mask) != mask) {
            return 0;
        }
    }

    int low = min;
    int high = setbits;

    for (int i = (high + low) / 2; low <= high; i = (high + low) / 2) {
        mask = ~((~0) << i);
        printf("Mask  %x %x %d\n", seg, mask, i);
        if ((seg & mask) != mask) {
            high = i - 1;
        }
        else {
            low = i + 1;
        }

        printf("%d %d\n", low, high);
    }

    return low - 1;
}

int tail(setbase seg, int min) {
    if (!~seg) {
        return setbits;
    }

    int mask;

    if (min > 0) {
        mask = (~0 << (setbits - min));
        printf("%x\n", mask);
        if ((seg & mask) != mask) {
            return 0;
        }
    }

    int low = min;
    int high = setbits;

    for (int i = (high + low) / 2; low <= high; i = (high + low) / 2) {
        mask = ~0 << (setbits - i);
        printf("%x %x\n", mask, mask & seg);
        if ((seg & mask) != mask) {
            high = i - 1;
        }
        else {
            low = i + 1;
        }

        printf("%d %d\n", low, high);
    }

    return low - 1;
}

int bscontiguous(Bitset* bitset, int index) {
    int section = index / setbits;
    int secti = index % setbits;
    int mask = ~0 >> (setbits - secti);
    printf("%x\n", bitset->sets[section]);
    if (mask == (mask & bitset->sets[section])) {
        int current = section;
        while (!~bitset->sets[++current]);
        return secti + tail(bitset->sets[current], 0) + setbits * (current - section - 1);
    }
    else {
        printf("%x %d\n", bitset->sets[section] >> secti, secti);
        return head(bitset->sets[section] >> secti, 0);
    }
}