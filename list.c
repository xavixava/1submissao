#include<stdio.h>
#include<stdlib.h>

#include"list.h"

#define MAX(a, b) (a > b) ? 1 : 0

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
	double custo;
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
 *    lengthList
 *
 *  Description:
 *    Determines the length of a list.
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
  return ((node == NULL) ? NULL : node->next);
}

/*
 *  Function:
 *    getCustoList
 *
 *  Description:
 *    Returns the cost of a linked list.
 *
 *  Arguments:
 *    Pointer to the current linked list node:´
 *        (List *) node
 *
 *  Return value:
 *    Returns the double value of cost. NULL
 *   is returned in case the current node is empty.
 */


double getCustoList(List * node){

    return ((node == NULL) ? -1 : node->custo);
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
 *    Returns the int value of index. -1
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
 *    None.
 */
void insertNextNodeList(List * node, List *next)
{
	node->next = next;
	return;
}

void insertSortedList(List *first, List *node)
{
	int a, b;
	List *aux, *l;
	if(first->next==NULL){
		first->next=node;
		return;
	}
	l = first;
	aux = l;
	a=node->index;
	while((l->next)!=NULL){
		l=l->next;
		b = l->index;
		if(!MAX(a, b))
		{
			node->next = l;
			aux->next = node;
			return;
		}
		aux = l;
	}
	l->next=node;
}

/*
 *  Function:
 *    createEdge
 *
 *  Description:
 *    Creates edge and assigns its values.
 *
 *  Arguments:
 *    int keeping the destination node of the edge 
 *	  double keeping the cost of the edge
 *
 *  Return value:
 *    pointer to the new edge.
 */

List *createEdge(int i, double cost)
{
	List *l;
	l = initList();
	l = (List *) malloc(sizeof(List));
	if (l == NULL)
	{
		/*printf("Não foi possivel alocar memoria\n");*/
		exit(0);
	}
	l->index = i;
	l->custo=cost;
	l->next = NULL;
	return l;
}
