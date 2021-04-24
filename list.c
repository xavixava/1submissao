#include<stdio.h>
#include<stdlib.h>

#include"list.h"

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
	float custo;
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
    for(aux = first, counter = 0; aux!=NULL; counter++, aux = aux->next);

    return counter;
}


/*
 *  Function:
 *    getNextNodeList
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
 *   is returned in case the next node is empty or there is no
 *   node following the current node.
 */
List *getNextNodeList(List * node)
{
  return ((node->next == NULL) ? NULL : node->next);
}

/*
 *  Function:
 *    getIndexList
 *
 *  Description:
 *    Returns the index of a linked list.
 *
 *  Arguments:
 *    Pointer to the current linked list node:
 *        (List *) node
 *
 *  Return value:
 *    Returns the int value of index. NULL
 *   is returned in case the current node is empty.
 */
int getIndexList(List * node)
{
  return ((node == NULL) ? -1 : node->index);
}

/*
 *  Function:
 *    insertNextNodeList
 *
 *  Description:
 *    assigns pointer to the next node of a linked list.
 *
 *  Arguments:
 *    Pointer to the current linked list node:
 *        (LinkedList *) node
 *	  Pointer to the next linked list node:
 *        (LinkedList *) next
 *
 *  Return value:
 *    Returns void.
 */
void insertNextNodeList(List * node, List *next)
{
	node->next = next;
	return;
}

/*
 *  Function:
 *    assignIndexList
 *
 *  Description:
 *    assigns int to the index of a linked list.
 *
 *  Arguments:
 *    Pointer to the current linked list node:
 *        (LinkedList *) node
 *	  Pointer to the next linked list node:
 *        (LinkedList *) next
 *
 *  Return value:
 *    Returns void.
 */

List *createEdge(int i, float cost)
{
	List *l;
	l = initList();
	l = (List *) malloc(sizeof(List));
	if (l == NULL)
	{
		printf("Não foi possivel alocar memoria\n");
		exit(1);
	}
	l->index = i;
	l->custo=cost;
	l->next = NULL;
	return l;
}
