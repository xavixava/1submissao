#ifndef GraphHeader
#define GraphHeader

/* Header file for the definition of the Item type */
#include "defs.h"

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
void GRAPHinsertE(Graph *g, List *l, int index);
void GRAPHremoveE(Graph *g, int i, int index);
void GRAPHdestroy(Graph *g);
void GRAPHaddV(Graph *g, Location *n);

Item getItemList(Node *node);

#endif