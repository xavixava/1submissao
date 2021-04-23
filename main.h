#ifndef MainHeader
#define MainHeader

/* Header file for the definition of the List type */
#include "list.h"
#include "graph.h"

/*
 *  Data type: Item
 *
 *  Description: Pointer to void.
 */
FILE *Openfile(char *name, char *mode);

void readprbs(FILE* fpprobs, Graph *g, FILE *out, int prob);

#endif