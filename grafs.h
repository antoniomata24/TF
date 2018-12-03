#ifndef grafs_h
#define grafs_h

#include "define.h"

Graph *createGraph (Puzzles *);
Graph *GRAPHinit(int );
void freeGraph(Graph *);
void freeLink(link *);
void invertConvertV(int , Puzzles *, int *, int *);
int convertV(int , int ,Puzzles *);
void GRAPHinsertE(Graph *, int, int, int);
link *NEW(int , link *, int);
int ValidateMoveA(int , int, int , int, Puzzles *);

#endif
