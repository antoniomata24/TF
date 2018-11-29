/*******************************************************************
TouristKnights - Projeto AED 2018/2019 MEEC - IST

Programado por: António da Mata nº90022
                Rafael Abranches nº90174

*******************************************************************/

#include "define.h"
#include "list.h"
#include "file.h"
/*#include "oper.h"*/
#include "grafs.h"
#include "pqueue.h"

int main(int argc, char *argv[]){

  FILE *fOut = NULL;
  Puzzles *Puzzle = NULL;
  /*Sol *Solutions = NULL;*/
  LGraph *Graphs = NULL;
  PQueue **Queue = NULL;
  int *sol=NULL;
  int i=0, f=0;

  if (argc != 2) {
    exit(0);
  }

  Puzzle = readFile(argv[1]);
  /*Solutions = mainOper(Puzzle);*/
  Graphs = createGraph(Puzzle);
  i=convertV(Puzzle->Positions->line, Puzzle->Positions->col, Puzzle);
  f=convertV(Puzzle->Positions->nPos->line, Puzzle->Positions->nPos->col, Puzzle);
  sol=searchPath(Graphs->G, (Queue = iniPQ(Graphs->G)), i, f);

  fOut = createFileSol(argv[1]);
  printSolutions(fOut, Graphs, sol, Puzzle, i, f);

  /*freeSolution(Solutions);*/
  freeAllPuzzle(Puzzle);
  freeGraph(Graphs);
  free(sol);
  fclose(fOut);

  return(0);
}
