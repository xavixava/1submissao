#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#include"graph.h"

#define MAX_LINHA 30

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
		printf("Não foi possivel alocar memoria\n");
		exit(1);
	}
	
	(*g).v = v;
	g->e = a;
	
	vector = NULL;
	vector = (Location **) malloc(v*sizeof(Location*));
	if (vector == NULL){
		printf("Não foi possivel alocar memoria\n");
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
		printf("Não foi possivel alocar memoria\n");
		exit(1);
		}
		n -> localidade = localidade;
		n -> interesse = interesse;
		n -> next = initList();
		(*g).vector[localidade-1]=n;
		return;
	}
	printf("Localidade inexistente");
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
	if(g->vector[index-1]->next != NULL) n = g->vector[index-1]->next;
	else
	{
		g->vector[index-1]->next = l;
		return;
	}
	while (getNextNodeList(n) != NULL) n = getNextNodeList(n);
	insertNextNodeList(n, l);
	
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
		if(g->vector[i]->next!=NULL){
			p = g->vector[i]->next;
			n = p;
			while(getNextNodeList(n)!=NULL){
				p = getNextNodeList(n);
				free(n);
				g->e--;
				n = p;
			}
			free(n);
			g->e--;
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


int modoA0(Graph *g, int v){

    int i, count;
	printf(" %d %d",g->v, g->e);

    if((v<1)||(v>g->v)){
        return -1;
    }else{

        for(i=0; i<=g->v; i++) {
            if(g->vector[i]->localidade==v) break;
        }
    }

    count=lengthList(g->vector[i]->next);
    return count;
}


double modoB0(Graph *g,int v1, int v2){

    List *l;

    if((v1>g->v)||(v1<1)||(v2>g->v)||(v2<1)){

        return -1;
    }

    l=g->vector[v1-1]->next;

    while(l!=NULL){

        if(getIndexList(l) == v2 ){
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
	int a = g->v, i;
	int visited[a], adj[a];
	memset(visited, 0, a*sizeof(int));
	memset(adj, 0, a*sizeof(int));
	adjacencia(g, v,visited, adj, k, 0);
	for(i=0; i < a; i++){
		if(adj[i]==1)return 1;
	}
	return 0;
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

/*void vizinho(Graph *g, int v, int *visited, int maxstage, int stage, int *flag)
{
	List *l = g->vector[v-1]->next;
	int i;
	if(stage == maxstage){
		if(visited[v-1] == maxstage){
			*flag=1;
			return;
		}
		else {
			visited[v-1] = -1;
			return;
			}
	}
	
	visited[v-1] = -1;
	
	while(getNextNodeList(l)!=NULL)
	{
		if((visited[(getIndexList(l))-1])==0)visited[(getIndexList(l))-1] = stage + 1;
		l = getNextNodeList(l);
	} 
	if((visited[(getIndexList(l))-1])==0)visited[(getIndexList(l))-1] = stage + 1;
	for(i = 0; i < g->v; i++) if((visited[i] == stage) && (stage!=0)) vizinho(g, getIndexList(l), visited, maxstage, stage, flag);
	for(i = 0; i < g->v; i++) if(visited[i] == stage+1) vizinho(g, getIndexList(l), visited, maxstage, stage + 1, flag);
	return;
}/*

/*int vizinho(Graph *g, int v, int *visited, int maxstage, int stage)
{
	List *l = g->vector[v-1]->next;
	int i;
	if(stage == maxstage){
		if(visited[v-1] == maxstage){
			*flag=1;
			return;
		}
		else {
			visited[v-1] = -1;
			return;
			}
	}
	visited[v-1] = -1;
	while(getNextNodeList(l)!=NULL)
	{
		if((visited[(getIndexList(l))-1])==0)visited[(getIndexList(l))-1] = stage + 1;
		l = getNextNodeList(l);
	} 
	if((visited[(getIndexList(l))-1])==0)visited[(getIndexList(l))-1] = stage + 1;
	for(i = 0; i < g->v; i++) if((visited[i] == stage) && (stage!=0)) vizinho(g, getIndexList(l), visited, maxstage, stage, flag);
	for(i = 0; i < g->v; i++) if(visited[i] == stage+1) vizinho(g, getIndexList(l), visited, maxstage, stage + 1, flag);
	return;
}*/

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
	int a = g->v, i, count=0;
	int visited[a], adj[a];
	memset(visited, 0, a*sizeof(int));
	memset(adj, 0, a*sizeof(int));
	adjacencia(g, v, visited, adj, k, 0);
	for(i=0; i < a; i++){
		if(adj[i]==1)count++;
	}
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

void adjacencia(Graph *g, int v, int *visited, int *adj, int maxstage, int stage)
{
	int i;
	List *l = g->vector[v-1]->next;
	if(stage == maxstage){
		if(visited[v-1] == maxstage){
			adj[v-1] = 1;
			return;
		}
		else {
			visited[v-1] = -1;
			return;
			}
	}
	visited[v-1]=-1;
	while(getNextNodeList(l)!=NULL)
	{
		if((visited[(getIndexList(l))-1])==0)visited[(getIndexList(l))-1] = stage + 1;
		l = getNextNodeList(l);
	}
	if((visited[(getIndexList(l))-1])==0){
		visited[(getIndexList(l))-1] = stage + 1;
		}
	for(i = 0; i < g->v; i++)if((visited[i] == stage) && (stage!=0))adjacencia(g, i+1, visited, adj, maxstage, stage);
	for(i = 0; i < g->v; i++)if(visited[i] == stage + 1)adjacencia(g, i+1, visited, adj, maxstage, stage+1);
	return;

}

int getV(Graph *g)
{
	return ((g == NULL) ? -1 : g->v);
}

int getE(Graph *g)
{
	return ((g == NULL) ? 0 : g->e);
}

Graph *readmaps(FILE * fpmaps){

    Graph *g;
    int n_vertices=0, n_arestas=0, countv=0, counta=0;
    double custos;
    char auxc[MAX_LINHA], *classificador;
    int edge1, edge2;

        counta = fscanf(fpmaps, "%d %d", &n_vertices, &n_arestas);
        printf(" ** %d %d \n", n_vertices , n_arestas);

        if(counta==2) g = GRAPHinit(n_vertices, n_arestas);
        else {
            printf("Algo deu errado ao ler ficheiro\n");
            return NULL;
            }

        counta=0;

        while(countv < n_vertices){

            fscanf(fpmaps, "%d %s", &edge1, auxc);


            if((strcmp("-",auxc))==0){

                classificador=NULL;

            }else{

                classificador = (char*) malloc((strlen(auxc)+1)*sizeof(char));
                if (classificador == NULL){
                printf("Não foi possivel alocar memoria\n");
                exit(1);
                }
                strcpy(classificador, auxc);
                }
            GRAPHaddV(g, edge1, classificador);
            countv++;
            printf("%d %s\n", edge1, classificador);
         }

         while(counta < n_arestas){

            fscanf(fpmaps, "%d %d %lf", &edge1, &edge2, &custos);
            counta++;
            GRAPHinsertE(g, edge1, edge2, custos);
            GRAPHinsertE(g, edge2, edge1, custos);
            printf("%d %d %f\n", edge1, edge2, custos);

         }

    return g;
}
