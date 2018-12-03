#ifndef define_h
#define define_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFINITY 999999

typedef struct node link;
typedef struct _graph Graph;
typedef struct _Puzzles Puzzles;
typedef struct _Pos Pos;
typedef void * Item;
typedef struct _lList lList;
typedef struct _PQueue PQueue;

struct _PQueue{
  int v;
  link *adj;
};

struct node {
  int v;
  int weight;
  link *next;
};

struct _graph{
  int V;
  int E;
  link **adj;
};

typedef struct _edge{
  int v;
  int w;
}Edge;

struct _lList{
  Item data;
  lList *next;
};

struct _Puzzles{
  char mode;
  int nmoves;
  int lines;
  int cols;
  Pos *Positions;
  int **board;
  Puzzles *nPuzzle;
};

struct _Pos{
  int line;
  int col;
  Pos *nPos;
};

#include "oper.h"
#include "grafs.h"
#include "file.h"
#include "list.h"

#endif
