#ifndef pqueue_h
#define pqueue_h

#include "define.h"
#include "grafs.h"

typedef struct _PQueue PQueue;

struct _PQueue{
  int v;
  link *adj;
};

void mainPQ(Puzzles *, FILE *);
PQueue **iniPQ(Graph *);
int *searchPath(Graph *, PQueue **, int , int );
int searchMin(int , int *, int *);
int vEmpty(int *, int );
void freePQ(PQueue **, Graph *);


#endif
