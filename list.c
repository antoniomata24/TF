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

/* addPathPoint - add a single point to the Path list computed by the "searchPathC"
                fuction

  \param Path - linked list with link structs that contain all path points where
                a single path point will be inserted (at the end of the list)
  \param n - absolute value of the path point to be inserted in the path list
*/
void addPathPoint(lList **Path, int n){
  lList *NewList = *Path;
  int* data = (int*)malloc(sizeof(int));

    data[0]=n;
    InsertListNode(&NewList, data);
    *Path=NewList;
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
