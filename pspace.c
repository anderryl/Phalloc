//
// Created by Rylie Anderson on 12/24/23.
//

#include "pspace.h"

short seglength(ContiguousList* list, ListItem* item) {
    Iterator iter = itinitref(list, item);
    if (itnext(&iter), !ithasnext(&iter)) {
        return width - item->payload.start;
    }
    else {
        return (short)(itpeeknext(&iter)->payload.start - item->payload.start);
    }
}

void splitstart(PenaltySpace* space, ListItem* whole, short len) {
    if (len < seglength(space, whole)) {
        clinsertbefore(space, whole, whole->payload);
        whole->payload.start += len;
    }
}

void splitend(PenaltySpace* space, ListItem* whole, short len) {
    if (len < seglength(space, whole)) {
        PenaltySegment segment = (PenaltySegment) {whole->payload.penalty, whole->payload.start + len};
        clinsertafter(space, whole, segment);
        ListItem* other = clafter(space, whole);
    }
}

void psinit(PenaltySpace* space) {
    clinit(space);
    clinsert(space, 0, (PenaltySegment){0, 0});
}

void pslaystart(PenaltySpace* space, ListItem* item, short offset, short penalty, short length) {
    Iterator iter = itinitref(space, item);
    short threshold = length + offset + item->payload.start;

    if (offset == 0) {
        if (ithasprev(&iter)) {
            ListItem* prev = itpeekprev(&iter);
            if (prev->payload.penalty == penalty + item->payload.penalty) {
                item->payload.start = prev->payload.start;
                clremove(space, prev);
            }
        }
    }
    else {
        splitstart(space, item, offset);
    }

    ListItem* current;
    while (ithasnext(&iter)) {
        current = itnext(&iter);
        if (current->payload.start >= threshold) {
            current = itprev(&iter);
            break;
        }
        else {
            current->payload.penalty += penalty;
        }
    }

    if (ithasnext(&iter)) {
        ListItem* next = itpeeknext(&iter);
        if (next->payload.start == threshold) {
            if (next->payload.penalty == current->payload.penalty) {
                clremove(space, next);
            }

            return;
        }
    }

    if (threshold <= width) {
        splitend(space, current, threshold - current->payload.start);
        clafter(space, current)->payload.penalty -= penalty;
    }
    else {
        pslaystart(space, clget(space, 0), 0, penalty, threshold - width);
    }
}

void pslayloc(PenaltySpace *space, short loc, short penalty, short length) {
    Iterator iter = itinitat(space, space->last);
    ListItem* current = itnext(&iter);
    while (ithasprev(&iter) && current->payload.start > loc) {
        current = itprev(&iter);
    }

    pslaystart(space, current, loc - current->payload.start, penalty, length);
}

void pslayref(PenaltySpace *space, ListItem* item, PenaltySegment segment, short length) {
    Iterator iter = itinitref(space, item);
    ListItem* current = itnext(&iter);

    if (current->payload.start > segment.start) {
        while (ithasprev(&iter) && current->payload.start > segment.start) {
            current = itprev(&iter);
        }
    }
    else {
        while (ithasnext(&iter) && current->payload.start < segment.start) {
            current = itnext(&iter);
        }

        if (current->payload.start > segment.start) {
            current = itprev(&iter);
        }
    }


    pslaystart(space, current, segment.start - current->payload.start, segment.penalty, length);
}

void pslayend(PenaltySpace* space, ListItem* item, short offset, short penalty, short length) {
    Iterator iter = itinitref(space, item);
    short dest = (short)((clafter(space, item)->payload.start + (width - ((offset + length) % width))) % width);

    ListItem* current = item;
    while (ithasprev(&iter) && item->payload.start > dest) {
        current = itprev(&iter);
    }

    pslaystart(space, current, dest - current->payload.start, penalty, 1 + length);
}

void psprint(PenaltySpace* space) {
    Iterator iter = itinit(space);
    while (ithasnext(&iter)) {
        ListItem* next = itnext(&iter);
        short len = seglength(space, next);
        printf("(%d, %d-%d), ", next->payload.penalty, next->payload.start, next->payload.start + len - 1);
    }
    printf("\n");
}