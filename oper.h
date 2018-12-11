#ifndef oper_h
#define oper_h

#include "define.h"

/* definition of the functions used in the oper.c file */
void mainOper(Puzzles *, FILE *);
lList *findAdj (Puzzles *, int );
int ValidateMoveA(short int , short int, short int , short int, Puzzles *);
int convertV(short int , short int ,Puzzles *);
void invertConvertV(int , Puzzles *, short int *, short int *);
int validateAllPoints(Puzzles *);
lList *convertAllPoints(Puzzles *);
int *searchPath(Puzzles *, int , int );
int searchPathC(Puzzles *, int, int );
void permute(int *, int , int , int ** , Puzzles *, int *, int*);

#endif
