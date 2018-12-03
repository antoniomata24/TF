#ifndef oper_h
#define oper_h

#include "define.h"

void searchPathC(Graph *, PQueue **, lList **, lList **, Edge *);
void addPathSol(int *, lList **,int , int );
void addPathPoint(lList **, int );
lList seachNode(Item, lList *);
lList *convertAllPoints(Puzzles *);
void mainOper(Puzzles *, FILE *);
PQueue **iniPQ(Graph *);
int *searchPath(Graph *, PQueue **, int , int );
int searchMin(int , int *, int *);
int vEmpty(int *, int );
void freePQ(PQueue **, Graph *);
int validateAllPoints(Puzzles *);

#endif
