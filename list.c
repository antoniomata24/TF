#include "list.h"
#include "define.h"

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
