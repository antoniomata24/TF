#ifndef file_h
#define file_h

#include "define.h"

/* definition of the functions used in the file.c file */
void readFile(char *);
FILE *createFileSol(char *);
void printSolutions(FILE *, int *, Puzzles *, int, int);
void printPathList(lList *, Puzzles *, FILE *);
void printreverse(int *, Puzzles *, int , int , int , FILE *);

#endif
