#include<stdio.h>
#include<stdlib.h>

#include"List.h"

/*
 *  Data Type: LinkedListStruct
 *
 *  Description: Structure with:
 *      1) Item of the linked list node (possibly pointer to data)
 *      2) Pointer to next node of the linked list.
 */
struct ListStruct
{
    int index;
	int custo;
    List *next;
};

/*
 *  Function:
 *    initList
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
List * initList(void)
{
    return NULL;
}


/*
 *  Function:
 *    freeLinkedList
 *
 *  Description:
 *    Frees the memory allocated to a linked list.
 *
 *  Arguments:
 *    Pointer to the first element of a linked list:
 *      (LinkedList *) first
 *    Function to free the memory allocated to the items:
 *      void freeItem(Item)
 *
 *  Return value:
 *    None
 */
/*void freeList(List *first, void (* freeItemFnt)(Item))
{
    List *aux, *next;

    /* Cycle from the first to the last element           
    for(aux = first; aux != NULL; aux = next)
    {
        next = aux->next;           /* Keep track of the next node 
        freeItemFnt(aux->this);     /* Free current item data with passed function 
        free(aux);                  /* Free current node    
    }
    return;
}


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
int lengthList(List *first)
{
    List *aux;
    int counter;

    /* Length determination cycle                                   */
    for(aux = first, counter = 0;
        aux!=NULL;
        counter++, aux = aux->next);

    return counter;
}


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
List *getNextNodeList(List * node)
{
  return ((node->next == NULL) ? NULL : node->next);
}


int getIndexList(List * node)
{
  return ((node == NULL) ? NULL : node->index);
}

void insertNextNodeList(List * node, List *next)
{
	node->next = next;
	return;
}

/*
 *  Function:
 *    insertUnsortedLinkedList
 *
 *  Description:
 *    Creates a new node at the head of the linked list.
 *
 *  Arguments:
 *    Item to associate to the new node:
 *      Item this
 *    Pointer to the next node:
 *      (LinkedList *) next
 *
 *  Return value:
 *    Returns the pointer to the new head of the list.
 */
/*List *insertUnsortedList(List *next, Item this)
{
    List *new;

    
    new = (List *) malloc(sizeof(List));

    /* Check memory allocation errors */
   /* if(new == NULL)
        return NULL;

    /* Initialize new node */
    /*new->this = this;
    new->next = next;

    return new;
}*/


/*
 *  Function:
 *    insertSortedLinkedList
 *
 *  Description:
 *    Inserts an item in order in a sorted linked list.
 *
 *  Arguments:
 *    Pointer to the first node of a sorted linked list:
 *        (LinkedList *) first
 *    Pointer to item to be inserted:
 *        Item item
 *    Pointer to function to compare two items:
 *        int comparisonItemFnt(void * item1, void * item2)
 *
 *      This function must return a value less, equal, or greater
 *      than zero if item1 compares less, equal, or greater than
 *      item2, respectively.
 *
 *    Pointer to integer to write error return value:
 *        (int *) err
 *
 *        0 upon sucess, 1 in case the item is NULL, and 2 in
 *      case of memory allocation failure.
 *
 *  Return value:
 *    Returns the pointer to the first node of the sorted linked list.
 */
/*List * insertSortedList(LinkedList *first, Item item,  int (* compareItems) (Item it1, Item it2),
                int * err)
{
    List  *new, *aux;

    /* alloc and check */
   /* new = (List *) malloc(sizeof(List));
    if(new == NULL)
        return NULL;
    
    new->this = item;           /* Initialize new node  */
   /* new->next = NULL;

    if (first == NULL)          /* first item in list */
   /* {
        return new;
    }
    /* list not empty, insertion sort */
    /* insert at head */
  /*  if ((compareItems(item, first->this) <= 0) )
    {
        new->next = first;
        return new;
    }
    /* second etc */
   /* aux = first;
    while(aux != NULL)
    {
        if (aux->next != NULL)
        {
            if ( compareItems(item, aux->next->this) <= 0 )
            {
                new->next = aux->next;
                aux->next = new;
                return first;
            }
        }
        else        /* none left, insert in tail */
    /*    {
            aux->next = new;
            return first;
        }
        aux = aux->next;
    }
    return NULL;
}*/
