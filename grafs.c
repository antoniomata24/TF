#include "grafs.h"

Graph *createGraph (Puzzles *Data){

  Puzzles *AuxPuzzle = NULL;
  Graph *NewG=NULL;
  int i, j, vi, vf;
  AuxPuzzle=Data;

  if (AuxPuzzle == NULL)
      exit(0);

  NewG=GRAPHinit((AuxPuzzle->cols)*(AuxPuzzle->lines));
  if(NewG==NULL)
    exit(0);

  if(Data->mode=='A' || Data->mode=='B' || Data->mode=='C'){

    for(i=0; i<Data->lines; i++){
      for(j=0; j<Data->cols; j++){
        vi=convertV(i, j, Data);
        if(ValidateMoveA(i, j, 1, 2, Data)==1){
          vf=convertV(i+1, j+2, Data);
          GRAPHinsertE(NewG, vi, vf, Data->board[i+1][j+2]);
        }
        if(ValidateMoveA(i, j, 1, -2, Data)==1){
          vf=convertV(i+1, j-2, Data);
          GRAPHinsertE(NewG, vi, vf, Data->board[i+1][j-2]);
        }
        if(ValidateMoveA(i, j, -1, 2, Data)==1){
          vf=convertV(i-1, j+2, Data);
          GRAPHinsertE(NewG, vi, vf, Data->board[i-1][j+2]);
        }
        if(ValidateMoveA(i, j, -1, -2, Data)==1){
          vf=convertV(i-1, j-2, Data);
          GRAPHinsertE(NewG, vi, vf, Data->board[i-1][j-2]);
        }
        if(ValidateMoveA(i, j, 2, 1, Data)==1){
          vf=convertV(i+2, j+1, Data);
          GRAPHinsertE(NewG, vi, vf, Data->board[i+2][j+1]);
        }
        if(ValidateMoveA(i, j, 2, -1, Data)==1){
          vf=convertV(i+2, j-1, Data);
          GRAPHinsertE(NewG, vi, vf, Data->board[i+2][j-1]);
        }
        if(ValidateMoveA(i, j, -2, 1, Data)==1){
          vf=convertV(i-2, j+1, Data);
          GRAPHinsertE(NewG, vi, vf, Data->board[i-2][j+1]);
        }
        if(ValidateMoveA(i, j, -2, -1, Data)==1){
          vf=convertV(i-2, j-1, Data);
          GRAPHinsertE(NewG, vi, vf, Data->board[i-2][j-1]);
        }
      }
    }
  }

  return NewG;
}

int convertV(int x, int y,Puzzles *Data){

  int n = 0;

  n=x*Data->cols;
  n+=y;

  return n;
}

void invertConvertV(int n, Puzzles *Data, int *x, int *y){
  (*x)=n/Data->cols;
  (*y)=n-(*x)*Data->cols;
}

void freeGraph(Graph *Data){

  int i=0;

  if(Data==NULL)
    return;

  for(i=0;i<Data->V;i++){
    freeLink(Data->adj[i]);
  }
  free(Data->adj);
  free(Data);
}

void freeLink(link *Data){
  if(Data==NULL)
    return;

  freeLink(Data->next);
  free(Data);

}

link *NEW(int v, link *next, int weight){
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

Graph *GRAPHinit(int V){
  int v;
  Graph *G = (Graph*) malloc(sizeof(Graph));

  G->V = V;
  G->E = 0;
  G->adj = (link **) malloc(V * sizeof(link*));

  for (v = 0; v < V; v++)
    G->adj[v] = NULL;
  return G;
}

void GRAPHinsertE(Graph *G, int v, int w, int weight){
  G->adj[v] = NEW(w, G->adj[v], weight);
  G->E++;
}

int ValidateMoveA(int x, int y, int difx, int dify, Puzzles *Data){
  if(x+difx<0 || y+dify < 0 || x+difx>=Data->lines || y+dify>=Data->cols){
    return 0;
  }else if(Data->board[x+difx][y+dify]==0 || Data->board[x][y]==0){
    return 0;
  }else{
    return 1;
  }
}
