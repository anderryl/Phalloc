#include <stdio.h>
#include "pspace.h"
#include "mspace.h"
#include "bitset.h"
#include <stdlib.h>



int main() {

    PenaltySpace* pspace = (PenaltySpace*)malloc(sizeof(PenaltySpace));
    psinit(pspace);
    printf("Penalty Space Test:\n");
    pslayloc(pspace, 10, 10, 10);
    pslayloc(pspace, 20, 10, 20);
    pslayloc(pspace, 15, 5, 10);
    psprint(pspace);

    MemorySpace* mspace = (MemorySpace*) malloc(sizeof(MemorySpace));
    msinit(mspace);
    msclose(mspace, 1, 0, 10);
    printf("\nMemory Space Test:\n");
    printf("Bins: %x %x\n", mspace->bins.sets[0], mspace->bins.sets[1]);
    printf("Flow: %x %x\n", mspace->flow.sets[0], mspace->flow.sets[1]);
    msopen(mspace, 1, 0);
    printf("Bins: %x %x\n", mspace->bins.sets[0], mspace->bins.sets[1]);
    printf("Flow: %x %x\n", mspace->flow.sets[0], mspace->flow.sets[1]);

    return 0;
}
