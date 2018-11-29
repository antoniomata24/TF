#ifndef file_h
#define file_h
#include "define.h"
#include "grafs.h"
#include "pqueue.h"

Puzzles *readFile(char *);
FILE *createFileSol(char *);
void printSolutions(FILE *, LGraph *, int *, Puzzles *, int, int);
void printreverse(int *sol, Puzzles *Puzzle, int ini, int fim, int n, FILE *f);

#endif
