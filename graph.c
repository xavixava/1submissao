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

void GRAPHinsertE(Graph *g, int index, int adj, float custo)
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
	List *l = g->vector[v-1]->next;
	int i;
	if(stage == maxstage) return((visited[v-1] > 0) ? 1 : 0);
	visited[v-1] = -1;
	while(getNextNodeList(l)!=NULL)
	{
		if((visited[(getIndexList(l))-1])==0)visited[(getIndexList(l))-1] = stage + 1;
		l = getNextNodeList(l);
	} 
	if((visited[(getIndexList(l))-1])==0)visited[(getIndexList(l))-1] = stage + 1;
	for(i = 0; i < g->v; i++)if((visited[i] == stage) && (stage!=0))if(vizinho(g, getIndexList(l), visited, maxstage, stage)==1) return 1;
	for(i = 0; i < g->v; i++)if((visited[i] == stage) && (stage!=0)) if(vizinho(g, getIndexList(l), visited, maxstage, stage + 1)==1) return 1;
	return 0;
}

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

Graph *readmaps(FILE* fpmaps){

	Graph *g;
    int n_vertices, n_arestas, countv=0, counta=0;
    float custos;
    char auxc[MAX_LINHA], *classificador;
    int edge1, edge2;
	
        if(fscanf(fpmaps, "%d %d", &n_vertices, &n_arestas)==2) ;
		
		g = GRAPHinit(n_vertices, n_arestas);
		
        printf(" ** %d %d \n", n_vertices , n_arestas);

         while(countv!=n_vertices){

            fscanf(fpmaps, "%d %s", &edge1, auxc);


            if((strcmp("-",auxc))!=0){
           
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

         while(counta!=n_arestas){

            fscanf(fpmaps, "%d %d %f", &edge1, &edge2, &custos);
            counta++;
			GRAPHinsertE(g, edge1, edge2, custos);
			GRAPHinsertE(g, edge2, edge1, custos);
            printf("%d %d %f\n", edge1, edge2, custos);

         }

	return g;
}
