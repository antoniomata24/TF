#ifndef file_h
#define file_h
#include "define.h"
#include "grafs.h"
#include "pqueue.h"

Puzzles *readFile(char *);
FILE *createFileSol(char *);
void printSolutions(FILE *, int *, Puzzles *, int, int);
void printSolutionsB(FILE *, int *, Puzzles *, int, int, int, int);
void printSolutionsBSteps(FILE *, int *, Puzzles *, int, int);
void printreverse(int *, Puzzles *, int , int , int , FILE *);

#endif
