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
    bsinit(bitset, false);
    bssetsection(bitset, 2, 10, true);
    printf("%d\n", bscontiguous(bitset, 3));

    return 0;
}
