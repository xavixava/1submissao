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

void readprbs( FILE* fpprobs, int prob, int map);

Graph *readmaps(FILE* fpmaps, int prob, int map);


#endif