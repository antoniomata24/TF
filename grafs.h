#ifndef grafs_h
#define grafs_h

#include "define.h"

Graph *createGraph (Puzzles *);
Graph *GRAPHinit(int );
void invertConvertV(int , Puzzles *, int *, int *);
int convertV(int , int ,Puzzles *);
void GRAPHinsertE(Graph *, int, int, int);
void NEW(int , lList **, int);
int ValidateMoveA(int , int, int , int, Puzzles *);

#endif
