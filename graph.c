#include<stdio.h>
#include<stdlib.h>

#include"graph.h"
#include"list.h"

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
	List *next;
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
	
	vector = NULL;
	vector = (Location **) malloc(v*sizeof(Location*));
	*vector = NULL;
	g->vector = vector;
	
	return g;
}

void GRAPHaddV(Graph *g, int localidade, char *interesse)
{	
	Location *n;
	if(localidade < (*g).v){
		n = (Location *) malloc(sizeof(Location));
		n -> localidade = localidade;
		n -> interesse = interesse;
		n -> next = initList();
		(*g).vector[localidade];
		return;
	}
	printf("Localidade inexistente");
	return;
}

void GRAPHinsertE(Graph *g, int index, int adj, int custo)
{
	List *n, *l;
	n = initList();
	l = initList();
	l = (List *) malloc(2*sizeof(int)+sizeof(List*));
	assignIndexList(l, adj, custo);	
	if(g->vector[index-1]->next != NULL) n = g->vector[index-1]->next;
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
	g->e--;
	return;
}

void GRAPHdestroy(Graph *g)
{
	List *n, *p;
	int i = 0;
	
	for(i = 0; i < g->v; i++, free(g->vector[i]->interesse))
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
 *    modoC0
 *
 *  Description:
 *    Discovers if a node has a neighbor in k stages.
 *
 *  Arguments:
 *    pointer to the graph: g
 *    int keeping the original node: v
 *	  int  keeping the number of stages: k
 *  Return value:
 *    Returns the pointer to the item of a linked list node. NULL
 *   is returned if the node is NULL (or if the item is NULL).
 */
 
int modoC0 (Graph *g, int v, int k)
 { 
	int a = g->v;
	int visited[a];
	memset(visited, 0, a*sizeof(int));
	return vizinho(g, v,visited, k, 0);
 }

/*
 *  Function:
 *    vizinho
 *
 *  Description:
 *    Discovers if a node has a neighbor in k stages.
 *
 *  Arguments:
 *    pointer to the graph: g
 *    int keeping the original node: v
 *	  int  keeping the number of stages
 *  Return value:
 *    Returns the pointer to the item of a linked list node. NULL
 *   is returned if the node is NULL (or if the item is NULL).
 */

int vizinho(Graph *g, int v, int *visited, int maxstage, int stage)
{
	int a;
	List *l = g->vector[v-1]->next;
	visited[v-1] = 1;
	if(stage == maxstage-1) return((visited[v-1] == 0) ? 1 : 0);
	while(getNextNodeList(l)!=NULL)
	{
		if(visited[(getIndexList(l))-1] == 0) if(vizinho(g, getIndexList(l), visited, maxstage, stage++)==1) return 1;
	}
	return 0;
}

int modoD0(Graph *g, int v, int k)
{
	int a = g->v, i, count=0;
	int visited[a];
	memset(visited, 0, a*sizeof(int));
	adjacencia(g, v, visited, k, 0);
	for(i=0; i < a; i++){
		if(visited[i]==1)count++;
	}
	return count;
}

void adjacencia(Graph *g, int v, int *visited, int maxstage, int stage)
{
	List *l = g->vector[v-1]->next;
	visited[v-1] = 1;
	if(stage == maxstage-1) return;
	while(getNextNodeList(l)!=NULL)
	{
		if(visited[(getIndexList(l))-1] == 0) adjacencia(g, getIndexList(l), visited, maxstage, stage++);
	}
	return;

}