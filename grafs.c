#include "grafs.h"

LGraph *createGraph (Puzzles *Data){

  Puzzles *AuxPuzzle = NULL;
  Graph *AuxG=NULL;
  LGraph *First = NULL, *NewLG = NULL, *AuxList=NULL;
  int i, j, vi, vf;
  AuxPuzzle=Data;

  if (AuxPuzzle == NULL)
      exit(0);

  while(AuxPuzzle!=NULL){
    NewLG=(LGraph *)malloc(sizeof(LGraph));

    AuxG=GRAPHinit((AuxPuzzle->cols)*(AuxPuzzle->lines));
    if(AuxG==NULL)
      exit(0);

    for(i=0; i<Data->lines; i++){
      for(j=0; j<Data->cols; j++){
        vi=convertV(i, j, Data);
        if(ValidateMoveA(i, j, 1, 2, Data)==1){
          vf=convertV(i+1, j+2, Data);
          GRAPHinsertE(AuxG, vi, vf, Data->board[i+1][j+2]);
        }
        if(ValidateMoveA(i, j, 1, -2, Data)==1){
          vf=convertV(i+1, j-2, Data);
          GRAPHinsertE(AuxG, vi, vf, Data->board[i+1][j-2]);
        }
        if(ValidateMoveA(i, j, -1, 2, Data)==1){
          vf=convertV(i-1, j+2, Data);
          GRAPHinsertE(AuxG, vi, vf, Data->board[i-1][j+2]);
        }
        if(ValidateMoveA(i, j, -1, -2, Data)==1){
          vf=convertV(i-1, j-2, Data);
          GRAPHinsertE(AuxG, vi, vf, Data->board[i-1][j-2]);
        }
        if(ValidateMoveA(i, j, 2, 1, Data)==1){
          vf=convertV(i+2, j+1, Data);
          GRAPHinsertE(AuxG, vi, vf, Data->board[i+2][j+1]);
        }
        if(ValidateMoveA(i, j, 2, -1, Data)==1){
          vf=convertV(i+2, j-1, Data);
          GRAPHinsertE(AuxG, vi, vf, Data->board[i+2][j-1]);
        }
        if(ValidateMoveA(i, j, -2, 1, Data)==1){
          vf=convertV(i-2, j+1, Data);
          GRAPHinsertE(AuxG, vi, vf, Data->board[i-2][j+1]);
        }
        if(ValidateMoveA(i, j, -2, -1, Data)==1){
          vf=convertV(i-2, j-1, Data);
          GRAPHinsertE(AuxG, vi, vf, Data->board[i-2][j-1]);
        }
      }
    }

    NewLG->G=AuxG;
    NewLG->n=NULL;
    if(First == NULL){
      First = NewLG;
      AuxList=NewLG;
    } else {
      AuxList->n = NewLG;
      AuxList=NewLG;
    }
    AuxPuzzle=AuxPuzzle->nPuzzle;
  }

  return First;

}

int convertV(int x, int y,Puzzles *Data){

  int n = 0;

  n=x*Data->cols;
  n+=y;

  return n;
}

void freeGraph(LGraph *Data){

  int i=0;

  if(Data==NULL)
    return;

  freeGraph(Data->n);
  for(i=0;i<Data->G->V;i++){
    freeLink(Data->G->adj[i]);
  }
  free(Data->G->adj);
  free(Data->G);
  free(Data);
}

void freeLink(link *Data){
  if(Data==NULL)
    return;

  freeLink(Data->next);
  free(Data);

}

link *NEW(int v, link *next, int weight)
{
  link *aux = next;
  link *first = next;
  link *x = (link *) malloc(sizeof(struct node));
  x->weight=weight;
  x->v = v;
  if(next==NULL){
    x ->next = next;
    return x;
  }else{
    while(aux->next!=NULL)
      aux=aux->next;
    aux->next=x;
    x->next=NULL;
    return first;
  }
}

Graph *GRAPHinit(int V)
{
  int v;
  Graph *G = (Graph*) malloc(sizeof(Graph));

  G->V = V;
  G->E = 0;
  G->adj = (link **) malloc(V * sizeof(link*));

  for (v = 0; v < V; v++)
    G->adj[v] = NULL;
  return G;
}

void GRAPHinsertE(Graph *G, int v, int w, int weight)
{
  G->adj[v] = NEW(w, G->adj[v], weight);
  /*G->adj[w] = NEW(v, G->adj[w], weight);*/
  G->E++;
}
