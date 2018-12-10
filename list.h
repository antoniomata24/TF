#ifndef list_h
#define list_h
#include "define.h"

void NEW(int , lList **, short int);
void InsertListNode(lList **, Item);
void freeNode(Item , lList **);
void freelList(lList *);
void freeAllPuzzle(Puzzles *);
void addPathPoint(lList **, int );
void addPathSol(int *, lList **,int , int );

#endif
