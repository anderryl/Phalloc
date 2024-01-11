#include "phalloc.h"
#include "mspace.h"
#include "stdlib.h"
#include "pspace.h"

int main() {
    //phalloc(0);
    MemorySpace* mspace = (MemorySpace*)malloc(sizeof(MemorySpace));
    msinit(mspace);
    msclose(mspace, 10, 0, 100);
    msprint(mspace);
    msclose(mspace, 120, 0, 50);
    msprint(mspace);
    msopen(mspace, 10, 0);
    msprint(mspace);

    PenaltySpace* pspace = (PenaltySpace*)malloc(sizeof(PenaltySpace));
    psinit(pspace);
    psprint(pspace);
    pslayloc(pspace, 10, 1, 100);
    pslayloc(pspace, 60, 1, 100);
    pslayloc(pspace, 50, 1, 10);
    pslayloc(pspace, 110, 1, 20);
    psprint(pspace);

    return 0;
}
