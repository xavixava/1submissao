#include<stdio.h>
#include<stdlib.h>

#include"graph.h"

/*	Data Type: Graph
 *  Description: Structure with:
 *      1) int that keeps the number of nodes
 *      2) int that keeps the number of edges
 *		3) Edge vector
 */
struct GraphStruct
{
	int v; 
	int e; 
	Location **vector; 
};

/*  Data Type: Location
 *  Description: Structure with:
 *      1) int that keeps the location
 *      2) string that keeps the characteristics of the location.
 */
struct NodeStruct
{
	int localidade;
	char *interesse;
	List *adj;
};

/*  Data Type: Node
 *  Description: Structure with:
 *      1) Item (possibly pointer to data)
 *      2) Pointer to next node of the list.
 *
struct Vector
{
	Item this;
    List *next;
};*/

/*
 *  Function:
 *    GRAPHinit
 *
 *  Description:
 *    Allocates memory for the graph.
 *
 *  Arguments:
 *    Pointer to the first element of a linked list:
 *      (LinkedList *) first
 *    
 *
 *  Return value:
 *    None
 */

Graph *GRAPHinit(int v)
{
	Graph *g;
	Location **vector;
	
	g = (Graph *) malloc(sizeof(Graph)); 
	
	if(g == NULL) return NULL;
	
	(*g).v = v;
	g->e = 0;
	
	*vector = initList();
	vector = (Location **) malloc(v*sizeof(Location*));
	vector = g->vector;
	
	return g;
}

void GRAPHaddV(Graph *g, Location *n)
{
	if((*n).localidade < (*g).v){
		int index = (n->localidade) - 1;
		(*g).vector[index] = (Node *) malloc(sizeof(Location));
		return;
	}
	printf("Localidade inexistente");
	return;
}

void GRAPHinsertE(Graph *g, List *l, int index)
{
	List *n;
	n = initList();
	if(g->vector[index-1]->next != NULL) n =g->vector[index-1]->next;
	else
	{
		g->vector[index-1]->next = l;
		return;
	}
	while (getNextNodeList(n) != NULL) getNextNodeList(n);
	insertNextNodeList(n, l);
	g->e++;
	
	return;
}

void GRAPHremoveE(Graph *g, int i, int index)
{
	List *prev, *next;
	
	prev = g->vector[i-1]->next;
	next = prev;
	
	while(getIndexList(next)!=index){
		prev = next;
		next = getNextNodeList(prev);
	}
	prev = getNextNodeList(next);
	free(next);
	return;
}

void GRAPHdestroy(Graph *g)
{
	List *n, *p;
	int i = 0;
	
	for(i = 0; i < g->v; i++)
	{
		p = g->vector[i]->next;
		n = p;
		while(getNextNodeList(n)!=NULL){
			n = getNextNodeList(n);
			free(n);
			g->e--;
			p = n;
		}
		free(n);
		g->e--;
	}
	if(g->e==0)	free(g->vector);
	else exit(1);
	free(g);
	return;
}

/*
 *  Function:
 *    getItemList
 *
 *  Description:
 *    Gets the item of a list node.
 *
 *  Arguments:
 *    Pointer to a list node:
 *        (LinkedList *) node
 *
 *  Return value:
 *    Returns the pointer to the item of a linked list node. NULL
 *   is returned if the node is NULL (or if the item is NULL).
 *
Item getItemList(Node *node)
{
    return ((node == NULL) ? NULL : node->this);
}*/

/*
 *  Function:
 *    getItemLinkedList
 *
 *  Description:
 *    Gets the item of a linked list node.
 *
 *  Arguments:
 *    Pointer to a linked list node:
 *        (LinkedList *) node
 *
 *  Return value:
 *    Returns the pointer to the item of a linked list node. NULL
 *   is returned if the node is NULL (or if the item is NULL).
 */
 
 
