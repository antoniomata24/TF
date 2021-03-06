#ifndef pqueue_h
#define pqueue_h

#include "define.h"
#include "grafs.h"
#include "list.h"

typedef struct _PQueue PQueue;

struct _PQueue{
  int v;
  link *adj;
};

void searchPathC(Graph *, PQueue **, lList **, lList **, Edge *);
void addPathSol(int *, lList **, Graph *, int , int );
void addPathPoint(lList **, Graph *, int );
lList seachNode(Item, lList *);
lList *convertAllPoints(Puzzles *);
void mainPQ(Puzzles *, FILE *);
PQueue **iniPQ(Graph *);
int *searchPath(Graph *, PQueue **, int , int );
int searchMin(int , int *, int *);
int vEmpty(int *, int );
void freePQ(PQueue **, Graph *);


#endif
