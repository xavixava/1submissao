#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#include"graph.h"

#define MAX_LINHA 30

#define swap(a, b) {typeof(a) c=b; b=a; a=c;} 

#define MAX(a, b) (a > b) ? 1 : 0

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

/*
 *  Function:
 *    GRAPHinit
 *
 *  Description:
 *    Allocates memory and initializes the graph.
 *
 *  Arguments:
 *    int v keeping the number of nodes
 *	  int a keeping the number of edges
 *    
 *
 *  Return value:
 *    Pointer to a new graph
 */

Graph *GRAPHinit(int v, int a)
{
	Graph *g;
	Location **vector;
	
	g = (Graph *) malloc(sizeof(Graph)); 
	if (g == NULL)
	{
		exit(1);
	}
	
	(*g).v = v;
	g->e = a;
	
	vector = NULL;
	vector = (Location **) malloc(v*sizeof(Location*));
	if (vector == NULL){
		exit(1);
	}
	*vector = NULL;
	g->vector = vector;
	
	return g;
}

/*
 *  Function:
 *    GRAPHaddv
 *
 *  Description:
 *    Allocates memory and initializes the node.
 *
 *  Arguments:
 *    Pointer to the graph
 *	  int localidade keeping the index of the node
 *    char* interesse keeping the special something of the location
 *
 *  Return value:
 *    None
 */

void GRAPHaddV(Graph *g, int localidade, char *interesse)
{	
	Location *n;
	if(localidade <= (*g).v){
		n = (Location *) malloc(sizeof(Location));
		if (n == NULL){
		exit(1);
		}
		n -> localidade = localidade;
		n -> interesse = interesse;
		n -> next = initList();
		(*g).vector[localidade-1]=n;
		return;
	}
	return;
}

/*
 *  Function:
 *    GRAPHinsertE
 *
 *  Description:
 *    Allocates memory and places the edge(List).
 *
 *  Arguments:
 *	  Pointer to the graph
 *    int index keeping the index of the origin node
 *	  int adj keeping the index of the adjacent node
 *	  double custo keeping the cost of the edge
 *
 *  Return value:
 *    None
 */

void GRAPHinsertE(Graph *g, int index, int adj, double custo)
{
	List *n, *l;
	n = initList();
	l = initList();
	l = createEdge(adj, custo);	
	if(g->vector[index-1]->next == NULL){
		g->vector[index-1]->next = l;
		return;
	}
	n = g->vector[index-1]->next;
	/*if(getIndexList(l)<getIndexList(n)){*/
	insertNextNodeList(l, n);
	g->vector[index-1]->next = l;
	/*}
	else{
		insertSortedList(n, l);
	}*/
	return;
}

/*
 *  Function:
 *    GRAPHremoveE
 *
 *	  we ended up not using it
 *
 *  Description:
 *    Destroys an edge that includes its arguments.
 *
 *  Arguments:
 *	  Pointer to the graph
 *    int i keeping the index of the origin node
 *	  int index keeping the index of the adjacent node
 *
 *  Return value:
 *    None
 */

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

/*
 *  Function:
 *    GRAPHdestroy
 *
 *  Description:
 *    Destroys a graph and frees its memory
 *
 *  Arguments:
 *	  Pointer to the graph
 *
 *  Return value:
 *    None
 */

void GRAPHdestroy(Graph *g)
{
	List *n, *p;
	int i = 0;

	for(i = 0; i < g->v; i++)
	{
		if(g->vector[i]->next==NULL)return;
		else{
			p = g->vector[i]->next;
			n = p;
			while(n!=NULL){
				p = getNextNodeList(n);
				free(n);
				g->e--;
				n = p;
			}
		}
		free(g->vector[i]->interesse);
	}
	for(i=0; i < g->v; i++) free(g->vector[i]);
	free(g->vector);
	/*if(g->e==0)	free(g->vector);
	else exit(1);*/
	free(g);
	return;
}

/*
 *  Function:
 *    modoA0
 *
 *  Description:
 *    Discovers the number of neighbors of a node.
 *
 *  Arguments:
 *    pointer to the graph: g
 *    int keeping the node: v1??
 *
 *  Return value:
 *    Returns the number of neighbours
 */


int modoA0(Graph *g, int v){

    int count;
	
    if((v<1)||(v>g->v)){
        return -1;
    }

    count=lengthList(g->vector[v-1]->next);
    return count;
}

/*
 *  Function:
 *    modoB0
 *
 *  Description:
 *    Discovers if two nodes are directly connected.
 *
 *  Arguments:
 *    pointer to the graph: g
 *    int keeping the first node: v1
 *      int keeping the second node: v2
 *
 *  Return value:
 *    Returns the value of cost if the nodes are directly connected.
 *   -1 is returned if the nodes are not directly connected.
 */


double modoB0(Graph *g,int v1, int v2){

    List *l;
	int v=g->v, a=1;

    if(MAX(v1, v)||MAX(a, v1)||MAX(v2, v)||MAX(a, v2)){

        return -1;
    }

	if(MAX(v2, v1))swap(v1, v2);

    l=g->vector[v1-1]->next;
	
    while(l!=NULL){
        if(getIndexList(l) == v2){
        return getCustoList(l);

        }
        l=getNextNodeList(l);
    }

    return -1;
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
 *
 *  Return value:
 *    Returns the pointer to the item of a linked list node. NULL
 *   is returned if the node is NULL (or if the item is NULL).
 */
 
int modoC0 (Graph *g, int v, int k)
 { 
	int a = g->v;
	int visited[a];
	memset(visited, 0, a*sizeof(int));
	a = vizinho(g, v,visited, k, 0, 0);
	return a;
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
 *  
 *	  Return value:
 *    1 if there is a neighbor, 0 if there isn't
 */

int vizinho(Graph *g, int v, int *visited, int maxstage, int stage, int flag)
{
	int i;
	List *l = g->vector[v-1]->next;
	if(stage == maxstage){
		if(visited[v-1] == maxstage){
			flag = 1;
			return flag;
		}
		else {
			visited[v-1] = -1;
			return flag;
			}
	}
	visited[v-1]=-1;
	while(l!=NULL)
	{
		if((visited[(getIndexList(l))-1])==0)visited[(getIndexList(l))-1] = stage + 1;
		l = getNextNodeList(l);
	}
	i = getIndexList(l);
	if(i!=-1){
		if(visited[i-1]==0){
			visited[i-1] = stage + 1;
		}
	}
	for(i = 0; i < g->v; i++){
		if(flag == 1)return flag;
		else{
			if((visited[i] == stage) && (stage!=0))flag = vizinho(g, i+1, visited, maxstage, stage, flag);
		}
	}	
	for(i = 0; i < g->v; i++){
		if(flag == 1)return flag;
		else{
			if(visited[i] == stage + 1)flag = vizinho(g, i+1, visited, maxstage, stage+1, flag);
		}
	}
	return flag;

}

/*
 *  Function:
 *    modoD0
 *
 *  Description:
 *    Discovers the number of neighbors in a node at k stages.
 *
 *  Arguments:
 *	  Pointer to the graph
 *    int i keeping the index of the origin node
 *	  int index keeping the index of the adjacent node
 *
 *  Return value:
 *    int
 */

int modoD0(Graph *g, int v, int k)
{
	int a = g->v, count=0;
	int visited[a];
	memset(visited, 0, a*sizeof(int));
	count =	adjacencia(g, v, visited, k, 0, 0);
	return count;
}

/*
 *  Function:
 *    adjacencia
 *
 *  Description:
 *    Discovers if a node has a neighbor in k stages.
 *
 *  Arguments:
 *    pointer to the graph: g
 *    int keeping the original node: v
 *	  int  keeping the number of stages
 *
 *  Return value:
 *    none
 */

int adjacencia(Graph *g, int v, int *visited, int maxstage, int stage, int count)
{
	int i;
	List *l = g->vector[v-1]->next;
	if(stage == maxstage){
		if(visited[v-1] == maxstage){
			visited[v-1]=-1;
			count++;
			return count;
		}
		else {
			visited[v-1] = -1;
			return count;
			}
	}
	visited[v-1]=-1;
	while(l != NULL)
	{
		if((visited[(getIndexList(l))-1])==0)visited[(getIndexList(l))-1] = stage + 1;
		l = getNextNodeList(l);
	}
	for(i = 0; i < g->v; i++)if((visited[i] == stage) && (stage!=0))count = adjacencia(g, i+1, visited, maxstage, stage, count);
	for(i = 0; i < g->v; i++)if(visited[i] == stage + 1)count = adjacencia(g, i+1, visited, maxstage, stage+1, count);
	return count;

}

int getV(Graph *g)
{
	return ((g == NULL) ? -1 : g->v);
}

int getE(Graph *g)
{
	return ((g == NULL) ? -1 : g->e);
}

/*
 *  Function:
 *    readmaps
 *
 *  Description:
 *    reads the mapfile and creates graph.
 *
 *  Arguments:
 *    pointer to file
 *
 *  Return value:
 *    pointer to graph
 */

Graph *readmaps(FILE * fpmaps){

    Graph *g;
    int n_vertices=0, n_arestas=0, countv=0, counta=0,scan=0;
    double custos;
    char auxc[MAX_LINHA], *classificador;
    int edge1, edge2;

        scan = fscanf(fpmaps, "%d %d", &n_vertices, &n_arestas);

        if(scan==2) g = GRAPHinit(n_vertices, n_arestas);
        else {
            return NULL;
            }

        counta=0;

        while(countv < n_vertices){

            scan = fscanf(fpmaps, "%d %s", &edge1, auxc);

			if (scan==2){
				if((strcmp("-",auxc))==0){

					classificador=NULL;

				}else{

					classificador = (char*) malloc((strlen(auxc)+1)*sizeof(char));
					if (classificador == NULL){
					exit(1);
					}
					strcpy(classificador, auxc);
					/*classificador[3]='\0';*/
					}
				GRAPHaddV(g, edge1, classificador);
				countv++;
			}
         }

         while(counta < n_arestas){

            scan=fscanf(fpmaps, "%d %d %lf", &edge1, &edge2, &custos);
            counta++;
            GRAPHinsertE(g, edge1, edge2, custos);
            GRAPHinsertE(g, edge2, edge1, custos);

         }

    return g;
}
