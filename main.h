#ifndef MainHeader
#define MainHeader

#include "list.h"
#include "graph.h"

FILE *Openfile(char *name, char *mode);

char *readprbs(FILE* fpprobs, Graph *g, FILE *out, char *modo);

#endif