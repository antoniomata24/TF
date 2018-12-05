#ifndef oper_h
#define oper_h

#include "define.h"

void mainOper(Puzzles *, FILE *);
int validateAllPoints(Puzzles *);
lList *convertAllPoints(Puzzles *);
int *IniHeap(int );
void swap(int *, int *);
void Hinsert(int *, int, int *, int, int *);
void FixDown(int *, int , int , int *);
void FixUp(int *, int, int*);
int *searchPath(Graph *, int , int );
void searchPathC(Graph *, lList **, lList **, Edge *);
void addPathPoint(lList **, int );
void addPathSol(int *, lList **,int , int );
int searchMin(int , int *, int *);
int vEmpty(int *, int );


#endif
