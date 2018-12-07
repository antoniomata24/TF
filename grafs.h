#ifndef grafs_h
#define grafs_h

#include "define.h"

Graph *createGraph (Puzzles *);
Graph *GRAPHinit(int );
void GRAPHinsertE(Graph *, int, int, int);
void NEW(int , lList **, int);
int ValidateMoveA(int , int, int , int, Puzzles *);
int convertV(int , int ,Puzzles *);
void invertConvertV(int , Puzzles *, int *, int *);

#endif
