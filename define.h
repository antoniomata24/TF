#ifndef define_h
#define define_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFINITY 5000
#define lessPri(A, B) ((A) > (B))

typedef struct node link;
typedef struct _graph Graph;
typedef struct _Puzzles Puzzles;
typedef struct _Pos Pos;
typedef void * Item;
typedef struct _lList lList;

struct node {
  int v;
  short int weight;
};

struct _graph{
  int V;
  int E;
  lList **adj;
};

typedef struct _edge{
  int v;
  short int w;
}Edge;

struct _lList{
  Item data;
  lList *next;
};

struct _Puzzles{
  char mode;
  short int nmoves;
  short int lines;
  short int cols;
  lList *Positions;
  short int **board;
};

struct _Pos{
  short int line;
  short int col;
};

#include "oper.h"
#include "grafs.h"
#include "file.h"
#include "list.h"

#endif
