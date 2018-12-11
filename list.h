#ifndef list_h
#define list_h
#include "define.h"

void NEW(int , lList **, short int);
void InsertListNode(lList **, Item);
void freelList(lList *);
void freeAllPuzzle(Puzzles *);
void addPathSol(int *, lList **,int , int );

#endif
