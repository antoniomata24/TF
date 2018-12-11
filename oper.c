#include "oper.h"

/** mainOper - computes and prints in exit file the solutions to the multiple
              Puzzles in the entry file

  \param Data - Pointer to the list of structs (Puzzles) wich contain the
                multiple Puzzles and all their info
  \param f - Pointer to the out file, wich will contains the solutions

*/
void mainOper(Puzzles *Data, FILE *f){
  int * new_sol = NULL;
  lList **new_solB = NULL, **new_solC=NULL;
  lList *AllPoints = NULL, *AuxPos=NULL, *AuxPosC = NULL;
  Pos *SinglePos=NULL;
  int i=0, ini = 0, fim = 0, contador = 0, n=0, fact=0, c=0, j=0;
  short int custo=0, passos=0, x, y, inv=0;
  int tallocs=0;
  link *Auxlink = NULL;
  link *Ed1=NULL, *Ed2=NULL;
  int iniC = NULL, *fimC=NULL, totalC=0, *order=NULL, *orderfim=NULL, min=INFINITY;
  link *AuxC=NULL;
  int **matrix=NULL;

  AuxPos = Data->Positions;
  /*Creates Graph to all the eligible points in the puzzle and their possible
  moves*/
  contador = 0;

  switch (Data->mode) {
    case 'A':
      if(validateAllPoints(Data)==0){
        printSolutions(f, NULL, Data, 0, 0);
        break;
      }
      /*converts initial and final points of the intended path*/
      SinglePos=AuxPos->data;
      ini=convertV(SinglePos->line, SinglePos->col, Data);
      SinglePos=AuxPos->next->data;
      fim=convertV(SinglePos->line, SinglePos->col, Data);

      /*runs Dijkstra algorithm to search minimum cost path*/
      new_sol=searchPath(Data, ini, fim);
      /*prints the solution in the exit file*/
      printSolutions(f, new_sol, Data, ini, fim);
      /*freeing of the memory used*/
      free(new_sol);

      break;

    case 'B':

      if(validateAllPoints(Data)==0){
         printSolutions(f, NULL, Data, 0, 0);
         break;
      }
      contador=0;
      /*allocation for all the paths and all the initial and final points*/
      new_solB = (lList**)malloc((Data->nmoves-1)*sizeof(lList*));
      if (new_solB==NULL) exit(0);
      for(n=0; n<Data->nmoves-1; n++)
        new_solB[n]=NULL;

      AllPoints=convertAllPoints(Data);
      AuxPos=AllPoints;
      while(AuxPos->next!=NULL){
        Ed1=AuxPos->data;
        Ed2=AuxPos->next->data;
        new_sol=searchPath(Data, Ed1->v, Ed2->v);
        if(new_sol==NULL){
          printSolutions(f, NULL, Data, 0, 0);
          free(new_sol);
          inv=1;
          break;
        }
        addPathSol(new_sol, &(new_solB[contador]), Ed1->v, Ed2->v);
        free(new_sol);
        AuxPos=AuxPos->next;
        contador++;
        new_sol=NULL;
      }
      if(inv==1)
        break;

      for(n=0; n<contador; n++){
        AuxPos=new_solB[n];
        while(AuxPos!=NULL){
          Auxlink=AuxPos->data;
          invertConvertV(Auxlink->v, Data, &x, &y);
          custo+=Data->board[x][y];
          passos++;
          AuxPos=AuxPos->next;
        }
      }

      fprintf(f, "%hi %hi %c %hi %hi %hi\n", Data->lines, Data->cols, Data->mode,
                                        Data->nmoves , custo, passos);
      for(n=0; n<contador; n++){
        printPathList(new_solB[n], Data, f);
      }
      fprintf(f, "\n");
      /*freeing all the memory used*/
      freelList(AllPoints);
      for (i=0; i<(Data->nmoves-1); i++){
        freelList(new_solB[i]);
      }
      free(new_solB);
      break;


    case 'C':

      if(validateAllPoints(Data)==0){
         printSolutions(f, NULL, Data, 0, 0);
         break;
      }
      new_solC = (lList**)malloc((Data->nmoves-1)*sizeof(lList*));
      if (new_solC==NULL) exit(0);
      for(n=0; n<(Data->nmoves-1); n++)
        new_solC[n]=NULL;

      AllPoints=convertAllPoints(Data);
      AuxPosC=AllPoints;
      AuxC=AuxPosC->data;
      fimC=(int*)malloc((Data->nmoves)*sizeof(int));
      if(fimC==NULL) exit(0);
      while(AuxPosC!=NULL){
        AuxC=AuxPosC->data;
        fimC[i]=AuxC->v;
        i++;
        AuxPosC=AuxPosC->next;
      }

      order=(int*)malloc((Data->nmoves)*sizeof(int));
      if(order==NULL) exit(0);
      for (n=0; n<(Data->nmoves);n++){
        order[n]=n;
      }
      orderfim=(int*)malloc((Data->nmoves)*sizeof(int));
      if(order==NULL) exit(0);
      for (n=0; n<(Data->nmoves);n++){
        order[n]=n;
      }

      matrix=(int**)malloc(sizeof(int*)*(Data->nmoves));
      for (n=0; n<(Data->nmoves); n++){
        matrix[n]=(int*)malloc(sizeof(int)*(Data->nmoves));
      }
      for (n=0; n<(Data->nmoves); n++){
        for (j=0; j<(Data->nmoves); j++){
          totalC=searchPathC(Data, fimC[n], fimC[j]);
          if (totalC==-1){
            inv=1;
            break;
          } else {
            matrix[n][j]=totalC;
          }
        }
        if(inv==1) break;
      }
      permute(order, 1, Data->nmoves, matrix, Data, &min, orderfim);

      if ( inv == 1){
        printSolutions(f, NULL, Data, 0, 0);
      } else {
        printf("min: %d\n\n", min);
        for (n=0; n<(Data->nmoves); n++){
          for (j=0; j<(Data->nmoves); j++){
            printf("Matrix[%d][%d]: %d\n", n, j, matrix[n][j]);
          }
        }
        for (n=0; n<(Data->nmoves); n++){
          printf("final[%d] : %d\n", n, orderfim[n]);
        }
      }

      for(i=0; i<(Data->nmoves-1);i++){
        new_sol=searchPath(Data, fimC[orderfim[i]], fimC[orderfim[i+1]]);
        addPathSol(new_sol, &(new_solC[i]), fimC[orderfim[i]], fimC[orderfim[i+1]]);
        free(new_sol);
      }

      for(n=0; n<(Data->nmoves-1); n++){
        AuxPosC=new_solC[n];
        while(AuxPosC!=NULL){
          AuxC=AuxPosC->data;
          invertConvertV(AuxC->v, Data, &x, &y);
          custo+=Data->board[x][y];
          passos++;
          AuxPosC=AuxPosC->next;
        }
      }
      fprintf(f, "%hi %hi %c %hi %hi %hi\n", Data->lines, Data->cols, Data->mode,
                                        Data->nmoves , custo, passos);

      for(n=0; n<(Data->nmoves-1); n++){
        printPathList(new_solC[n], Data, f);
      }
      fprintf(f, "\n");

      free(order);
      free(orderfim);
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


lList *findAdj (Puzzles *Data, int n){

  Puzzles *AuxPuzzle = NULL;
  lList *lAdj=NULL;
  short int i=0, j=0;
  int vi, vf;
  AuxPuzzle=Data;

  if (AuxPuzzle == NULL)
      exit(0);

  if(Data->mode=='A' || Data->mode=='B' || Data->mode=='C'){

        vi=n;
        invertConvertV(vi, Data, &i, &j);
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

int ValidateMoveA(short int x, short int y, short int difx, short int dify, Puzzles *Data){
  if(x+difx<0 || y+dify < 0 || x+difx>=Data->lines || y+dify>=Data->cols){
    return 0;
  }else if(Data->board[x+difx][y+dify]==0 || Data->board[x][y]==0){
    return 0;
  }else{
    return 1;
  }
}

int convertV(short int x, short int y,Puzzles *Data){

  int n = 0;

  n=x*Data->cols;
  n+=y;

  return n;
}

void invertConvertV(int n, Puzzles *Data, short int *x, short int *y){
  (*x)=n/Data->cols;
  (*y)=n-(*x)*Data->cols;
}

/** validateAllPoints - checks if all path points inserted in the entry file are
                        valid (within board margin and contains a value diferent
                        than 0)

    \param AuxP - Puzzle struct wich contains board values and path points

    returns 1 if all points are valid
    returns 0 if a invalid point is detected
*/
int validateAllPoints(Puzzles *AuxP){

    lList *PosList=AuxP->Positions;
    Pos *AuxPos=NULL;
    lList *AuxList = NULL;
    while(PosList!=NULL){
        AuxPos=PosList->data;
        if(AuxPos->col>=AuxP->cols||AuxPos->line>=AuxP->lines||AuxPos->line<0||AuxPos->col<0)
            return 0;
        if(AuxP->board[AuxPos->line][AuxPos->col]==0)
            return 0;
        PosList=PosList->next;
        AuxList=findAdj(AuxP, convertV(AuxPos->line, AuxPos->col, AuxP));
        if(AuxList==NULL)
          return 0;
        freelList(AuxList);
        AuxList=NULL;
    }
    return 1;
}
/* convertAllPoints - converts path points in the entry file from coordinates to
                      absolute value (horizontal order)
  \param AuxP - Puzzle struct wich contains board values and path points

  returns a linked list with link strutcs with all the path points to be analysed
*/
lList *convertAllPoints(Puzzles *AuxP){

  int *AuxL = NULL;
  lList *lPoints= NULL, *PosList = NULL;
  Pos *AuxPos=NULL;

  PosList=AuxP->Positions;
  while (PosList!=NULL){
    AuxL=(int *)malloc(sizeof(int));
    AuxPos=PosList->data;
    AuxL[0]=convertV(AuxPos->line, AuxPos->col, AuxP);
    InsertListNode(&lPoints, AuxL);
    PosList=PosList->next;
  }
  return lPoints;
}


/** searchPath - runs Dijkstra algorithm to find the lowest cost path between 2
                points

    \param G - Graph wich contain all points and their adjacent points
    \param Q - vertex wich contains in each position a single point and its
               adjacent points
    \param source - absolute value of the ortigin of the intended Path
    \param dest - absolute value of the destination of the intended path

    return a vertex of int wich contains the previous path position of each
          point (if a point doesn't has a previous path points that point vertex
          position will contain -1)
*/
int *searchPath(Puzzles *P, int source, int dest){
  unsigned int *price = NULL;
  int *prev = NULL;
  int *heap=NULL;
  int i=0, v=0, nfree=0, n=0;
  short int x=0, y=0;
  link *aux =NULL;
  lList *laux=NULL, *AllAdj=NULL;

  AllAdj=findAdj(P, source);
  if(AllAdj==NULL){
    return NULL;
  }
  freelList(AllAdj);
  AllAdj=NULL;

  AllAdj=findAdj(P, dest);
  if(AllAdj==NULL){
    return NULL;
  }
  freelList(AllAdj);
  AllAdj=NULL;

  if(source==dest){
    prev = (int*)calloc(1,sizeof(int));
    return prev;
  } else{
    prev=(int *)malloc((P->lines*P->cols)*sizeof(int));
    if(prev == NULL)
      exit(0);
  }
  int *posInH = (int *)malloc((P->lines*P->cols)*sizeof(int));
  price=(unsigned int *)malloc((P->lines*P->cols)*sizeof(unsigned int));
  if(price == NULL)
    exit(0);
  for(i=0; i<(P->lines*P->cols); i++){
    price[i]=INFINITY;
    prev[i]=-1;
    posInH[i]=-1;
  }

  heap=IniHeap((P->lines*P->cols)/2);
  price[source]=0;
  v=source;
  n=1;
  Hinsert(&heap, &nfree, v, price, &posInH);

  while (n<(P->lines*P->cols)){

    v=HExtractMin(&heap, price, &posInH, &nfree);
    n++;
    if(v==-1){
      free(heap);
      free(price);
      free(posInH);
      free(prev);
      return NULL;
    }
    AllAdj=findAdj(P, v);

    laux=AllAdj;
    if(laux==NULL)
      break;

    aux=laux->data;

    while(laux!=NULL){
      aux=laux->data;
      if(price[aux->v]>aux->weight+price[v]){
        price[aux->v]=aux->weight+price[v];
        if(posInH[aux->v]==-1){
          Hinsert(&heap, &nfree, aux->v, price, &posInH);
        }else{
          i=posInH[aux->v];
          if(i!=-2)
            if(price[heap[i]]<price[heap[(i-1)/2]])
              FixUp(&heap, i, price, &posInH);
        }
        prev[aux->v]=v;
      }

      laux=laux->next;
    }

    if(prev[dest]!=-1){
      free(heap);
      free(price);
      free(posInH);
      freelList(AllAdj);
      AllAdj=NULL;
      return prev;
    }
    freelList(AllAdj);
    AllAdj=NULL;
  }
  free(heap);
  free(price);
  free(posInH);
  free(prev);
  prev=NULL;
  return prev;
}


void permute(int *v, int start, int n, int** matrix, Puzzles *P, int *min, int*final)
{
  int i, a=0, b=0, total=0;
  if (start == n-1) {
    for (a=0; a<(P->nmoves-1);a++){/*
      if (v[a]<v[a+1])
        total+=matrix[v[a+1]][v[a]];
      if (v[a]>v[a+1])*/
        total+=matrix[v[a]][v[a+1]];
        if (total>(*min)) break;
    }
    if (total<(*min)){
      (*min)=total;
      for (a=0; a<(P->nmoves);a++){
        final[a]=v[a];
      }
    }
  }
  else {
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


int searchPathC(Puzzles *P, int source, int dest){
  unsigned int *price = NULL;
  int *prev = NULL;
  int *heap=NULL;
  int i=0, v=0, nfree=0, n=0, total=0;
  short int x=0, y=0;
  link *aux =NULL;
  lList *laux=NULL, *AllAdj=NULL;

  AllAdj=findAdj(P, source);
  if(AllAdj==NULL){
    return -1;
  }
  freelList(AllAdj);
  AllAdj=NULL;

  AllAdj=findAdj(P, dest);
  if(AllAdj==NULL){
    return -1;
  }
  freelList(AllAdj);
  AllAdj=NULL;

  if(source==dest){
    return 0;
  } else{
    prev=(int *)malloc((P->lines*P->cols)*sizeof(int));
    if(prev == NULL)
      exit(0);
  }
  int *posInH = (int *)malloc((P->lines*P->cols)*sizeof(int));
  price=(unsigned int *)malloc((P->lines*P->cols)*sizeof(unsigned int));
  if(price == NULL)
    exit(0);
  for(i=0; i<(P->lines*P->cols); i++){
    price[i]=INFINITY;
    prev[i]=-1;
    posInH[i]=-1;
  }

  heap=IniHeap((P->lines*P->cols)/2);
  price[source]=0;
  v=source;
  n=1;
  Hinsert(&heap, &nfree, v, price, &posInH);

  while (n<(P->lines*P->cols)){

    v=HExtractMin(&heap, price, &posInH, &nfree);
    n++;
    if(v==-1){
      free(heap);
      free(price);
      free(posInH);
      free(prev);
      return -1;
    }
    AllAdj=findAdj(P, v);

    laux=AllAdj;
    if(laux==NULL)
      break;

    aux=laux->data;

    while(laux!=NULL){
      aux=laux->data;
      if(price[aux->v]>aux->weight+price[v]){
        price[aux->v]=aux->weight+price[v];
        if(posInH[aux->v]==-1){
          Hinsert(&heap, &nfree, aux->v, price, &posInH);
        }else{
          i=posInH[aux->v];
          if(i!=-2)
            if(price[heap[i]]<price[heap[(i-1)/2]])
              FixUp(&heap, i, price, &posInH);
        }
        prev[aux->v]=v;
      }

      laux=laux->next;
    }

    if(prev[dest]!=-1){
      total=price[dest];
      free(heap);
      free(price);
      free(posInH);
      freelList(AllAdj);
      free(prev);
      AllAdj=NULL;
      return total;
    }
    freelList(AllAdj);
    AllAdj=NULL;
  }
  free(heap);
  free(price);
  free(posInH);
  free(prev);
  prev=NULL;
  return -1;
}
