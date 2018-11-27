#ifndef define_h
#define define_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Puzzles Puzzles;
typedef struct _Pos Pos;
typedef struct _Sol Sol;

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

struct _Sol{
  int nLines;
  int nCols;
  int mode;
  int moves;
  int valid;
  int cost;
  Sol *nSol;
};

#endif
