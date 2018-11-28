#include "pqueue.h"

PQueue **iniPQ(Graph *G){
  PQueue **New = NULL;
  link *Aux = NULL;
  int i = 0, j =0;

  New = (PQueue **)malloc(G->E*sizeof(PQueue*));
  if(New == NULL) exit(0);

  for(i=0; i<G->E; i++){
    New[i]=(PQueue *)malloc(sizeof(PQueue ));
    if (New[i] == NULL) exit(0);
  }

  for(i=0; i<G->V; i++){
    Aux=G->adj[i];

    if(Aux!=NULL){
      New[j]->v=i;
      New[j]->adj=Aux;
      j++;
    }
  }

  return New;
}

int *searchPath(Graph *G, PQueue **Q, int source, int dest){
  int *price = NULL;
  int *prev = NULL;
  int i=0, visitedP =0, v=0, pmin=INFINITY, u=0, tPrice=0;
  link *aux =NULL;

  price=(int *)malloc(G->V*sizeof(int));
  if(price == NULL) exit(0);

  for(i=0; i<G->V; i++){
    price[i]=INFINITY;
  }

  prev=(int *)malloc(G->V*sizeof(int));
  if(prev == NULL) exit(0);

  for(i=0; i<G->V; i++){
    prev[i]=-1;
  }

  price[source]=0;

  visitedP = G->V-1;
  v=source;
  while (visitedP!=0){
    pmin=INFINITY;

    aux=Q[v]->adj;
    while(aux!=NULL){
      if(aux->v!=prev[v]){
        if(aux->weight<pmin){

          if(price[aux->v]>aux->weight+price[v]){
            price[aux->v]=aux->weight+price[v]
          }

          if(price[aux->v]<pmin){
            u=aux->v;
            pmin=price[u];
            prev[u]=v;
          }
        }
      }
      aux=aux->next;
    }
    v=u;
    if(v=dest||prev[v]!=-1){
      return prev;
    }

    visitedP--;
  }
  return NULL;
}
