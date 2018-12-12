/*******************************************************************
* TouristKnights - Projeto AED 2018/2019 MEEC - IST
*
* Author: António da Mata nº90022
*         Rafael Abranches nº90174
*
* File name: list.c
*
* Release date: 2018/12/11
*
* Description: file that has the funtions to free the memory and list related functions
*
*******************************************************************/
/* including the header files used */
#include "list.h"

/******************************************************************************
* NEW()
*
* Arguments: v - absolute value of the vertex
*            next - points to the next free position in the list
*            weight - cost of that turist point
*
* Returns: none
*
* Side-Effects: generates a new node to insert in the list
*
* Description: creates and inserts the new node with the absolute value of v and
*             the cost of weight in the next postition of the list
*
*****************************************************************************/
void NEW(int v, lList **next, short int weight){
  /* allocation of the new node to be inserted */
  link *x = (link *) malloc(sizeof(struct node));
  if (x==NULL) exit(0); /* verification of the allocation */
  /* initialization of the new node */
  x->weight=weight;
  x->v = v;
  InsertListNode(next, x); /* insertion of the new node in the list */
}

/******************************************************************************
* InsertListNode()
*
* Arguments: ListIn - pointer to a list
*            DataIn - generic pointer to some data
*
* Returns: none
*
* Side-Effects: inserts a node in the list
*
* Description: inserts a node with the information given in DataIn in the ListIn
*
*****************************************************************************/
void InsertListNode(lList **ListIn ,Item DataIn){
  /* General Initializations */
  lList *New=NULL; /* new list node */
  lList *Aux=*ListIn; /* auxiliary pointer to the ListIn */

  /* allocation of the new list node */
  New=(lList *)malloc(sizeof(lList ));
  if (New == NULL) exit(0); /* verification of the allocation */
  /* initialization of the list node */
  New->data=DataIn;
  New->next=NULL;
  if(Aux==NULL) /* if the list is empty, New becomes the list */
     *ListIn=New;
  else{ /* else iterate the list until the end and insert New in the end of the list */
    while(Aux->next!=NULL)
      Aux=Aux->next;
    Aux->next=New;
  }
}

/******************************************************************************
* freelList()
*
* Arguments: DataOut - pointer to a linked list
*
* Returns: none
*
* Side-Effects: frees all the memory from the list
*
* Description: frees all the memory from a list with the format of the struct lList
*
*****************************************************************************/
void freelList(lList *DataOut){

  if(DataOut==NULL) /* if there is no more data */
    return;

  /* recursive call of the funtion for it to free the memory from the end to the beggining */
  freelList(DataOut->next);
  /* free all the memory */
  free(DataOut->data);
  free(DataOut);
}

/******************************************************************************
* freeAllPuzzle()
*
* Arguments: Data - pointer to a puzzle
*
* Returns: none
*
* Side-Effects: frees all the memory from the puzzle
*
* Description: frees all the memory from a puzzle with the format of the struct Puzzles
*
*****************************************************************************/
void freeAllPuzzle(Puzzles *Data){

  if(Data == NULL) /* if there is no more data */
    return;

  int i = 0; /* iterator */

  /* recursive call of the funtion for it to free the memory from the end to the beggining */
  freelList(Data->Positions);

  /* free all the memory */
  if(Data->board!=NULL){
    for(i=0; i<Data->lines; i++){
      free(Data->board[i]);
    }
    free(Data->board);
  }
  free(Data);
}

/******************************************************************************
* addPathSol()
*
* Arguments: prev - pointer to a puzzle
*            Path -
*            source -
*            n -
*
* Returns: none
*
* Side-Effects: adds the prev vector to the list Path
*
* Description: adds the prev vector to the list Path converting it
*             from an array to a linked list
*
*****************************************************************************/
void addPathSol(int *prev, lList **Path, int source, int n){
  /* General Initializations */
  lList *AuxList=NULL; /* pointer to the link struct to be inserted */
  lList *NewList = NULL; /* pointer to the head of the list */

  while(n!=source){ /* while there are still path to follow */
    /* allocates memory for an integer to insert in the list*/
    int* data = (int*)malloc(sizeof(int));
    if (data == NULL) exit(0); /* verification of the allocation */
    data[0]=n;
    /* allocates the memory for the list node */
    AuxList=(lList *)malloc(sizeof(lList));
    if (AuxList == NULL) exit(0); /* verification of the allocation */
    /* initializes the list node */
    AuxList->data=data;
    /* inserts the list node in the head */
    AuxList->next=NewList;
    NewList=AuxList;
    n=prev[n];
  }
  /* adds the listed solution to the paths */
  *Path=NewList;
  return;
}
