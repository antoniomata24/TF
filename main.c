/*******************************************************************
TouristKnights - Projeto AED 2018/2019 MEEC - IST

Programado por: António da Mata nº90022
                Rafael Abranches nº90174

*******************************************************************/

#include "define.h"
#include "list.h"
#include "file.h"
#include "grafs.h"
#include "pqueue.h"

int main(int argc, char *argv[]){

  FILE *fOut = NULL;
  Puzzles *Puzzle = NULL;

  if (argc != 2) {
    exit(0);
  }

  Puzzle = readFile(argv[1]);

  fOut = createFileSol(argv[1]);

  mainPQ(Puzzle, fOut);

  freeAllPuzzle(Puzzle);
  fclose(fOut);

  return(0);
}
