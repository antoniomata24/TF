#ifndef heap_h
#define heap_h

#include "define.h"

/* definition of the functions used in the heap.c file */
int *IniHeap(int );
void swap(int **, int **, int , int);
void Hinsert(int ** , int *, int, unsigned int *, int **);
int HExtractMin(int **, unsigned int *, int **, int *);
void FixDown(int **, int , int , unsigned int *, int **);
void FixUp(int **, int, unsigned int*, int **);

#endif
