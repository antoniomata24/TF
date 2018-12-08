#include "file.h"

void readFile(char *nomef){

  FILE *fi = NULL, *fOut = NULL;
  Puzzles *Puzzle = NULL;
  Pos *NewPos = NULL;

  int nCols, nLines, moves;
  char mode;
  int i=0, j=0, p=0, val=0;
  int dumb;


  fi = fopen(nomef, "r");

  if(fi == NULL){
    exit(0);
  }

  fOut = createFileSol(nomef);

  while(fscanf(fi, "%d %d %c %d", &nLines, &nCols, &mode, &moves)==4){

    val=0;

    Puzzle = (Puzzles *)malloc(sizeof(Puzzles));
    if(Puzzle == NULL){
      exit(0);
    }

    Puzzle->mode = mode;
    Puzzle->nmoves = moves;
    Puzzle->cols = nCols;
    Puzzle->lines = nLines;
    Puzzle->Positions = NULL;

    if((Puzzle->mode== 'A' && Puzzle->nmoves!=2)||
       (Puzzle->mode== 'B' && Puzzle->nmoves<2)||
       (Puzzle->mode== 'C' && Puzzle->nmoves<2)){

      printSolutions(fOut, NULL, Puzzle, 0, 0);
      val=1;
      for(i=0; i<moves; i++){
          p = fscanf(fi, "%d %d", &dumb, &dumb);
          if(p!=2)
            exit(0);
      }
      Puzzle->board=NULL;
      for(i=0; i<nLines; i++){
        for(j=0; j<nCols; j++){
        p = fscanf(fi, "%d", &dumb);
        if(p!=1)
          exit(0);
        }
      }
      free(Puzzle);
    }

    if(val==0){
      for(i=0; i<moves; i++){
          NewPos=NULL;
          NewPos=(Pos *)malloc(sizeof(Pos));
          if(NewPos == NULL){
            exit(0);
          }

          p = fscanf(fi, "%d %d", &NewPos->line, &NewPos->col);
          if(p!=2)
            exit(0);
          InsertListNode(&Puzzle->Positions, NewPos);
      }

      if(mode=='A'||mode=='B'||mode=='C'){
        Puzzle->board = (int **)malloc(nLines*sizeof(int *));
        if(Puzzle->board == NULL){
          exit(0);
        }
        for(i=0; i<nLines; i++){
          Puzzle->board[i]=(int *)malloc(nCols*sizeof(int));
          if(Puzzle->board[i] == NULL){
            exit(0);
          }
        }

        for(i=0; i<nLines; i++){
          for(j=0; j<nCols; j++){
          p = fscanf(fi, "%d", &Puzzle->board[i][j]);
          if(p!=1)
            exit(0);
          }
        }
      }else{
        Puzzle->board=NULL;
        for(i=0; i<nLines; i++){
          for(j=0; j<nCols; j++){
          p = fscanf(fi, "%d", &dumb);
          if(p!=1)
            exit(0);
          }
        }
      }

      mainOper(Puzzle, fOut);
      freeAllPuzzle(Puzzle);
    }
  }
  fclose(fi);
  fclose(fOut);
}

FILE *createFileSol(char *nomef){
  FILE *f1 = NULL;
  char *string = NULL;
  int len = 0;

  string = (char*)calloc(1, (strlen(nomef) - strlen(".cities") +
                                          strlen(".walks") + 1)*sizeof(char));
  if (string == NULL)
    exit(0);

  len = strlen(nomef)-strlen(".cities");
  strncpy(string, nomef, len);
  strcat(string, ".walks");

  f1=fopen(string, "w");
  if(f1==NULL)
    exit(0);

  free(string);
  return f1;
}

void printSolutions(FILE *f, int *sol, Puzzles *Puzzle, int ini, int fim){
  int custo=0, passos=0, x=0, y=0, n;

  n=fim;
  if (sol == NULL){
    custo = -1;
    passos = 0;
    fprintf(f, "%d %d %c %d %d %d\n\n", Puzzle->lines, Puzzle->cols, Puzzle->mode,
                                      Puzzle->nmoves , custo, passos);
    return;
  }

  if(ini!=fim){
    while(n!=ini){
      invertConvertV(n, Puzzle, &x, &y);
      custo += Puzzle->board[x][y];
      passos++;
      n=sol[n];
      }
  }

  fprintf(f, "%d %d %c %d %d %d\n", Puzzle->lines, Puzzle->cols, Puzzle->mode,
                                    Puzzle->nmoves , custo, passos);

  printreverse(sol, Puzzle, ini, fim, fim, f);

  fprintf(f,"\n");

}

void printSolutionsB(FILE *f, int *sol, Puzzles *Puzzle,
                    int ini, int fim, int custo, int passos){

  if (sol == NULL){
    custo = -1;
    passos = 0;
    fprintf(f, "%d %d %c %d %d %d\n\n", Puzzle->lines, Puzzle->cols, Puzzle->mode,
                                      Puzzle->nmoves , custo, passos);
    return;
  }

  fprintf(f, "%d %d %c %d %d %d\n", Puzzle->lines, Puzzle->cols, Puzzle->mode,
                                    Puzzle->nmoves , custo, passos);
}

void printSolutionsBSteps(FILE *f, int *sol, Puzzles *Puzzle,
                          int ini, int fim){

  printreverse(sol, Puzzle, ini, fim, fim, f);

}

void printSolutionsC(FILE *f, lList *Sol, Puzzles *Puzzle){
  int custo=0, passos=0, x=0, y=0;
  Edge *AuxE=NULL;
  lList *AuxL = Sol;

  if (Sol == NULL){
    custo = -1;
    passos = 0;
    fprintf(f, "%d %d %c %d %d %d\n\n", Puzzle->lines, Puzzle->cols, Puzzle->mode,
                                      Puzzle->nmoves , custo, passos);
    return;
  }

  while(AuxL!=NULL){
    AuxE=AuxL->data;
    invertConvertV(AuxE->v, Puzzle, &x, &y);
    custo += Puzzle->board[x][y];
    passos++;
    AuxL=AuxL->next;
  }

  fprintf(f, "%d %d %c %d %d %d\n", Puzzle->lines, Puzzle->cols, Puzzle->mode,
                                    Puzzle->nmoves , custo, passos);

  printPathList(Sol, Puzzle, f);

  fprintf(f,"\n");

}

void printPathList(lList *Sol, Puzzles *P, FILE *fOut){
  Edge *AuxE = NULL;
  lList *AuxL = Sol;
  int x=0, y=0;

  while(AuxL!=NULL){
    AuxE=AuxL->data;
    invertConvertV(AuxE->v, P, &x, &y);
    fprintf(fOut, "%d %d %d\n", x, y, P->board[x][y]);
    AuxL=AuxL->next;
  }

}

void printreverse(int *sol, Puzzles *Puzzle, int ini, int fim, int n, FILE *f){
  if (n!=ini){
    printreverse(sol, Puzzle, ini, fim, sol[n], f);

    int x=0, y=0;

    invertConvertV(n, Puzzle, &x, &y);
    fprintf(f, "%d %d %d\n", x, y, Puzzle->board[x][y]);
  }
}
