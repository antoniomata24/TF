/*******************************************************************
* TouristKnights - Projeto AED 2018/2019 MEEC - IST
*
* Author: António da Mata nº90022
*         Rafael Abranches nº90174
*
* File name: file.c
*
* Release date: 2018/12/11
*
* Description: file that has the funtions to read the problems and write the solutions of the puzzles
*
*******************************************************************/
/* including the header files used */
#include "file.h"

/******************************************************************************
* readFile()
*
* Arguments: nomef - name of the entry file
*
* Returns: none
*
* Side-Effects: generates a file with the solutions to the puzzles
*
* Description: reads the puzzles one by one and processes the information on each puzzle
*             creating a structure with all the informations to each puzzle
*
*****************************************************************************/
void readFile(char *nomef){
  /* General Initializations */
  FILE *fi = NULL, *fOut = NULL; /* File pointers, file in and file out */
  Puzzles *Puzzle = NULL; /* Pointer to each puzzle's information */
  Pos *NewPos = NULL; /* auxiliary pointer so temporarily save the information about each position */
  short int nCols, nLines, moves; /* information about the columns, lines and moves to each puzzle */
  char mode; /* mode of each puzzle */
  int i=0, j=0, p=0, val=0; /* iterators and validation flag */
  int dumb; /* dummy integer */


  fi = fopen(nomef, "r"); /* opens the entry file */

  if(fi == NULL){ /* if there is no file with such name it exits the program */
    exit(0);
  }

  fOut = createFileSol(nomef); /* creates the exit file */
  if (fOut==NULL) exit(0); /* if there is no file created it exits the program */

  /* while there are still puzzles to be solved it reads the first line of each puzzle */
  while(fscanf(fi, "%hi %hi %c %hi", &nLines, &nCols, &mode, &moves)==4){
    /* reinitialize the validation flag */
    val=0;

    Puzzle = (Puzzles *)malloc(sizeof(Puzzles)); /* allocates memory for one puzzle */
    if(Puzzle == NULL){ /* verification of the allocation */
      exit(0);
    }

    /* saves the information about the puzzle */
    Puzzle->mode = mode;
    Puzzle->nmoves = moves;
    Puzzle->cols = nCols;
    Puzzle->lines = nLines;
    Puzzle->Positions = NULL;

    /* if the moves of the puzzle are invalid, prints invalid solution */
    if((Puzzle->mode== 'A' && Puzzle->nmoves!=2)||
       (Puzzle->mode== 'B' && Puzzle->nmoves<2)||
       (Puzzle->mode== 'C' && Puzzle->nmoves<2)){

      printSolutions(fOut, NULL, Puzzle, 0, 0);
      val=1; /* validation flag change */
      for(i=0; i<moves; i++){ /* reads the rest of the information to a dummy integer */
          p = fscanf(fi, "%d %d", &dumb, &dumb);
          if(p!=2) /* if it doesn't read two integers it exits the program */
            exit(0);
      }
      Puzzle->board=NULL;
      /* reads the rest of the information to a dummy integer */
      for(i=0; i<nLines; i++){
        for(j=0; j<nCols; j++){
        p = fscanf(fi, "%d", &dumb);
        if(p!=1) /* if it doesn't read one integer it exits the program */
          exit(0);
        }
      }
      /* free the memory used */
      free(Puzzle);
    }

    if(val==0){ /* if the puzzle is valid */
      for(i=0; i<moves; i++){ /* saves all the postitions in the position list in the struct Puzzles */
          NewPos=NULL;
          NewPos=(Pos *)malloc(sizeof(Pos)); /* allocates memory for one position */
          if(NewPos == NULL){ /* verification of the allocation */
            exit(0);
          }

          p = fscanf(fi, "%hi %hi", &NewPos->line, &NewPos->col); /* reads a point */
          if(p!=2) /* if it doesn't read two integers it exits the program */
            exit(0);
          InsertListNode(&Puzzle->Positions, NewPos); /* inserts the position to the next point on the positions list */
      }

      if(mode=='A'||mode=='B'||mode=='C'){ /* if the mode is correct */
        /* allocates memory for the board with the dimensions specified in the first line of the puzzle */
        Puzzle->board = (short int **)malloc(nLines*sizeof(short int *));
        if(Puzzle->board == NULL){ /* verification of the allocation */
          exit(0);
        }
        for(i=0; i<nLines; i++){
          Puzzle->board[i]=(short int *)malloc(nCols*sizeof(short int));
          if(Puzzle->board[i] == NULL){ /* verification of the allocation */
            exit(0);
          }
        }
        /* reads the board of the entry file to the allocated board */
        for(i=0; i<nLines; i++){
          for(j=0; j<nCols; j++){
          p = fscanf(fi, "%hi", &Puzzle->board[i][j]);
          if(p!=1) /* if it doesn't read one integer it exits the program */
            exit(0);
          }
        }
      } else { /* if the mode is wrong */
        /* reads the rest of the information to a dummy integer */
        Puzzle->board=NULL;
        for(i=0; i<nLines; i++){
          for(j=0; j<nCols; j++){
          p = fscanf(fi, "%d", &dumb);
          if(p!=1) /* if it doesn't read one integer it exits the program */
            exit(0);
          }
        }
      }
      /* compute all that is necessary about the puzzle */
      mainOper(Puzzle, fOut);
      /* free the puzzle */
      freeAllPuzzle(Puzzle);
    }
  }
  /* close all files opened */
  fclose(fi);
  fclose(fOut);
}

/******************************************************************************
* createFileSol()
*
* Arguments: nomef - name of the entry file
*
* Returns: pointer to the opened exit file
*
* Side-Effects: generates an exit file and opens it
*
* Description: creates a file with the same name of the entry file
*             but with a different extention
*
*****************************************************************************/
FILE *createFileSol(char *nomef){
  /* General Initializations */
  FILE *f1 = NULL; /* File pointer to the exit file */
  char *string = NULL; /* string with the name to the exit file */
  int len = 0; /* lenght of the entry file without the extention */

  /* allocates and initializes memory for the exit file name */
  string = (char*)calloc(1, (strlen(nomef) - strlen(".cities") +
                                          strlen(".walks") + 1)*sizeof(char));
  if (string == NULL) /* verification of the allocation */
    exit(0);

  len = strlen(nomef)-strlen(".cities");
  strncpy(string, nomef, len); /* copies nomef to string until the [len] caracter */
  strcat(string, ".walks"); /* adds the wanted extention in the end */

  f1=fopen(string, "w"); /* opens the exit file on write mode */
  if(f1==NULL) /* verification of the allocation */
    exit(0);

  /* frees the memory used */
  free(string);
  return f1;
}

/******************************************************************************
* printSolutions()
*
* Arguments: f - name of the exit file
*            sol - integer vector with the solution
*            Puzzle - Puzzle that is being analysed
*            ini - initial point of the path
*            fim - final point of the path
*
* Returns: none
*
* Side-Effects: prints a solution to the exit file
*
* Description: if the solution is invalid prints out the invalid solution,
*              if the initial point is the same to the end point prints out the no steps solution,
*              if none of those two happens prints out the whole solution
*
*****************************************************************************/
void printSolutions(FILE *f, int *sol, Puzzles *Puzzle, int ini, int fim){
  /* General Initializations */
  short int custo=0, passos=0, x=0, y=0; /* total cost, total steps and coordinates initialization */
  int n; /* iterator */

  n=fim;
  if (sol == NULL){ /* if the solution is invalid prints the invalid solution */
    custo = -1;
    passos = 0;
    fprintf(f, "%hi %hi %c %hi %hi %hi\n\n", Puzzle->lines, Puzzle->cols, Puzzle->mode,
                                      Puzzle->nmoves , custo, passos);
    return;
  }

  if(ini!=fim){ /* if the solution is valid and the initial and end points are different */
    while(n!=ini){ /* sums the steps and the cost of the path */
      invertConvertV(n, Puzzle, &x, &y);
      custo += Puzzle->board[x][y];
      passos++;
      n=sol[n];
      }
  }

  fprintf(f, "%hi %hi %c %hi %hi %hi\n", Puzzle->lines, Puzzle->cols, Puzzle->mode,
                                    Puzzle->nmoves , custo, passos); /* prints out the first line of the solution */

  printreverse(sol, Puzzle, ini, fim, fim, f); /* prints out all the steps and the cost to each step */

  fprintf(f,"\n"); /* prints the paragraph between puzzles */

}

/******************************************************************************
* printPathList()
*
* Arguments: Sol - integer vector with the solution
*            P - Puzzle that is being analysed
*            fOut - name of the exit file
*
* Returns: none
*
* Side-Effects: prints a path to the exit file
*
* Description: prints a path to the exit file
*
*****************************************************************************/
void printPathList(lList *Sol, Puzzles *P, FILE *fOut){
  /* General Initializations */
  link *AuxE = NULL; /* pointer to the information on each node */
  lList *AuxL = Sol; /* auxiliary pointer to the path */
  short int x=0, y=0; /* converted coordinates */

  while(AuxL!=NULL){ /* while there are still path positions to be printed */
    AuxE=AuxL->data;
    invertConvertV(AuxE->v, P, &x, &y); /* converts the absolute value of the vertex to coordinates */
    fprintf(fOut, "%hi %hi %hi\n", x, y, P->board[x][y]); /* prints in the exit file the path position */
    AuxL=AuxL->next;
  }

}

/******************************************************************************
* printreverse()
*
* Arguments: sol - integer vector with the solution
*            Puzzle - Puzzle that is being analysed
*            ini - initial point of the path
*            fim - final point of the path
*            n - point iterator of the path
*            f - name of the exit file
*
* Returns: none
*
* Side-Effects: prints each path position to the exit file
*
* Description: prints each path position to the exit file
*
*****************************************************************************/
void printreverse(int *sol, Puzzles *Puzzle, int ini, int fim, int n, FILE *f){
  /* if the iterator is different of the initia point of the path it keeps iterating */
  if (n!=ini){
    /* recursive call of the funcion to print from the beggining to the end */
    printreverse(sol, Puzzle, ini, fim, sol[n], f);

    short int x=0, y=0; /* converted coordinates */

    invertConvertV(n, Puzzle, &x, &y); /* converts the absolute value of the vertex to coordinates */
    fprintf(f, "%hi %hi %hi\n", x, y, Puzzle->board[x][y]); /* prints in the exit file the path position */
  }
}
