#include "list.h"

void NEW(int v, lList **next, short int weight){
  link *x = (link *) malloc(sizeof(struct node));
  x->weight=weight;
  x->v = v;
  InsertListNode(next, x);
}

void InsertListNode(lList **ListIn ,Item DataIn){
  lList *New=NULL;
  lList *Aux=*ListIn;

  New=(lList *)malloc(sizeof(lList ));
  New->data=DataIn;
  New->next=NULL;
  if(Aux==NULL)
     *ListIn=New;
  else{
    while(Aux->next!=NULL)
      Aux=Aux->next;
    Aux->next=New;
  }
}

void freelList(lList *DataOut){

  if(DataOut==NULL)
    return;

  freelList(DataOut->next);
  free(DataOut->data);
  free(DataOut);
}

void freeAllPuzzle(Puzzles *Data){
  if(Data == NULL)
    return;

  int i = 0;

  freelList(Data->Positions);

  if(Data->board!=NULL){
    for(i=0; i<Data->lines; i++){
      free(Data->board[i]);
    }
    free(Data->board);
  }

  free(Data);
}

void addPathSol(int *prev, lList **Path, int source, int n){

  lList *AuxList=NULL;
  lList *NewList = NULL;

  while(n!=source){
    int* data = (int*)malloc(sizeof(int));
    data[0]=n;
    AuxList=(lList *)malloc(sizeof(lList));
    AuxList->data=data;
    AuxList->next=NewList;
    NewList=AuxList;
    n=prev[n];
  }
  *Path=NewList;
  return;
}
