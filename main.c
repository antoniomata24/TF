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
  Graph *G=NULL;
  link *aux = NULL;

  int i=0;

  if (argc != 2) {
    exit(0);
  }

  Puzzle = readFile(argv[1]);
  Solutions = mainOper(Puzzle);
  Graphs = createGraph(Puzzle);

  G=Graphs->G;
  for(i=0; i<G->V;i++){
    aux=G->adj[i];
    if(aux!=NULL){
      while(aux!=NULL){
        fprintf(fOut, "%d:%d ", aux->x, aux->weight);
        aux=aux->next;
      }
    }
    fprintf(fOut, "-1\n");
  }
  fOut = createFileSol(argv[1]);
  printSolutions(fOut, Solutions);

  freeAllPuzzle(Puzzle);
  freeSolution(Solutions);
  freeGraph(Graphs);
  fclose(fOut);

  return(0);
}
