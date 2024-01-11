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

int head(setbase seg) {
    if (!~seg) {
        return setbits;
    }

    int low = 0;
    int high = setbits;

    for (int i = (high + low) / 2; low <= high; i = (high + low) / 2) {
        int mask = (~0) << (setbits - i);
        if ((seg & mask) != mask)
            high = i - 1;
        else
            low = i + 1;
    }

    return low - 1;
}

int tail(setbase seg) {
    if (!~seg) {
        return setbits;
    }

    int low = 0;
    int high = setbits;

    for (int i = (high + low) / 2; low <= high; i = (high + low) / 2) {
        int mask = ~((~0) << i);
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
            while (!~bitset->sets[++current] && current < setcount - 1);
            return (setbits - secti) +
                    tail(bitset->sets[current]) +
                   setbits * (current - section - 1);
        }
        else
            return tail(bitset->sets[section] >> secti);
    }
    else {
        if (mask == (mask & ~bitset->sets[section])) {
            int current = section;
            while (!bitset->sets[++current] && current < setcount - 1);
            return (setbits - secti) +
                    tail(~bitset->sets[current]) +
                   setbits * (current - section - 1);
        }
        else
            return tail(~bitset->sets[section] >> secti);
    }
}

int bscontiguousreverse(Bitset* bitset, int index, bool state) {
    int section = index / setbits;
    int secti = index % setbits;
    unsigned int mask = (unsigned)~0 >> (setbits - secti);
    printf("%x %d\n", mask, secti);

    if (state) {
        if (mask == (mask & bitset->sets[section])) {
            int current = section;
            while (!~bitset->sets[--current] && current > 0);
            printf("%d %x %d %d\n", head(bitset->sets[current]), bitset->sets[current], current, section);
            return secti +
                   head(bitset->sets[current]) +
                   setbits * (section - current - 1);
        }
        else {
            return head(bitset->sets[section] << (setbits - secti - 1));
        }
    }
    else {
        if (mask == (mask & ~bitset->sets[section])) {
            int current = section;
            while (!bitset->sets[--current] && current > 0);
            return secti +
                    head(~bitset->sets[current]) +
                    setbits * (section - current - 1);
        }
        else {
            return head(~bitset->sets[section] << (setbits - secti - 1));
        }
    }
}