/* Prevent multiple inclusions */
#ifndef ListHeader
#define ListHeader

typedef struct ListStruct List;

List * initList(void);

int lengthList(List * first);

List * getNextNodeList(List * node);

int getIndexList(List * node);

void insertNextNodeList(List * node, List *next);

List *createEdge(int i, double cost);

double getCustoList(List * node);

/* End of: Protect multiple inclusions                              */
#endif
