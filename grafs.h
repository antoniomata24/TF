#ifndef grafs_h
#define grafs_h

#include "define.h"

Graph *createGraph (Puzzles *);
Graph *GRAPHinit(int );
void GRAPHinsertE(Graph *, int, int, short int);
void NEW(int , lList **, short int);
int ValidateMoveA(int , int, int , int, Puzzles *);
int convertV(short int , short int ,Puzzles *);
void invertConvertV(int , Puzzles *, short int *, short int *);

#endif
