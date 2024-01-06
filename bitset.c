//
// Created by Rylie Anderson on 12/21/23.
//

#include "bitset.h"

void bsinit(Bitset* ptr, bool value) {
    memset(ptr, value ? ~0 : 0, sizeof(Bitset));
}

void bsset(Bitset* bitset, int index, int len, bool value) {
    int section = index / setbits;
    int final = (index + len) / setbits;

    if (value) {
        int start = ~0 << (index % setbits);
        int end = ~(~0 << ((index + len) % setbits));
        if (section != final) {
            bitset->sets[section++] |= start;
            while (section < final) bitset->sets[section++] = ~0;
            bitset->sets[section] |= end;
        }
        else
            bitset->sets[section] |= start & end;
    }
    else {
        int start = ~(~0 << (index % setbits));
        int end = ~0 << ((index + len) % setbits);
        if (section != final) {
            bitset->sets[section++] &= start;
            while (section < final) bitset->sets[section++] = 0;
            bitset->sets[section] &= end;
        }
        else
            bitset->sets[section] &= start | end;
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
        if ((seg & mask) != mask)
            return 0;
    }

    int low = min;
    int high = setbits;

    for (int i = (high + low) / 2; low <= high; i = (high + low) / 2) {
        mask = ~((~0) << i);
        if ((seg & mask) != mask)
            high = i - 1;
        else
            low = i + 1;
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
        if ((seg & mask) != mask)
            return 0;
    }

    int low = min;
    int high = setbits;

    for (int i = (high + low) / 2; low <= high; i = (high + low) / 2) {
        mask = ~0 << (setbits - i);
        if ((seg & mask) != mask)
            high = i - 1;
        else
            low = i + 1;
    }

    return low - 1;
}

int bscontiguous(Bitset* bitset, int index, bool state) {
    int section = index / setbits;
    int secti = index % setbits;
    int mask = ~0 << secti;

    if (state) {
        if (mask == (mask & bitset->sets[section])) {
            int current = section;
            while (!~bitset->sets[++current]);
            return (setbits - secti) +
                   head(bitset->sets[current], 0) +
                   setbits * (current - section - 1);
        }
        else
            return head(bitset->sets[section] >> secti, 0);
    }
    else {
        if (mask == (mask & ~bitset->sets[section])) {
            int current = section;
            while (!bitset->sets[++current]);
            return (setbits - secti) +
                   head(~bitset->sets[current], 0) +
                   setbits * (current - section - 1);
        }
        else
            return head(~bitset->sets[section] >> secti, 0);
    }
}