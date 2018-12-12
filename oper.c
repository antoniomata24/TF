/*******************************************************************
* TouristKnights - Projeto AED 2018/2019 MEEC - IST
*
* Author: António da Mata nº90022
*         Rafael Abranches nº90174
*
* File name: oper.c
*
* Release date: 2018/12/11
*
* Description: file that has the funtions to compute the solutions according
*             to the mode for each puzzle
*
*******************************************************************/
/* including the header files used */
#include "oper.h"


/******************************************************************************
* mainOper()
*
* Arguments: Data - Puzzle that is being analysed
*            f - pointer to the exit file
*
* Returns: none
*
* Side-Effects: writes the solution to the puzzle in the exit file
*
* Description: computes and prints in exit file the solutions to the puzzle
*             that is being analysed
*
*****************************************************************************/
void mainOper(Puzzles *Data, FILE *f){
  /* General initializations */
  int * new_sol = NULL; /* vector with the designated path solution between 2 poits */
  lList **new_solB = NULL, **new_solC=NULL; /* list of the solutions to the modes B and C */
  lList *AllPoints = NULL, *AuxPos=NULL, *AuxPosC = NULL; /* list of the points of the puzzle and auxiliary position vectors */
  Pos *SinglePos=NULL; /* auxiliary pointer to a single position */
  int i=0, ini = 0, fim = 0, contador = 0, n=0, j=0; /* iterator initializations and initialization of the beggining and end of part A */
  short int custo=0, passos=0, x, y, inv=0; /* coordinates to be used, validation flag and the cost and step total for all modes */
  link *Auxlink = NULL; /* auxiliary pointer to the point used to sum the costs */
  link *Ed1=NULL, *Ed2=NULL;  /* auxiliary pointers for the beggining and end of pahts*/
  int *fimC=NULL, totalC=0, *order=NULL, *orderfim=NULL, min=INFINITY; /* auxiliary pointers used in part C, total cost of a path and lowest cost of all paths */
  link *AuxC=NULL; /* auxiliary pointer to the points in part C to iterate the points or to sum the total */
  int **matrix=NULL; /* matrix for part C for saving the costs between points of the path */
  short int x1=0, x2=0, y1=0, y2=0; /* coordinates of the points of the matrix */

  /* initialization of the auxiliary pointer to the puzzle postitions */
  AuxPos = Data->Positions;

  /* switch : Data->mode (its the mode of the puzzle in the provided file)
  *     if 'A', the program executes the part A code, which is finding the lowest cost path between 2 points;
  *     if 'B', the program executes the part B code, which is finding the lowest cost path between all the points in the order they are provided;
  *     if 'C', the program executes the part C code, which is finding the lowest cost path between all the points provided;
  *     if none of those are chosen, prints out the invalid solution          */
  switch (Data->mode) {
    case 'A':
      /* if any of the given points is invalid prints out the invalid solution */
      if(validateAllPoints(Data)==0){
        printSolutions(f, NULL, Data, 0, 0);
        break;
      }
      /* converts initial and final points of the intended path */
      SinglePos=AuxPos->data;
      ini=convertV(SinglePos->line, SinglePos->col, Data);
      SinglePos=AuxPos->next->data;
      fim=convertV(SinglePos->line, SinglePos->col, Data);

      /* runs Dijkstra algorithm to search minimum cost path */
      new_sol=searchPath(Data, ini, fim);
      /* prints the solution in the exit file */
      printSolutions(f, new_sol, Data, ini, fim);
      /* freeing of the memory used */
      free(new_sol);

      break;

    case 'B':
      /* if any of the given points is invalid prints out the invalid solution */
      if(validateAllPoints(Data)==0){
         printSolutions(f, NULL, Data, 0, 0);
         break;
      }
      /*allocation for all the paths and all the initial and final points*/
      new_solB = (lList**)malloc((Data->nmoves-1)*sizeof(lList*));
      if (new_solB==NULL) exit(0); /* verification of the allocation */
      for(n=0; n<Data->nmoves-1; n++) /* initializing the list of solutions */
        new_solB[n]=NULL;

      AllPoints=convertAllPoints(Data); /* converts all the points to the path to a list of points to be used */
      AuxPos=AllPoints;
      while(AuxPos->next!=NULL){ /* iterates all the points given */
        Ed1=AuxPos->data; /* beggining of the path */
        Ed2=AuxPos->next->data; /* end of the path */
        new_sol=searchPath(Data, Ed1->v, Ed2->v); /* runs Dijkstra algorithm to search minimum cost path */
        if(new_sol==NULL){ /* if there are no solutions prints out the invalid solution and frees the memory */
          printSolutions(f, NULL, Data, 0, 0);
          free(new_sol);
          inv=1;
          break;
        }
        addPathSol(new_sol, &(new_solB[contador]), Ed1->v, Ed2->v); /* if it the path isn't invalid adds it to the solution and frees the memory used*/
        free(new_sol);
        AuxPos=AuxPos->next;
        contador++;
        new_sol=NULL;
      }
      if(inv==1) /* if there was an invalid solution it breaks out of the funtion */
        break;

      for(n=0; n<contador; n++){ /* iterates all the solutions and sums the number of steps and the cost from the beggining to the end of the paths */
        AuxPos=new_solB[n];
        while(AuxPos!=NULL){
          Auxlink=AuxPos->data;
          invertConvertV(Auxlink->v, Data, &x, &y); /* converts the absolute number to the coordinates of the turist point */
          custo+=Data->board[x][y];
          passos++;
          AuxPos=AuxPos->next;
        }
      }

      fprintf(f, "%hi %hi %c %hi %hi %hi\n", Data->lines, Data->cols, Data->mode,
                                        Data->nmoves , custo, passos); /* prints out the first line of the solution */
      for(n=0; n<contador; n++){ /* prints out all the steps and cost of every step */
        printPathList(new_solB[n], Data, f);
      }
      fprintf(f, "\n"); /* prints the paragraph between puzzles */
      /* freeing all the memory used */
      freelList(AllPoints);
      for (i=0; i<(Data->nmoves-1); i++){
        freelList(new_solB[i]);
      }
      free(new_solB);
      break;


    case 'C':
      /* if any of the given points is invalid prints out the invalid solution */
      if(validateAllPoints(Data)==0){
         printSolutions(f, NULL, Data, 0, 0);
         break;
      }
      new_solC = (lList**)malloc((Data->nmoves-1)*sizeof(lList*));
      if (new_solC==NULL) exit(0); /* verification of the allocation */
      for(n=0; n<(Data->nmoves-1); n++) /* initializing the list of solutions */
        new_solC[n]=NULL;

      AllPoints=convertAllPoints(Data); /* converts all the points to the path to a list of points to be used */
      AuxPosC=AllPoints;
      AuxC=AuxPosC->data;
      fimC=(int*)malloc((Data->nmoves)*sizeof(int)); /* allocates memory for the turist points on a vector */
      if(fimC==NULL) exit(0); /* verification of the allocation */
      while(AuxPosC!=NULL){ /* iterates the points and puts them in the i position of the vector */
        AuxC=AuxPosC->data;
        fimC[i]=AuxC->v;
        i++;
        AuxPosC=AuxPosC->next;
      }

      /* allocates the matrix to save the cost of every path from point a to point b */
      matrix=(int**)malloc(sizeof(int*)*(Data->nmoves));
      if (matrix == NULL) exit(0); /* verification of the allocation */
      for (n=0; n<(Data->nmoves); n++){
        matrix[n]=(int*)malloc(sizeof(int)*(Data->nmoves));
        if (matrix[n]==NULL) exit(0); /* verification of the allocation */
      }
      /* fills in the matrix with the costs of the paths for the upper side and for the diagonal
      *  (it will be all 0, because from n to n the path is 0) of the matrix  */
      for (n=0; n<(Data->nmoves); n++){
        for (j=0; j<=n; j++){
          totalC=searchPathC(Data, fimC[n], fimC[j]); /* runs Dijkstra algorithm to search minimum cost path */
          if (totalC==-1){ /* if there is any non existing path between n and j it is invalid so breaks out of the funtion */
            inv=1;
            break;
          } else { /* saves the total of that path to that place in the matrix */
            matrix[n][j]=totalC;
          }
        }
        if(inv==1) break; /* if it's invalid breaks out of the iteration */
      }

      if (inv==0){ /* only if all the paths are valid it will continue */

        /* allocation and initialization of the vector to be permutated */
        order=(int*)malloc((Data->nmoves)*sizeof(int));
        if(order==NULL) exit(0); /* verification of the allocation */
        for (n=0; n<(Data->nmoves);n++){
          order[n]=n;
        }
        /* allocation and initialization of the vector to save the lowest cost path */
        orderfim=(int*)malloc((Data->nmoves)*sizeof(int));
        if(order==NULL) exit(0); /* verification of the allocation */
        for (n=0; n<(Data->nmoves);n++){
          order[n]=n;
        }
        /* for the lower part of the matrix, the cost is the same as the upper
        *  except for the initial and end points,so we need to add
        *  the end point cost and subtract the initial point costs            */
        for (n=0; n<(Data->nmoves); n++){
          for (j=(Data->nmoves-1); j>n; j--){
            /* conversion from absolute value to coordinates */
            invertConvertV(fimC[n], Data, &x1, &y1);
            invertConvertV(fimC[j], Data, &x2, &y2);
            matrix[n][j]=matrix[j][n]-Data->board[x1][y1]+Data->board[x2][y2];
          }
        }
        /* permutates and calculates the minimal cost path between all points
        *  starts an the second number because the first point is the origin to the path */
        permute(order, 1, Data->nmoves, matrix, Data, &min, orderfim);
      }


      if ( inv == 1){ /* if there are invalid paths prints out the invalid solution */
        printSolutions(f, NULL, Data, 0, 0);
      } else {
        /* iterates all the moves */
        for(i=0; i<(Data->nmoves-1);i++){
          /* runs Dijkstra algorithm to search minimum cost path between the points making the lowest cost path*/
          new_sol=searchPath(Data, fimC[orderfim[i]], fimC[orderfim[i+1]]);
          addPathSol(new_sol, &(new_solC[i]), fimC[orderfim[i]], fimC[orderfim[i+1]]); /* adds path to solution */
          free(new_sol); /* frees the memory */
        }

        /* iterates all the solutions and sums the number of steps and the cost from the beggining to the end of the paths */
        for(n=0; n<(Data->nmoves-1); n++){
          AuxPosC=new_solC[n];
          while(AuxPosC!=NULL){
            AuxC=AuxPosC->data;
            invertConvertV(AuxC->v, Data, &x, &y); /* converts the absolute number to the coordinates of the turist point */
            custo+=Data->board[x][y];
            passos++;
            AuxPosC=AuxPosC->next;
          }
        }
        fprintf(f, "%hi %hi %c %hi %hi %hi\n", Data->lines, Data->cols, Data->mode,
                                          Data->nmoves , custo, passos); /* prints out the first line of the solution */

        for(n=0; n<(Data->nmoves-1); n++){ /* prints out all the steps and cost of every step */
          printPathList(new_solC[n], Data, f);
        }
        fprintf(f, "\n"); /* prints the paragraph between puzzles */
        /* frees vectors used if all the paths are valid */
        free(order);
        free(orderfim);
      }
      /* freeing all the memory used */
      for(i=0;i<Data->nmoves;i++)
        free(matrix[i]);
      free(matrix);
      free(fimC);
      freelList(AllPoints);
      for (i=0; i<(Data->nmoves-1); i++){
        freelList(new_solC[i]);
      }
      free(new_solC);

      break;
    default:
      /*if the mode is invalid prints the invalid solution*/
      printSolutions(f, NULL, Data, 0, 0);
      break;
  }

}

/******************************************************************************
* findAdj()
*
* Arguments: Data - Puzzle that is being analysed
*            n - absolute value of the turist point to be verified
*
* Returns: a list with the adjacent points of the turist point, if none found returns NULL
*
* Side-Effects: creates a list with the valid adjacent points of the turist point
*
* Description: computes the point and checks if it has any adjacent points that
*             are valid, if it does returns them in a list, if it doesn't returns NULL
*
*****************************************************************************/
lList *findAdj (Puzzles *Data, int n){
  /* General Initializations */
  Puzzles *AuxPuzzle = NULL; /* auxiliary pointer to the puzzle */
  lList *lAdj=NULL; /* list of adjacent points to be returned */
  short int i=0, j=0; /* coordinates to the turist point */
  int vi, vf; /* initial value and final absolute values of turist points */

  AuxPuzzle=Data;

  if (AuxPuzzle == NULL) /* verification of the allocation */
      exit(0);

  if(Data->mode=='A' || Data->mode=='B' || Data->mode=='C'){ /* if the mode is valid it verifies the adjacent points */

        vi=n;
        invertConvertV(vi, Data, &i, &j); /* converts the absolute value of the point to its coordinates */

        /* verifies all the adjacent points, if they are valid adds them to the list */
        if(ValidateMoveA(i, j, 1, 2, Data)==1){
          vf=convertV(i+1, j+2, Data);
          NEW(vf, &lAdj, Data->board[i+1][j+2]);
        }
        if(ValidateMoveA(i, j, 1, -2, Data)==1){
          vf=convertV(i+1, j-2, Data);
          NEW(vf, &lAdj, Data->board[i+1][j-2]);
        }
        if(ValidateMoveA(i, j, -1, 2, Data)==1){
          vf=convertV(i-1, j+2, Data);
          NEW(vf, &lAdj, Data->board[i-1][j+2]);
        }
        if(ValidateMoveA(i, j, -1, -2, Data)==1){
          vf=convertV(i-1, j-2, Data);
          NEW(vf, &lAdj, Data->board[i-1][j-2]);
        }
        if(ValidateMoveA(i, j, 2, 1, Data)==1){
          vf=convertV(i+2, j+1, Data);
          NEW(vf, &lAdj, Data->board[i+2][j+1]);
        }
        if(ValidateMoveA(i, j, 2, -1, Data)==1){
          vf=convertV(i+2, j-1, Data);
          NEW(vf, &lAdj, Data->board[i+2][j-1]);
        }
        if(ValidateMoveA(i, j, -2, 1, Data)==1){
          vf=convertV(i-2, j+1, Data);
          NEW(vf, &lAdj,Data->board[i-2][j+1]);
        }
        if(ValidateMoveA(i, j, -2, -1, Data)==1){
          vf=convertV(i-2, j-1, Data);
          NEW(vf, &lAdj, Data->board[i-2][j-1]);
        }
  }
  return lAdj;
}

/******************************************************************************
* ValidateMoveA()
*
* Arguments: Data - Puzzle that is being analysed
*            x - coordinate of the turist point
*            y - coordinate of the turist point
*            difx - value of the move in the x axis
*            dify - value of the move in the y axis
*
* Returns: 1 if the move is valid
*          0 if th move is invalid
*
* Side-Effects: none
*
* Description: verifies if the move that it is atempted is valid
*
*****************************************************************************/
int ValidateMoveA(short int x, short int y, short int difx, short int dify, Puzzles *Data){
  /* if the move is to a point out of the board is invalid */
  if(x+difx<0 || y+dify < 0 || x+difx>=Data->lines || y+dify>=Data->cols){
    return 0;
  /* if the move is to a point that is invalid on the board of from an invalid point on the board */
  }else if(Data->board[x+difx][y+dify]==0 || Data->board[x][y]==0){
    return 0;
  }else{ /* if the move is valid */
    return 1;
  }
}

/******************************************************************************
* convertV()
*
* Arguments: Data - Puzzle that is being analysed
*            x - coordinate of the turist point
*            y - coordinate of the turist point
*
* Returns: the absolute value of the turist point on the board
*
* Side-Effects: none
*
* Description: computes the coordinates and returns the absolute value of the turist point
*
*****************************************************************************/
int convertV(short int x, short int y,Puzzles *Data){
  /* General Initializations */
  int n = 0; /* absolute value */

  n=x*Data->cols;
  n+=y;

  return n;
}

/******************************************************************************
* convertV()
*
* Arguments: Data - Puzzle that is being analysed
*            x - coordinate of the turist point
*            y - coordinate of the turist point
*
* Returns: none
*
* Side-Effects: changes the x and y values to the values of the coordinates
*
* Description: computes the absolute value and changes the values of x and y
*             to match the coordinates of the turist point
*
*****************************************************************************/
void invertConvertV(int n, Puzzles *Data, short int *x, short int *y){
  (*x)=n/Data->cols;
  (*y)=n-(*x)*Data->cols;
}

/******************************************************************************
* validateAllPoints()
*
* Arguments: AuxP - Puzzle that is being analysed
*
* Returns: 1 if all the points are valid
*          0 if there is any invalid point
*
* Side-Effects: none
*
* Description: checks if all path points inserted in the entry file are
*             valid (within board margin and contains a value diferent than 0)
*
*****************************************************************************/
int validateAllPoints(Puzzles *AuxP){
  /* General Initializations */
  lList *PosList=AuxP->Positions; /* auxiliary list to iterate the positions of the path */
  Pos *AuxPos=NULL; /* auxiliary pointer to each position */
  lList *AuxList = NULL; /* list to verify if there are any adjacent points */

  while(PosList!=NULL){ /* while there are still positions to be checked */
    AuxPos=PosList->data;
    /* if the point is outside the board it is invalid */
    if(AuxPos->col>=AuxP->cols||AuxPos->line>=AuxP->lines||AuxPos->line<0||AuxPos->col<0)
        return 0;
    /* if the point is an unpassable point, it is invalid */
    if(AuxP->board[AuxPos->line][AuxPos->col]==0)
        return 0;
    PosList=PosList->next;
    /* checks if there are adjacent points to that turist point */
    AuxList=findAdj(AuxP, convertV(AuxPos->line, AuxPos->col, AuxP));
    if(AuxList==NULL) /* if there are no valid adjacent points it is invalid */
      return 0;
    freelList(AuxList); /* frees the list */
    AuxList=NULL;
  }
  return 1; /* only returns 1 if everything is valid */
}

/******************************************************************************
* convertAllPoints()
*
* Arguments: AuxP - Puzzle that is being analysed
*
* Returns: list with all the points of the path in absolute value form
*
* Side-Effects: creates a list to be returned
*
* Description: converts path points in the entry file from coordinates to
*             absolute value (horizontal order)
*
*****************************************************************************/
lList *convertAllPoints(Puzzles *AuxP){
  /* General Initializations */
  int *AuxL = NULL; /* auxiliary pointer to an integer */
  lList *lPoints= NULL, *PosList = NULL; /* list of points to be returned and the list to be iterated */
  Pos *AuxPos=NULL; /* auxiliary pointer to each position */

  PosList=AuxP->Positions;
  while (PosList!=NULL){ /* while there are still positions to be checked */
    AuxL=(int *)malloc(sizeof(int)); /* allocation of the memory fot that pointer */
    if(AuxL == NULL) exit(0); /* verification of the allocation */
    AuxPos=PosList->data;
    AuxL[0]=convertV(AuxPos->line, AuxPos->col, AuxP); /* conversion from coordinates to absolute value form */
    InsertListNode(&lPoints, AuxL); /* insertion of the turist point on the list of absolute value points */
    PosList=PosList->next;
  }
  return lPoints;
}

/******************************************************************************
* searchPath()
*
* Arguments: P - Puzzle that is being analysed
*           source - absolute value of the origin of the intended Path
*           dest - absolute value of the destination of the intended path
*
* Returns: vector with the solution path
*
* Side-Effects: creates a vector of integers which contains the previous path position of each
*              point (if a point doesn't has a previous path points that point vertex
*              position will contain -1)
*
* Description: runs Dijkstra algorithm to find the lowest cost path between two points
*
*****************************************************************************/
int *searchPath(Puzzles *P, int source, int dest){
  /* General Initializations */
  unsigned int *price = NULL; /* vector with the prices of paths to every point */
  int *prev = NULL; /* vector with the previous points of each point */
  int *heap=NULL; /* heap to run Dijkstra's algorithm */
  int i=0, v=0, nfree=0, n=0; /* initialization of iterators, the vertex being used and the size of the heap being used */
  link *aux =NULL; /* pointer to the information of each node in the list */
  lList *laux=NULL, *AllAdj=NULL; /* list iterator and adjacent list */

  /* if the source doesn't have any adjacent points then it is an invalid point, returns NULL*/
  AllAdj=findAdj(P, source);
  if(AllAdj==NULL){
    return NULL;
  }
  freelList(AllAdj); /* frees the list */
  AllAdj=NULL;

  /* if the dest doesn't have any adjacent points then it is an invalid point, returns NULL*/
  AllAdj=findAdj(P, dest);
  if(AllAdj==NULL){
    return NULL;
  }
  freelList(AllAdj); /* frees the list */
  AllAdj=NULL;

  if(source==dest){ /* if the source and the dest are the same then there are no steps to be done */
    prev = (int*)calloc(1,sizeof(int));
    if (prev == NULL) exit(0); /* verification of the allocation */
    return prev;
  } else{ /* if the source and dest are diferent allocates memory for the vector to be retured */
    prev=(int *)malloc((P->lines*P->cols)*sizeof(int));
    if(prev == NULL) /* verification of the allocation */
      exit(0);
  }
  /* allocation of the memory for a vector with the positions of every point in the heap */
  int *posInH = (int *)malloc((P->lines*P->cols)*sizeof(int));
  if (posInH == NULL) exit(0); /* verification of the allocation */
  /* allocation of the memory for a vector with the prices for every path to every point from the source */
  price=(unsigned int *)malloc((P->lines*P->cols)*sizeof(unsigned int));
  if(price == NULL) /* verification of the allocation */
    exit(0);
  for(i=0; i<(P->lines*P->cols); i++){ /* initialize all the vectors */
    price[i]=INFINITY;
    prev[i]=-1;
    posInH[i]=-1;
  }

  heap=IniHeap((P->lines*P->cols)/2); /* allocate the memory for the heap */
  price[source]=0; /* initialize the first value of the price with a 0 */
  v=source; /* the first vertex is the source */
  n=1;
  Hinsert(&heap, &nfree, v, price, &posInH); /* inserts the vertex into the heap */

  while (n<(P->lines*P->cols)){

    v=HExtractMin(&heap, price, &posInH, &nfree); /* extracts the lowest value of the heap */
    n++;
    if(v==-1){ /* if the vertex is invalid free the memory used an return NULL */
      free(heap);
      free(price);
      free(posInH);
      free(prev);
      return NULL;
    }
    AllAdj=findAdj(P, v); /* finds the adjacent points to the vertex */

    laux=AllAdj;
    if(laux==NULL) /* if there are no more adjacent vertexes it breaks out of the iteration */
      break;

    aux=laux->data;

    while(laux!=NULL){ /* while there are still adjacent points to verify */
      aux=laux->data;
      /* if the current price to the next point is higher
      *  then the price to the current point plus the distance
      *  between the current point and the next point */
      if(price[aux->v]>aux->weight+price[v]){
        price[aux->v]=aux->weight+price[v]; /* changes the price to that point */
        if(posInH[aux->v]==-1){ /* if it hasn't been inserted yet, inserts the point in the heap */
          Hinsert(&heap, &nfree, aux->v, price, &posInH);
        }else{
          i=posInH[aux->v]; /* gets the current position of the point in the heap */
          if(i!=-2)
            if(price[heap[i]]<price[heap[(i-1)/2]]) /* if the value is lower then the root, fixes the value up */
              FixUp(&heap, i, price, &posInH);
        }
        prev[aux->v]=v; /* changes the previous point of aux-v to the point being analysed */
      }

      laux=laux->next;
    }

    if(prev[dest]!=-1){ /* if the dest is reached, end the algorithm and return the prev vector */
      /* free all memory used */
      free(heap);
      free(price);
      free(posInH);
      freelList(AllAdj);
      AllAdj=NULL;
      return prev;
    }
    /* free adjacent list */
    freelList(AllAdj);
    AllAdj=NULL;
  }
  /* if there are no solutions free all memory and return NULL */
  free(heap);
  free(price);
  free(posInH);
  free(prev);
  prev=NULL;
  return prev;
}

/******************************************************************************
* permute()
*
* Arguments: v - Puzzle that is being analysed
*           start - absolute value of the origin of the intended Path
*           n - absolute value of the destination of the intended path
*           matrix -
*           P -
*           min -
*           final - order of the lowest cost
*
* Returns: none
*
* Side-Effects: changes the min value to the lowest path value between all points and
*               changes the final vector to be the order of the lowest path
*
* Description: permutates all the values except the origin and compares the values
*             of the paths formed by the permutations changing the value of min and
*             final along the way, saves the lowest path cost and the path with the lowest cost
*
*****************************************************************************/
void permute(int *v, int start, int n, int** matrix, Puzzles *P, int *min, int*final)
{
  /* General Initializations */
  int i, a=0, total=0; /* iterators and total sum of the path chosen */
  if (start == n-1) { /* if there is a new permutation */
    for (a=0; a<(P->nmoves-1);a++){ /* iterates the path */
        total+=matrix[v[a]][v[a+1]]; /* sums the path between those two points to the total */
        if (total>(*min)) break; /* if the total is already bigger then the min value it breaks out of the iteration */
    }
    if (total<(*min)){ /* if the total is lower then the min value */
      (*min)=total; /* the min becomes that total */
      for (a=0; a<(P->nmoves);a++){ /* the order of the path is saved */
        final[a]=v[a];
      }
    }
  }
  else { /* it iterates to a new permutation */
    for ( i = start; i < n; i++) {
      int tmp = v[i];

      v[i] = v[start];
      v[start] = tmp;
      permute(v, start+1, n, matrix, P, &(*min), final);
      v[start] = v[i];
      v[i] = tmp;
    }
  }
}

/******************************************************************************
* searchPathC()
*
* Arguments: P - Puzzle that is being analysed
*           source - absolute value of the origin of the intended Path
*           dest - absolute value of the destination of the intended path
*
* Returns: total cost of the path
*
* Side-Effects: none
*
* Description: runs Dijkstra algorithm to find the lowest cost path between
*             two points and returns that cost
*
*****************************************************************************/
int searchPathC(Puzzles *P, int source, int dest){
  /* General Initializations */
  unsigned int *price = NULL; /* vector with the prices of paths to every point */
  int *prev = NULL; /* vector with the previous points of each point */
  int *heap=NULL; /* heap to run Dijkstra's algorithm */
  /* initialization of iterators, the vertex being used,
  *  the size of the heap being used and the total value of the path */
  int i=0, v=0, nfree=0, n=0, total=0;
  link *aux =NULL; /* pointer to the information of each node in the list */
  lList *laux=NULL, *AllAdj=NULL; /* list iterator and adjacent list */

  /* if the source doesn't have any adjacent points then it is an invalid point, returns NULL*/
  AllAdj=findAdj(P, source);
  if(AllAdj==NULL){
    return -1;
  }
  freelList(AllAdj); /* frees the list */
  AllAdj=NULL;

  /* if the dest doesn't have any adjacent points then it is an invalid point, returns NULL*/
  AllAdj=findAdj(P, dest);
  if(AllAdj==NULL){
    return -1;
  }
  freelList(AllAdj); /* frees the list */
  AllAdj=NULL;

  if(source==dest){/* if the source and the dest are the same then there are no steps to be done */
    return 0;
  } else{ /* if the source and dest are diferent allocates memory for the vector of the previous positions */
    prev=(int *)malloc((P->lines*P->cols)*sizeof(int));
    if(prev == NULL) /* verification of the allocation */
      exit(0);
  }
  /* allocation of the memory for a vector with the positions of every point in the heap */
  int *posInH = (int *)malloc((P->lines*P->cols)*sizeof(int));
  if (posInH == NULL) exit(0); /* verification of the allocation */
  /* allocation of the memory for a vector with the prices for every path to every point from the source */
  price=(unsigned int *)malloc((P->lines*P->cols)*sizeof(unsigned int));
  if(price == NULL) /* verification of the allocation */
    exit(0);
  for(i=0; i<(P->lines*P->cols); i++){ /* initialize all the vectors */
    price[i]=INFINITY;
    prev[i]=-1;
    posInH[i]=-1;
  }

  heap=IniHeap((P->lines*P->cols)/2); /* allocate the memory for the heap */
  price[source]=0; /* initialize the first value of the price with a 0 */
  v=source; /* the first vertex is the source */
  n=1;
  Hinsert(&heap, &nfree, v, price, &posInH); /* inserts the vertex into the heap */

  while (n<(P->lines*P->cols)){

    v=HExtractMin(&heap, price, &posInH, &nfree); /* extracts the lowest value of the heap */
    n++;
    if(v==-1){
      free(heap);
      free(price);
      free(posInH);
      free(prev);
      return -1;
    }
    AllAdj=findAdj(P, v); /* finds the adjacent points to the vertex */

    laux=AllAdj;
    if(laux==NULL) /* if there are no more adjacent vertexes it breaks out of the iteration */
      break;

    aux=laux->data;

    while(laux!=NULL){ /* while there are still adjacent points to verify */
      aux=laux->data;
      /* if the current price to the next point is higher
      *  then the price to the current point plus the distance
      *  between the current point and the next point */
      if(price[aux->v]>aux->weight+price[v]){
        price[aux->v]=aux->weight+price[v]; /* changes the price to that point */
        if(posInH[aux->v]==-1){ /* if it hasn't been inserted yet, inserts the point in the heap */
          Hinsert(&heap, &nfree, aux->v, price, &posInH);
        }else{
          i=posInH[aux->v]; /* gets the current position of the point in the heap */
          if(i!=-2)
            if(price[heap[i]]<price[heap[(i-1)/2]]) /* if the value is lower then the root, fixes the value up */
              FixUp(&heap, i, price, &posInH);
        }
        prev[aux->v]=v; /* changes the previous point of aux-v to the point being analysed */
      }

      laux=laux->next;
    }

    if(prev[dest]!=-1){/* if the dest is reached, end the algorithm and return the total value */
      total=price[dest]; /* gets the price of the path */
      /* free all memory used */
      free(heap);
      free(price);
      free(posInH);
      freelList(AllAdj);
      free(prev);
      AllAdj=NULL;
      return total;
    }
    /* free adjacent list */
    freelList(AllAdj);
    AllAdj=NULL;
  }
  /* if there are no solutions free all memory and return -1 */
  free(heap);
  free(price);
  free(posInH);
  free(prev);
  prev=NULL;
  return -1;
}
