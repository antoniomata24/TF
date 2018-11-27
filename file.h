#ifndef file_h
#define file_h
#include "define.h"
#include "grafs.h"

Puzzles *readFile(char *);
FILE *createFileSol(char *);
void printSolutions(FILE *, LGraph *);
#endif
