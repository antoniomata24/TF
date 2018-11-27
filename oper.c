#include "oper.h"

Sol *mainOper(Puzzles *Data){
  Puzzles *AuxP = NULL;
  AuxP=Data;
  Sol *AllSol = NULL;
  Sol *NewSol = NULL;
  Sol *AuxSol = NULL;

  if(AuxP == NULL){
    exit(0);
  }

  while(AuxP!=NULL){
    switch(AuxP->mode){
      case 'A':
        NewSol = operA(AuxP);
        break;
      case 'B':
        NewSol = operB(AuxP);
        break;
      default:
        NewSol=InicializeSolution(AuxP);
      }
    AuxP=AuxP->nPuzzle;

    if(AllSol==NULL){
      AllSol=NewSol;
    } else {
      AuxSol->nSol=NewSol;
    }
    AuxSol=NewSol;
  }

  return AllSol;
}

Sol *operA(Puzzles *Data){
  int col, line;
  Sol *Solution = NULL;

  col=Data->Positions->col;
  line=Data->Positions->line;

  Solution = InicializeSolution(Data);
  if( col>=0 && line >= 0 && Data->mode == 'A' && Data->nmoves==1 && col<Data->cols && line < Data->lines){
    if(Data->board[line][col]!=0){
      if(ValidateMoveA(line, col, 1, 2, Data)==1){
        computeSolutionA(line+1, col+2, Data, Solution);
      }
      if(ValidateMoveA(line, col, 1, -2, Data)==1){
        computeSolutionA(line+1, col-2, Data, Solution);
      }
      if(ValidateMoveA(line, col, -1, 2, Data)==1){
        computeSolutionA(line-1, col+2, Data, Solution);
      }
      if(ValidateMoveA(line, col, -1, -2, Data)==1){
        computeSolutionA(line-1, col-2, Data, Solution);
      }
      if(ValidateMoveA(line, col, 2, 1, Data)==1){
        computeSolutionA(line+2, col+1, Data, Solution);
      }
      if(ValidateMoveA(line, col, 2, -1, Data)==1){
        computeSolutionA(line+2, col-1, Data, Solution);
      }
      if(ValidateMoveA(line, col, -2, 1, Data)==1){
        computeSolutionA(line-2, col+1, Data, Solution);
      }
      if(ValidateMoveA(line, col, -2, -1, Data)==1){
        computeSolutionA(line-2, col-1, Data, Solution);
      }
    }
  }
  return(Solution);
}

Sol *operB(Puzzles *Data){
  int col1, col2, line1, line2;
  Sol *Solution = NULL;
  Pos *aux = Data->Positions;

  Solution = InicializeSolution(Data);

  while(aux->nPos!=NULL && Data->mode=='B'){
    col1=aux->col;
    col2=aux->nPos->col;
    line1=aux->line;
    line2=aux->nPos->line;
    if(col1<0 || col2<0 || line1<0 || line2<0 || line1>=Data->lines || col1>=Data->cols || line2>=Data->lines||col2>=Data->cols){
        Solution->valid=-1;
        Solution->cost=0;
        break;
    }
    if(line1>=Data->lines || col1>=Data->cols || line2>=Data->lines||col2>=Data->cols){
        Solution->valid=-1;
        Solution->cost=0;
        break;
    }
    if(ValidateMoveB(line1, col1, line2, col2, Data)==1){
      computeSolutionB(line2, col2, Data, Solution);
    }else{
      Solution->valid=-1;
      Solution->cost=0;
      break;
    }
    aux=aux->nPos;
  }
  return(Solution);
}

Sol *InicializeSolution(Puzzles *Data){
  Sol *Solution = NULL;

  Solution = (Sol *)malloc(sizeof(Sol));
  if(Solution==NULL)
    exit(0);

  Solution->nLines = Data->lines;
  Solution->nCols = Data->cols;
  Solution->mode = Data->mode;
  Solution->moves = Data->nmoves;
  Solution->valid=-1;
  Solution->cost=0;
  Solution->nSol = NULL;

  return Solution;
}

void computeSolutionA(int x, int y, Puzzles *Data, Sol *Solution){
  if(Data->board[x][y]<Solution->cost||Solution->cost==0){
    Solution->cost=Data->board[x][y];
    Solution->valid = 1;
  }
}

int ValidateMoveA(int x, int y, int difx, int dify, Puzzles *Data){
  if(x+difx<0 || y+dify < 0 || x+difx>=Data->lines || y+dify>=Data->cols){
    return 0;
  }else if(Data->board[x+difx][y+dify]==0 || Data->board[x][y]==0){
    return 0;
  }else{
    return 1;
  }
}

void computeSolutionB(int x, int y, Puzzles *Data, Sol *Solution){
  Solution->cost+=Data->board[x][y];
  Solution->valid = 1;
}

int ValidateMoveB(int x, int y, int x2, int y2, Puzzles *Data){
  if(Data->board[x][y]==0 || Data->board[x2][y2]==0 ){
    return 0;
  }else if (x>=Data->lines || x2>=Data->lines || y>=Data->cols || y2>=Data->cols){
    return 0;
  } else if(((x-x2) == 1 || (x-x2)== -1)&& ((y-y2)==2 || (y-y2)==-2)){
    return 1;
  }else if(((x-x2) == 2 || (x-x2)== -2)&& ((y-y2)==1 || (y-y2)==-1)){
    return 1;
  } else{
    return 0;
  }
}
