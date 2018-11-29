#include "pqueue.h"

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
    if(prev[dest]!=-1)
        return prev;
  }
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
