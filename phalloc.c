//
// Created by Rylie Anderson on 12/22/23.
//

#include "phalloc.h"

void* raw = NULL;
void* base = NULL;
Bitset* flow;
char* space;

void initphalloc() {
    raw = mmap(NULL, (width * depth + 1) * line, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
    base = raw;

    if ((unsigned long)base % line != 0) {
        base += line - ((unsigned long)base % line);
    }

    void* current = base;

    flow = current;
    bsinit(flow, true);

    space = current;
    current += sizeof(char) * bcount;
}

void* phalloc(size_t size) {
    if (base == NULL) {
        initphalloc();
    }

    return NULL;
}

void phree(void* ptr) {

}