#include "grafs.h"

lList *findAdj (Puzzles *Data, int n){

  Puzzles *AuxPuzzle = NULL;
  lList *lAdj=NULL;
  short int i=0, j=0;
  int vi, vf;
  AuxPuzzle=Data;

  if (AuxPuzzle == NULL)
      exit(0);

  if(Data->mode=='A' || Data->mode=='B' || Data->mode=='C'){

        vi=n;
        invertConvertV(vi, Data, &i, &j);
        if(ValidateMoveA(i, j, 1, 2, Data)==1){
          vf=convertV(i+1, j+2, Data);
          NEW(vf, &lAdj, Data->board[i+1][j+2]);
        }
        if(ValidateMoveA(i, j, 1, -2, Data)==1){
          vf=convertV(i+1, j-2, Data);
          NEW(vf, &lAdj, Data->board[i+1][j-2]);
        }
        if(ValidateMoveA(i, j, -1, 2, Data)==1){
          vf=convertV(i-1, j+2, Data);
          NEW(vf, &lAdj, Data->board[i-1][j+2]);
        }
        if(ValidateMoveA(i, j, -1, -2, Data)==1){
          vf=convertV(i-1, j-2, Data);
          NEW(vf, &lAdj, Data->board[i-1][j-2]);
        }
        if(ValidateMoveA(i, j, 2, 1, Data)==1){
          vf=convertV(i+2, j+1, Data);
          NEW(vf, &lAdj, Data->board[i+2][j+1]);
        }
        if(ValidateMoveA(i, j, 2, -1, Data)==1){
          vf=convertV(i+2, j-1, Data);
          NEW(vf, &lAdj, Data->board[i+2][j-1]);
        }
        if(ValidateMoveA(i, j, -2, 1, Data)==1){
          vf=convertV(i-2, j+1, Data);
          NEW(vf, &lAdj,Data->board[i-2][j+1]);
        }
        if(ValidateMoveA(i, j, -2, -1, Data)==1){
          vf=convertV(i-2, j-1, Data);
          NEW(vf, &lAdj, Data->board[i-2][j-1]);
        }
  }

  return lAdj;
}

void NEW(int v, lList **next, short int weight){
  link *x = (link *) malloc(sizeof(struct node));
  x->weight=weight;
  x->v = v;
  InsertListNode(next, x);
}

int ValidateMoveA(short int x, short int y, short int difx, short int dify, Puzzles *Data){
  if(x+difx<0 || y+dify < 0 || x+difx>=Data->lines || y+dify>=Data->cols){
    return 0;
  }else if(Data->board[x+difx][y+dify]==0 || Data->board[x][y]==0){
    return 0;
  }else{
    return 1;
  }
}

int convertV(short int x, short int y,Puzzles *Data){

  int n = 0;

  n=x*Data->cols;
  n+=y;

  return n;
}

void invertConvertV(int n, Puzzles *Data, short int *x, short int *y){
  (*x)=n/Data->cols;
  (*y)=n-(*x)*Data->cols;
}
