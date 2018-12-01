#include "list.h"
#include "define.h"

lList *InsertListNode(lList *ListIn ,Item DataIn){
  lList *New=NULL;
  lList *First = ListIn, *Aux=ListIn;

  New=(lList *)malloc(sizeof(lList));
  New->data=DataIn;
  New->next=NULL;
  if(First==NULL)
    return New;
  else{
    while(Aux->next!=NULL)
      Aux=Aux->next;
    Aux->next=New;
    return First;
  }
}

lList *freeNode(Item DataOut, lList *First){

  lList *FList = First;
  lList *Aux = First;
  lList *Prev = NULL;
  if (Aux!=NULL && Aux->data==DataOut) {
    First=Aux->next;
    free(Aux->data);
    free(Aux);
    return FList;
  }

  while (Aux!=NULL&&Aux->data!=DataOut) {
    Prev=Aux;
    Aux=Aux->next;
  }

  if(Aux==NULL)
    return FList;

  Prev->next=Aux->next;
  free(Aux->data);
  free(Aux);

  return FList;
}

void freeAllPuzzle(Puzzles *Data){
  if(Data == NULL)
    return;

  int i = 0;

  freeAllPuzzle(Data->nPuzzle);
  freePosition(Data->Positions);

  if(Data->board!=NULL){
    for(i=0; i<Data->lines; i++){
      free(Data->board[i]);
    }
    free(Data->board);
  }

  free(Data);
}

void freePosition(Pos *Data){
  if(Data==NULL)
    return;

  freePosition(Data->nPos);

  free(Data);
}

void freeSolution(Sol *Data){
  if(Data==NULL)
    return;

  freeSolution(Data->nSol);
  free(Data);
}
