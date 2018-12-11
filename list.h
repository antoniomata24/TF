#ifndef list_h
#define list_h

#include "define.h"

/* definition of the functions used in the list.c file */
void NEW(int , lList **, short int);
void InsertListNode(lList **, Item);
void freelList(lList *);
void freeAllPuzzle(Puzzles *);
void addPathSol(int *, lList **,int , int );

#endif
