//
// Created by Rylie Anderson on 12/22/23.
//

#ifndef PHALLOCATE_CLIST_H
#define PHALLOCATE_CLIST_H

#include "constants.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define NSI ~0

#ifndef Payload
typedef struct {
    char penalty;
    short start;
} PenaltySegment;
#define Payload PenaltySegment
#endif

typedef struct {
    Payload payload;
    short next;
    short prev;
} ListItem;

typedef struct {
    short first;
    short last;
    short count;
    ListItem items[width];
} ContiguousList;

typedef struct {
    ContiguousList* list;
    short index;
    bool first;
} Iterator;

/**
 * Initializes an empty list in a previosuly allocated structure
 * @param ptr pointer to list structure
 */
void clinit(ContiguousList* ptr);

/**
 * Creates an iterator on the given list
 * Removing current iteration item will invalidate the iterator
 * @param list pointer to list to be iterated over
 * @return A list iterator object
 */
Iterator itinit(ContiguousList* list);

Iterator itinitat(ContiguousList* list, short index);

Iterator itinitref(ContiguousList* list, ListItem* ref);

/**
 * Determines whether the iterator has another item
 * @param iterator pointer to an iterator object
 * @return whether iterator has another item
 */
bool ithasnext(Iterator* iterator);

/**
 * Determines whether a itprev call on the iterator would be valid
 * @param iterator pointer to an iterator object
 * @return wheth
 */
bool ithasprev(Iterator* iterator);

/**
 * Retrieves the itnext item from the iterator
 * @param iterator pointer to the iterator object
 * @pre iterator must have a itnext item
 * @return the pointer to itnext item
 */
ListItem* itnext(Iterator* iterator);

ListItem* itpeeknext(Iterator* iterator);

/**
 * Retrieves the previous item from the iterator
 * @param iterator pointer to the iterator object
 * @pre iterator must have a previous item
 * @return the pointer to previous item
 */
ListItem* itprev(Iterator* iterator);

ListItem* itpeekprev(Iterator* iterator);

ListItem* clafter(ContiguousList* list, ListItem* item);

ListItem* clbefore(ContiguousList* list, ListItem* item);

/**
 * Retrieves an item from the list
 * @param list the list
 * @param index the index to be retrieved
 * @return the pointer to the item at the specified index
 */
ListItem* clget(ContiguousList* list, short index);

/**
 * Inserts an item into the list
 * @param list the list
 * @param index index to be inserted at
 * @param value penalty value
 * @param len start value
 */
void clinsert(ContiguousList* list, short index, Payload payload);

/**
 * Inserts clafter the given item
 * @param list list pointer
 * @param ref pointer to reference item
 * @param value penalty value for new item
 * @param len start value for new item
 */
void clinsertafter(ContiguousList* list, ListItem* ref, Payload payload);

/**
 * Inserts clbefore the given item
 * @param list list pointer
 * @param ref pointer to reference item
 * @param value penalty value for new item
 * @param len start value for new item
 */
void clinsertbefore(ContiguousList* list, ListItem* ref, Payload payload);

/**
 * Removes the item for the list
 * @param list the list
 * @param item pointer to item to be removed
 */
void clremove(ContiguousList* list, ListItem* item);

/**
 * Removes the indexed item from the list
 * @param list the list
 * @param index index to be removed
 */
void clremoveat(ContiguousList* list, short index);

void clprint(ContiguousList* list);

#endif //PHALLOCATE_CLIST_H
