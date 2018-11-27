#ifndef file_h
#define file_h
#include "define.h"

Puzzles *readFile(char *);
FILE *createFileSol(char *);
void printSolutions(FILE *, Sol *);
#endif
