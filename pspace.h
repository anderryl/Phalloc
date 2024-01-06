//
// Created by Rylie Anderson on 12/23/23.
//

#ifndef PHALLOCATE_PSPACE_H
#define PHALLOCATE_PSPACE_H

typedef struct PenaltySegment {
    char penalty;
    short start;
} PenaltySegment;

#define Payload PenaltySegment
#include "clist.h"

typedef ContiguousList PenaltySpace;

void psinit(PenaltySpace* space);

void pslayloc(PenaltySpace *space, short loc, short penalty, short length);

void pslayend(PenaltySpace* space, ListItem* item, short offset, short penalty, short length);

void pslaystart(PenaltySpace* space, ListItem* item, short offset, short penalty, short length);

void psprint(PenaltySpace* space);

#endif //PHALLOCATE_PSPACE_H
