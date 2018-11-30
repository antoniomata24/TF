#include "pqueue.h"
#include "file.h"

void mainPQ(Puzzles *Data, FILE *f){
  int * new_sol = NULL, *iniB =NULL, *fimB = NULL;
  int **new_solB = NULL;
  PQueue **Queue = NULL;
  Puzzles *AuxP = NULL;
  Pos *AuxPos = NULL;
  LGraph *Graphs = NULL, *AuxG = NULL, *NewG = NULL;
  int i=0, ini = 0, fim = 0, contador = 0, n=0, custo=0, passos=0, x, y;

  AuxP = Data;
  if (AuxP == NULL) exit(0);

  while (AuxP!=NULL){
    AuxPos = AuxP->Positions;
    NewG = createGraph(AuxP);
    contador = 0;

    switch (Data->mode) {
      case 'A':

        ini=convertV(AuxP->Positions->line, AuxP->Positions->col, AuxP);
        fim=convertV(AuxP->Positions->nPos->line, AuxP->Positions->nPos->col, AuxP);
        new_sol=searchPath(NewG->G, (Queue = iniPQ(NewG->G)), ini, fim);
        printSolutions(f, new_sol, AuxP, ini, fim);

        freePQ(Queue, NewG->G);
        free(new_sol);

        break;

      case 'B':
        new_solB = (int**)malloc(AuxP->nmoves*sizeof(int*));
        if (new_solB==NULL) exit(0);
        iniB = (int*)malloc(AuxP->nmoves*sizeof(int));
        if (iniB==NULL) exit(0);
        fimB = (int*)malloc(AuxP->nmoves*sizeof(int));
        if (fimB==NULL) exit(0);

        contador=0;
        custo=0;
        passos=0;

        while (AuxPos->nPos!=NULL){
          new_solB[contador]=NULL;
          iniB[contador]=convertV(AuxPos->line, AuxPos->col, AuxP);
          fimB[contador]=convertV(AuxPos->nPos->line, AuxPos->nPos->col, AuxP);
          new_solB[contador]=searchPath(NewG->G, (Queue = iniPQ(NewG->G)), iniB[contador], fimB[contador]);

          AuxPos = AuxPos->nPos;
          contador++;
        }

        for (contador=0; contador<AuxP->nmoves-1; contador++){
          if(new_solB[contador]==NULL) exit(0);
        }

        for (contador = (AuxP->nmoves)-2; contador >= 0; contador--){
          n = fimB[contador];
          while(n!=iniB[contador]){
            invertConvertV(n, AuxP, &x, &y);
            custo += AuxP->board[x][y];
            passos++;
            n = new_solB[contador][n];
          }
        }

        for (contador=0; contador<AuxP->nmoves-1; contador++){
          if (contador == 0){
            printSolutionsB(f, new_solB[contador], AuxP, iniB[contador], fimB[contador], custo, passos);
            printSolutionsBSteps(f, new_solB[contador], AuxP, iniB[contador], fimB[contador]);
          } else {
            printSolutionsBSteps(f, new_solB[contador], AuxP, iniB[contador], fimB[contador]);
          }
        }
        fprintf(f,"\n");

        freePQ(Queue, NewG->G);
        for (i=0; i<=contador; i++){
          free(new_solB[i]);
        }
        free(new_solB);
        free(iniB);
        free(fimB);
        break;

      default:

        ini=convertV(AuxPos->line, AuxPos->col, AuxP);
        fim=convertV(AuxPos->nPos->line, AuxPos->nPos->col, AuxP);
        new_sol=searchPath(NewG->G, (Queue = iniPQ(NewG->G)), ini, fim);

        printSolutions(f, new_sol, AuxP, ini, fim);

        freePQ(Queue, NewG->G);
        free(new_sol);

        break;
    }


    if(Graphs==NULL){
      Graphs=NewG;
      AuxG=Graphs;
    } else {
      AuxG->n=NewG;
    }
    AuxG=NewG;
    AuxP=AuxP->nPuzzle;
  }

  freeGraph(Graphs);
}

PQueue **iniPQ(Graph *G){
  PQueue **New = NULL;
  link *Aux = NULL;
  int i = 0, j =0;

  New = (PQueue **)malloc(G->E*sizeof(PQueue*));
  if(New == NULL) exit(0);

  for(i=0; i<G->V; i++){
    New[i]=(PQueue *)malloc(sizeof(PQueue ));
    if (New[i] == NULL) exit(0);
  }

  for(i=0; i<G->V; i++){
    Aux=G->adj[i];

    if(Aux!=NULL){
      New[j]->v=i;
      New[j]->adj=Aux;
      j++;
    }else{
      New[j]->v=i;
      New[j]->adj=NULL;
      j++;
    }
  }

  return New;
}

int *searchPath(Graph *G, PQueue **Q, int source, int dest){
  int *price = NULL;
  int *prev = NULL, *visited = NULL;
  int i=0, visitedP =0, v=0, pmin=INFINITY, u=0, tPrice=0;
  link *aux =NULL;

  if(G->adj[source]==NULL || G->adj[dest]==NULL) return NULL;

  price=(int *)malloc(G->V*sizeof(int));
  if(price == NULL) exit(0);

  for(i=0; i<G->V; i++){
    price[i]=INFINITY;
  }

  visited=(int *)malloc(G->V*sizeof(int));
  if(visited == NULL) exit(0);

  for(i=0; i<G->V; i++){
    visited[i]=0;
  }

  prev=(int *)malloc(G->V*sizeof(int));
  if(prev == NULL) exit(0);

  for(i=0; i<G->V; i++){
    prev[i]=-1;
  }

  price[source]=0;

  visitedP = G->V-1;
  v=source;

  if (source==dest){
    return prev;
  }

  while (vEmpty(visited, G->V)==0){
    pmin=INFINITY;

    v=searchMin(G->V, visited, price);
    aux=Q[v]->adj;
    visited[v]=1;

    while(aux!=NULL){

      if(price[aux->v]>aux->weight+price[v]){
        price[aux->v]=aux->weight+price[v];
        prev[aux->v]=v;
      }

      aux=aux->next;
    }
    if(prev[dest]!=-1){
      free(visited);
      free(price);
      return prev;
    }
  }
  free(visited);
  free(price);
  return prev;
}

int searchMin(int n, int *visited, int *price){
    int min=INFINITY, i, v;

    for(i=0; i<n; i++){
        if(price[i]<min&&visited[i]==0){
            min=price[i];
            v=i;
        }
    }

    return v;
}

int vEmpty(int *Data, int n){
    int i=0;
    for(i=0; i<n; i++){
        if(Data[i]!=1)
            return 0;
    }
    return 1;
}

void freePQ(PQueue **Data, Graph *G){
  int i;

  for(i=0; i<G->V; i++)
    free(Data[i]);

  free(Data);
}
