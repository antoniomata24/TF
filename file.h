#ifndef file_h
#define file_h
#include "define.h"

Puzzles *readFile(char *);
FILE *createFileSol(char *);
void printSolutions(FILE *, int *, Puzzles *, int, int);
void printSolutionsB(FILE *, int *, Puzzles *, int, int, int, int);
void printSolutionsBSteps(FILE *, int *, Puzzles *, int, int);  
void printSolutionsC(FILE *, lList *, Puzzles *);
void printPathList(lList *, Puzzles *, FILE *);
void printreverse(int *, Puzzles *, int , int , int , FILE *);

#endif
