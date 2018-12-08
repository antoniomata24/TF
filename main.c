/*******************************************************************
TouristKnights - Projeto AED 2018/2019 MEEC - IST

Programado por: António da Mata nº90022
                Rafael Abranches nº90174

*******************************************************************/

#include "define.h"

int main(int argc, char *argv[]){

  if (argc != 2 || strstr(argv[1],".cities")== NULL) {
    exit(0);
  }

  readFile(argv[1]);

  return(0);
}
