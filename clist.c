//
// Created by Rylie Anderson on 12/22/23.
//

#include "clist.h"

void clinit(ContiguousList* ptr) {
    memset(ptr, NSI, sizeof(ContiguousList));

    ptr->first = 0;
    ptr->last = 0;
    ptr->count = 0;

    for (short i = 0; i < width; i++) {
        ptr->items[i].next = i + 1;
    }

    ptr->items[width - 1].next = NSI;
}

Iterator itinit(ContiguousList* list) {
    return (Iterator){list, list->first, true};
}

Iterator itinitat(ContiguousList* list, short index) {
    return (Iterator){list, index, true};
}

Iterator itinitref(ContiguousList* list, ListItem* ref) {
    return (Iterator){list, (short)(ref - list->items), true};
}

bool ithasnext(Iterator* iterator) {
    return iterator->index != iterator->list->last || (iterator->first && iterator->list->count != 0);
}

bool ithasprev(Iterator* iterator) {
    return iterator->index != iterator->list->first;
}

ListItem* itnext(Iterator* iterator) {
    if (iterator->first) {
        iterator->first = false;
        return &iterator->list->items[iterator->index];
    }

    iterator->index = iterator->list->items[iterator->index].next;
    return &iterator->list->items[iterator->index];
}

ListItem* itpeeknext(Iterator* iterator) {
    if (iterator->first) {
        return &iterator->list->items[iterator->index];
    }

    short nexti = iterator->list->items[iterator->index].next;
    return &iterator->list->items[nexti];
}

ListItem* itprev(Iterator* iterator) {
    iterator->first = false;
    iterator->index = iterator->list->items[iterator->index].prev;
    return &iterator->list->items[iterator->index];
}

ListItem* itpeekprev(Iterator* iterator) {
    short previ = iterator->list->items[iterator->index].prev;
    return &iterator->list->items[previ];
}

ListItem* clafter(ContiguousList* list, ListItem* item) {
    return &list->items[item->next];
}

ListItem* clbefore(ContiguousList* list, ListItem* item) {
    return &list->items[item->prev];
}

ListItem* clget(ContiguousList* list, short index) {
    if (index > list->count) {
        return NULL;
    }

    short dest;
    if (index < list->count / 2) {
        dest = list->first;
        for (int i = 0; i < index; i++) {
            dest = list->items[dest].next;
        }
    }
    else {
        dest = list->last;
        for (int i = 0; i < list->count - index - 1; i++) {
            dest = list->items[dest].prev;
        }
    }

    return &list->items[dest];
}

void clinsert(ContiguousList* list, short index, Payload payload) {
    if (index > list->count || index < 0 || list->count >= width) {
        return;
    }

    short newi = list->items[list->last].next;
    ListItem* new = &list->items[newi];
    ListItem* last = &list->items[list->last];
    ListItem* first = &list->items[list->first];

    if (index == 0) {
        if (list->count > 0) {
            last->next = new->next;
            first->prev = newi;
            new->next = list->first;
            new->prev = NSI;
            list->first = newi;
        }
        else {
            new = first;
        }
    }
    else if (index == list->count) {
        new->prev = list->last;
        last->next = newi;
        list->last = newi;
    }
    else {
        ListItem* nex = clget(list, index);
        last->next = new->next;
        new->prev = nex->prev;
        new->next = list->items[new->prev].next;
        list->items[nex->prev].next = newi;
        nex->prev = newi;
    }

    new->payload = payload;

    list->count++;
}

void clinsertafter(ContiguousList* list, ListItem* ref, Payload payload) {
    short newi = list->items[list->last].next;
    ListItem* new = &list->items[newi];
    ListItem* last = &list->items[list->last];

    short pindex = (short)(ref - list->items);

    if (pindex == list->last) {
        new->prev = list->last;
        last->next = newi;
        list->last = newi;
    }
    else {
        last->next = new->next;
        new->next = ref->next;
        list->items[ref->next].prev = newi;
        ref->next = newi;
        new->prev = pindex;
    }

    new->payload = payload;

    list->count++;
}

void clinsertbefore(ContiguousList* list, ListItem* ref, Payload payload) {
    short newi = list->items[list->last].next;
    ListItem* new = &list->items[newi];
    ListItem* last = &list->items[list->last];
    short pindex = (short)(ref - list->items);

    if (pindex == list->first) {
        last->next = new->next;
        new->next = pindex;
        ref->prev = newi;
        list->first = newi;
    }
    else {
        last->next = new->next;
        new->prev = ref->prev;
        new->next = list->items[new->prev].next;
        list->items[ref->prev].next = newi;
        ref->prev = newi;
    }

    new->payload = payload;

    list->count++;
}

void clremove(ContiguousList* list, ListItem* item) {
    ListItem* last = &list->items[list->last];
    short rindex = (short)(item - list->items);

    if (rindex == list->first) {
        if (list->count > 1) {
            ListItem* first = &list->items[list->first];
            short firsti = list->first;
            list->first = first->next;
            list->items[first->next].prev = NSI;
            first->next = list->items[list->last].next;
            last->next = firsti;
        }
    }
    else if (rindex == list->last) {
        list->last = last->prev;
    }
    else {
        list->items[item->prev].next = item->next;
        list->items[item->next].prev = item->prev;
        item->next = last->next;
        last->next = rindex;
    }

    item->prev = NSI;

    list->count--;
}

void clremoveat(ContiguousList* list, short index) {
    if (index > list->count - 1 || index < 0) {
        return;
    }

    clremove(list, clget(list, index));
}

void clprint(ContiguousList* list) {
    Iterator iter = itinit(list);
    while (ithasnext(&iter)) {
        ListItem* item = itnext(&iter);
        printf("%d: (%c %d %d), ", iter.index, item->payload, item->prev, item->next);
    }
    printf("\n");
}