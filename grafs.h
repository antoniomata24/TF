#ifndef grafs_h
#define grafs_h

#include "define.h"

lList *findAdj (Puzzles *, int );
void NEW(int , lList **, short int);
int ValidateMoveA(short int , short int, short int , short int, Puzzles *);
int convertV(short int , short int ,Puzzles *);
void invertConvertV(int , Puzzles *, short int *, short int *);

#endif
