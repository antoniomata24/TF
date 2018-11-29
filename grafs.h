#ifndef grafs_h
#define grafs_h

#include <stdlib.h>
#include <stdio.h>
#include "oper.h"
#include "define.h"

typedef struct node link;
typedef struct _graph Graph;
typedef struct _ListG LGraph;


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

struct _ListG{
  Graph *G;
  LGraph *n;
};

LGraph *createGraph (Puzzles *);
Graph *GRAPHinit(int );
void freeGraph(LGraph *);
void freeLink(link *);
int convertV(int , int ,Puzzles *);
void GRAPHinsertE(Graph *, int, int, int);
link *NEW(int , link *, int);
int ValidateMoveA(int , int, int , int, Puzzles *);

#endif
