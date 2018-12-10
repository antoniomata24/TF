#ifndef oper_h
#define oper_h

#include "define.h"

void mainOper(Puzzles *, FILE *);
int validateAllPoints(Puzzles *);
lList *convertAllPoints(Puzzles *);
int *IniHeap(int );
void swap(int **, int **, int , int);
void Hinsert(int ** , int *, int, unsigned int *, int **);
int HExtractMin(int **, unsigned int *, int **, int *);
void FixDown(int **, int , int , unsigned int *, int **);
void FixUp(int **, int, unsigned int*, int **);
int *searchPath(Puzzles *, int , int );
lList **searchPathC(Puzzles *, int, int *);
void searchAllPath(Puzzles *, int , int *, int , int*, lList**);
void addPathPoint(lList **, int );
void addPathSol(int *, lList **,int , int );
int searchMin(int , int *, int *);
int vEmpty(int *, int );
int **matrixInit(int , int , int );


#endif
