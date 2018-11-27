/*******************************************************************
TouristKnights - Projeto AED 2018/2019 MEEC - IST

Programado por: António da Mata nº90022
                Rafael Abranches nº90174

*******************************************************************/

#include "define.h"
#include "list.h"
#include "file.h"
#include "oper.h"

int main(int argc, char *argv[]){

  FILE *fOut = NULL;
  Puzzles *Puzzle = NULL;
  Sol *Solutions = NULL;
  if (argc != 2) {
    exit(0);
  }

  Puzzle = readFile(argv[1]);
  Solutions = mainOper(Puzzle);

  fOut = createFileSol(argv[1]);
  printSolutions(fOut, Solutions);

  freeAllPuzzle(Puzzle);
  freeSolution(Solutions);
  fclose(fOut);
  return(0);
}
