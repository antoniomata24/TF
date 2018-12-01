#include "file.h"

Puzzles *readFile(char *nomef){

  FILE *fi = NULL;
  Puzzles *AllPuzzle = NULL;
  Puzzles *AuxPuzzle, *NewPuzzle = NULL;
  Pos *AuxPos = NULL, *NewPos = NULL;

  int nCols, nLines, moves;
  char mode;
  int i=0, j=0, p=0;
  int dumb;

  fi = fopen(nomef, "r");

  if(fi == NULL){
    exit(0);
  }

  while(fscanf(fi, "%d %d %c %d", &nLines, &nCols, &mode, &moves)==4){

    NewPuzzle = (Puzzles *)malloc(sizeof(Puzzles));
    if(NewPuzzle == NULL){
      exit(0);
    }

    NewPuzzle->mode = mode;
    NewPuzzle->nmoves = moves;
    NewPuzzle->cols = nCols;
    NewPuzzle->lines = nLines;
    NewPuzzle->Positions = NULL;

    for(i=0; i<moves; i++){
        NewPos=(Pos *)malloc(sizeof(Pos));
        if(NewPos == NULL){
          exit(0);
        }

        p = fscanf(fi, "%d %d", &NewPos->line, &NewPos->col);
        if(p!=2)
          exit(0);
        NewPos->nPos = NULL;
      if(NewPuzzle->Positions==NULL){
        NewPuzzle->Positions = NewPos;
      }else{
        AuxPos->nPos = NewPos;
      }
        AuxPos = NewPos;
    }

    if(mode=='A'||mode=='B'){
      NewPuzzle->board = (int **)malloc(nLines*sizeof(int *));
      if(NewPuzzle->board == NULL){
        exit(0);
      }
      for(i=0; i<nLines; i++){
        NewPuzzle->board[i]=(int *)malloc(nCols*sizeof(int));
        if(NewPuzzle->board[i] == NULL){
          exit(0);
        }
      }

      for(i=0; i<nLines; i++){
        for(j=0; j<nCols; j++){
        p = fscanf(fi, "%d", &NewPuzzle->board[i][j]);
        if(p!=1)
          exit(0);
        }
      }
    }else{
      NewPuzzle->board=NULL;
      for(i=0; i<nLines; i++){
        for(j=0; j<nCols; j++){
        p = fscanf(fi, "%d", &dumb);
        if(p!=1)
          exit(0);
        }
      }
    }
    NewPuzzle -> nPuzzle = NULL;
    if(AllPuzzle == NULL)
      AllPuzzle = NewPuzzle;
    else
      AuxPuzzle->nPuzzle = NewPuzzle;

    AuxPuzzle = NewPuzzle;

  }
  fclose(fi);
  return AllPuzzle;
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

void printSolutions(FILE *f, int *sol, Puzzles *Puzzle,
                    int ini, int fim){
  int custo=0, passos=0, x=0, y=0, n;

  n=fim;
  if (sol == NULL){
    custo = -1;
    passos = 0;
    fprintf(f, "%d %d %c %d %d %d\n\n", Puzzle->lines, Puzzle->cols, Puzzle->mode,
                                      Puzzle->nmoves , custo, passos);
    return;
  }

  while(n!=ini){
    invertConvertV(n, Puzzle, &x, &y);
    custo += Puzzle->board[x][y];
    passos++;
    n=sol[n];
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

void printreverse(int *sol, Puzzles *Puzzle, int ini, int fim, int n, FILE *f){
  if (n!=ini){
    printreverse(sol, Puzzle, ini, fim, sol[n], f);

    int x=0, y=0;

    invertConvertV(n, Puzzle, &x, &y);
    fprintf(f, "%d %d %d\n", x, y, Puzzle->board[x][y]);
  }
}
