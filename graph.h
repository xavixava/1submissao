#ifndef GraphHeader
#define GraphHeader

/* Header file for the definition of the List type */
#include "list.h"

/*
 *  Data type: Item
 *
 *  Description: Pointer to void.
 */
typedef struct GraphStruct Graph;
typedef struct NodeStruct Location;
typedef struct Vector Node;

Graph *GRAPHinit(int v);
void GRAPHinsertE(Graph *g, int index, int adj, float custo);
void GRAPHremoveE(Graph *g, int i, int index);
void GRAPHdestroy(Graph *g);
void GRAPHaddV(Graph *g, int localidade, char *interesse);

int modoC0 (Graph *g, int v, int k);
int vizinho(Graph *g, int v, int *visited, int maxstage, int stage);
int modoD0(Graph *g, int v, int k);
void adjacencia(Graph *g, int v, int *visited, int *adj, int maxstage, int stage);

int getV(Graph *g);
int getE(Graph *g);

Graph *readmaps(FILE* fpmaps);


#endif