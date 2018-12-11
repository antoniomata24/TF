/*******************************************************************
* TouristKnights - Projeto AED 2018/2019 MEEC - IST
*
* Author: António da Mata nº90022
*         Rafael Abranches nº90174
*
* File name: main.c
*
* Release date: 2018/12/11
*
* Description: main file to the program that calls the functions
*            for everything to work
*
*******************************************************************/
/* including the header files used */
#include "define.h"

/******************************************************************************
* main()
*
* Arguments: argc - number of comand line arguments
*            argv - array of pointers to command line arguments
* Returns: success
*
* Side-Effects: Creates a file with the solution of the entry file
*
* Description: main funtion to the program, it checks if the entry arguments
*				     are according to the requirements
*
*****************************************************************************/
int main(int argc, char *argv[]){

  /* checks number of argumentes and if the file has the required extention */
  if (argc != 2 || strstr(argv[1],".cities")== NULL) {
    exit(0);
  }

  /* calls the funcion that will read the file, process all the information,
  * compute a solution and print it to a created file with the required extention */
  readFile(argv[1]);

  return(0);
}
