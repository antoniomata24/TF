/*******************************************************************
TouristKnights - Projeto AED 2018/2019 MEEC - IST

Programado por: António da Mata nº90022
                Rafael Abranches nº90174

*******************************************************************/

#include "define.h"
#include "list.h"
#include "file.h"
#include "oper.h"
#include "grafs.h"

int main(int argc, char *argv[]){

  FILE *fOut = NULL;
  Puzzles *Puzzle = NULL;
  Sol *Solutions = NULL;
  LGraph *Graphs = NULL;

  int i=0;

  if (argc != 2) {
    exit(0);
  }

  Puzzle = readFile(argv[1]);
  Solutions = mainOper(Puzzle);
  Graphs = createGraph(Puzzle);

  fOut = createFileSol(argv[1]);
  printSolutions(fOut, Graphs);

  freeAllPuzzle(Puzzle);
  freeSolution(Solutions);
  freeGraph(Graphs);
  fclose(fOut);

  return(0);
}
