#ifndef GraphHeader
#define GraphHeader

/* Header file for the definition of the List type */
#include "list.h"

typedef struct GraphStruct Graph;
typedef struct NodeStruct Location;
typedef struct Vector Node;

Graph *GRAPHinit(int v, int a);
void GRAPHinsertE(Graph *g, int index, int adj, double custo);
void GRAPHremoveE(Graph *g, int i, int index);
void GRAPHdestroy(Graph *g);
void GRAPHaddV(Graph *g, int localidade, char *interesse);

int modoA0(Graph *g, int v);
double modoB0(Graph *g,int edge1,int edge2);
int modoC0 (Graph *g, int v, int k);
int vizinho(Graph *g, int v, int *visited, int maxstage, int stage, int flag);
int modoD0(Graph *g, int v, int k);
int adjacencia(Graph *g, int v, int *visited, int maxstage, int stage, int count);

int getV(Graph *g);
int getE(Graph *g);

Graph *readmaps(FILE* fpmaps);


#endif
