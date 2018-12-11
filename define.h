#ifndef define_h
#define define_h
/* including the necessary libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* definitions of expressions needed */
#define INFINITY 30000
#define lessPri(A, B) ((A) > (B))

/* definition of all the structures used in the program */
typedef struct node link;
typedef struct _Puzzles Puzzles;
typedef struct _Pos Pos;
typedef void * Item;
typedef struct _lList lList;

struct node { /* structure to define the turist points */
  int v;  /* position of the turist point in the board */
  short int weight; /* cost of that turist point */
};

struct _lList{ /* structure to hold data */
  Item data; /* gereric pointer to some data */
  lList *next;  /* point to the next structure */
};

struct _Puzzles{ /* structure holding all the information about the puzzle */
  char mode;  /* saves the mode of the puzzle being analized */
  short int nmoves; /* saves the number of turist points to be used */
  short int lines; /* saves the line dimension of the board */
  short int cols; /* saves the column dimension of the board */
  lList *Positions; /* saves all the turist points to be used */
  short int **board; /* saves the board of the costs of the turist points */
};

struct _Pos{ /* struture holding the information of one turist point */
  short int line; /* information about the line position of the turist point */
  short int col; /* information about the column position of the turist point */
};

/* including all the header files created */
#include "file.h"
#include "heap.h"
#include "list.h"
#include "oper.h"

#endif
