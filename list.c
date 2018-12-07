#include "list.h"

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

void freeNode(Item DataOut, lList **First){
  lList *Aux = *First;
  lList *Prev = NULL;
  if (Aux!=NULL && Aux->data==DataOut) {
    *First=Aux->next;
    free(Aux->data);
    free(Aux);
  }else{
      if (Aux!=NULL && Aux->next==NULL &&Aux->data==DataOut) {
        free(Aux->data);
        free(Aux);
        *First=NULL;
        return;
      }

      while (Aux!=NULL&&Aux->data!=DataOut) {
        Prev=Aux;
        Aux=Aux->next;
      }
      Prev->next=Aux->next;
      free(Aux->data);
      free(Aux);
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

void freeGraph(Graph *Data){

  int i=0;

  if(Data==NULL)
    return;

  for(i=0;i<Data->V;i++){
    freelList(Data->adj[i]);
  }
  free(Data->adj);
  free(Data);
}

void freePQ(PQueue **Data, Graph *G){
  int i;

  for(i=0; i<G->V; i++){
    free(Data[i]);
  }
  free(Data);
}
