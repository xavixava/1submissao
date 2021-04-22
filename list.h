/******************************************************************************
 * (c) 2018-2019 AED Team
 * Last modified: abl 2019-03-17
 *
 * NAME
 *   LinkedList.h
 *
 * DESCRIPTION
 *  Header file for an abstract implementation of a List
 *
 * COMMENTS
 *  (Derived from 2018/10/24 lab4 code)
 *
 *  Data type list:
 *     list node: List
 *
 *  Function list:
 *    A) Initialization & Termination
 *        initList
 *        freeLista
 *
 *    B) Properties
 *        lengthList
 *
 *    C) Navigation
 *        getNextNodeList
 *
 *    D) Lookup
 *        getItemList
 *
 *    E) Insertion - simple at head, sorted
 *       insertUnsortedList
 *       insertSortedList
 *
 *  Dependencies:
 *    stdio.h
 *    stdlib.h
 *    defs.h
 *
 *****************************************************************************/


/* Prevent multiple inclusions */
#ifndef ListHeader
#define ListHeader


/*
 *  Data type: LinkedList
 *
 *  Description: Node of a linked list
 */
typedef struct ListStruct List;


/*
 *  Function:
 *    initLinkedList
 *
 *  Description:
 *    Initializes a new linked list.
 *
 *  Arguments:
 *    None
 *
 *  Return value:
 *    Returns the pointer to a new linked list.
 */
List * initList(void);

/*
 *  Function:
 *    lengthLinkedList
 *
 *  Description:
 *    Determines the length of a linked list.
 *
 *  Arguments:
 *    Pointer to the first node of the linked list:
 *        (LinkedList *) first
 *
 *  Return value:
 *    Returns the length of the linked list.
 */
int lengthList(List * first);



/*
 *  Function:
 *    getNextNodeLinkedList
 *
 *  Description:
 *    Returns the next node of a linked list.
 *
 *  Arguments:
 *    Pointer to the current linked list node:
 *        (LinkedList *) node
 *
 *  Return value:
 *    Returns the pointer to the next node of a linked list. NULL
 *   is returned in case the current node is empty or there is no
 *   node following the current node.
 */
List * getNextNodeList(List * node);

int getIndexList(List * node);

void insertDataList(List * node, List *next, int index);


/*
 *  Function:
 *    insertUnsortedLinkedList
 *
 *  Description:
 *    Creates a new linked list node.
 *
 *  Arguments:
 *    Item to associate to the new node:
 *      Item this
 *    Pointer to the next node:
 *      (LinkedList *) next
 *
 *  Return value:
 *    Returns the pointer to the new node.
 */
/*List * insertUnsortedList(List * next, Item this);



/*
 *  Function:
 *    InsertSortedLinkedList
 *
 *  Description:
 *    Inserts an item in order in an sorted linked list.
 *
 *  Arguments:
 *    Pointer to the first node of a sorted linked list:
 *        (LinkedList *) first
 *    Pointer to item to be inserted:
 *        Item item
 *    Pointer to function to compare two items:
 *        int comparisonItemFnt(void * item1, void * item2)
 *
 *        This function returns a value less, equal, or greater
 *       than zero if item1 compares less, equal, or greater than
 *       item2, respectively.
 *
 *    Pointer to integer to write error return value:
 *        (int *) err
 *
 *        0 upon sucess, 1 in case the item is NULL, and 2 in
 *   case of memory allocation failure.
 *
 *  Return value:
 *    Returns the pointer to the first node of the sorted linked list.
 */
/*List * insertSortedList(List * first,
                           Item item,
                           int (* comparisonItemFnt)
                           (Item item1, Item item2),
                           int * err);


/* End of: Protect multiple inclusions                              */
#endif
