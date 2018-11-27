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
                                          strlen(".valid") + 1)*sizeof(char));
  if (string == NULL)
    exit(0);

  len = strlen(nomef)-strlen(".cities");
  strncpy(string, nomef, len);
  strcat(string, ".valid");

  f1=fopen(string, "w");
  if(f1==NULL)
    exit(0);

  free(string);
  return f1;
}

void printSolutions(FILE *f, LGraph *Graphs){
  int i = 0;
  Graph *G = NULL;
  link *aux = NULL;

  G=Graphs->G;

  for(i=0; i<G->V;i++){
    aux=G->adj[i];
    if(aux==NULL){
      fprintf(f,"%d-> -1\n", i);
    }else{
      fprintf(f,"%d-> ", i);
      while(aux!=NULL){
        fprintf(f, "%d:%d ", aux->v, aux->weight);
        aux=aux->next;
      }
      fprintf(f,"-1\n");
    }
  }
}
