#ifndef pqueue_h
#define pqueue_h

#include "define.h"
#include "grafs.h"

typedef struct _PQueue PQueue;
/*typedef struct _path Path;*/

struct _PQueue{
  int v;
  link *adj;
};

/*struct _path{
  int *points;
  int *price;
  int tprice;
};*/

PQueue **iniPQ(Graph *);
int *searchPath(Graph *, PQueue **, int , int );
int searchMin(int , int *, int *);
int vEmpty(int *, int );
void freePQ(PQueue **, Graph *);


#endif
