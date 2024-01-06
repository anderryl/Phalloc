#include <stdio.h>
#include "pspace.h"
#include "bitset.h"
#include "mspacechars.h"
#include <stdlib.h>



int main() {
    /*
    PenaltySpace* pspace = (PenaltySpace*)malloc(sizeof(PenaltySpace));
    psinit(pspace);
    MemorySpace* mspace = (MemorySpace*) malloc(sizeof(MemorySpace));
    msinit(mspace);
    msclose(mspace, 0, 1, 10);
     */

    Bitset* bitset = (Bitset*)malloc(sizeof(Bitset));
    bsinit(bitset, true);
    bsset(bitset, 2, 100, false);
    printf("%x %x %x %x\n", bitset->sets[0], bitset->sets[1], bitset->sets[2], bitset->sets[3]);
    printf("%d\n", bscontiguous(bitset, 2, false));

    return 0;
}
