#include "oper.h"

/** mainOper - computes and prints in exit file the solutions to the multiple
              Puzzles in the entry file

  \param Data - Pointer to the list of structs (Puzzles) wich contain the
                multiple Puzzles and all their info
  \param f - Pointer to the out file, wich will contains the solutions

*/
void mainOper(Puzzles *Data, FILE *f){
  int * new_sol = NULL;
  lList **new_solB = NULL;
  lList *AllPoints = NULL, *new_solC=NULL, *AuxPos=NULL;
  Pos *SinglePos=NULL;
  int i=0, ini = 0, fim = 0, contador = 0, n=0;
  short int custo=0, passos=0, x, y, inv=0;
  int tallocs=0;
  link *Auxlink = NULL;
  Edge *Ed1=NULL, *Ed2=NULL;

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
      AuxPos=AuxPos->next;
      contador++;
      free(new_sol);
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
    for (i=0; i<tallocs; i++){
      freelList(new_solB[i]);
    }
    free(new_solB);
    break;


    case 'C':
      printSolutions(f, NULL, Data, 0, 0);

      break;
    default:
      /*if the mode is invalid prints the invalid solution*/
      printSolutions(f, NULL, Data, 0, 0);
      break;
  }

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
    Pos *AuxPos=NULL;;
    while(PosList!=NULL){
        AuxPos=PosList->data;
        if(AuxPos->col>=AuxP->cols||AuxPos->line>=AuxP->lines||AuxPos->line<0||AuxPos->col<0)
            return 0;
        if(AuxP->board[AuxPos->line][AuxPos->col]==0)
            return 0;
        PosList=PosList->next;
    }
    return 1;
}
/* convertAllPoints - converts path points in the entry file from coordinates to
                      absolute value (horizontal order)
  \param AuxP - Puzzle struct wich contains board values and path points

  returns a linked list with Edge strutcs with all the path points to be analysed
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

int *IniHeap(int n){
  int *Heap = NULL;

  Heap=(int *)malloc(n*sizeof(int));
  if(Heap==NULL)
    exit(0);

  return Heap;
}

void swap(int **heap, int **posInH, int n1, int n2){
  int i=0, j=0;
  int *auxH = *heap;
  int *auxP = *posInH;
  i=auxH[n1];
  j=auxH[n2];

  auxP[i]=n2;
  auxP[j]=n1;
  auxH[n1]=j;
  auxH[n2]=i;
}

void Hinsert(int **Heap, int *free, int n, unsigned int *price, int **posInH){
    (*Heap)[*free]=n;
    (*posInH)[n]=*free;
    FixUp(Heap, *free, price, posInH);
    (*free)++;
}

int HExtractMin(int **Heap, unsigned int *price, int **posinH, int *nfree){
  int n=0;
  if(nfree==0)
    return -1;

  n=*Heap[0];
  (*posinH)[(*Heap)[0]]=-2;

  (*Heap)[0]=(*Heap)[(*nfree)-1];
  (*posinH)[(*Heap)[0]]=0;
  FixDown(Heap, 0, (*nfree)-1, price, posinH);
  (*nfree)--;
  return n;
}

void FixDown(int **Heap, int Idx, int N, unsigned int *price, int **posinH) {
    int Child;
    while(2*Idx < N-1) {
        Child = 2*Idx+1;
        if (Child < (N-1) && lessPri(price[(*Heap)[Child]], price[(*Heap)[Child+1]]))
          Child++;
        if (!lessPri(price[(*Heap)[Idx]], price[(*Heap)[Child]]))
          break;
        swap(Heap, posinH, Idx, Child);
        Idx = Child;
    }

}

void FixUp(int **Heap, int Idx, unsigned int *price, int **posInH){
  while (Idx > 0 && lessPri(price[(*Heap)[(Idx-1)/2]], price[(*Heap)[Idx]])){
    swap(Heap, posInH, Idx, (Idx-1)/2);
    Idx = (Idx-1)/2;
  }
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


/* addPathPoint - add a single point to the Path list computed by the "searchPathC"
                fuction

  \param Path - linked list with Edge structs that contain all path points where
                a single path point will be inserted (at the end of the list)
  \param n - absolute value of the path point to be inserted in the path list
*/
void addPathPoint(lList **Path, int n){
  lList *NewList = *Path;
  int* data = (int*)malloc(sizeof(int));

    data[0]=n;
    InsertListNode(&NewList, data);
    *Path=NewList;
}

void addPathSol(int *prev, lList **Path, int source, int n){

  lList *AuxList=NULL;
  lList *NewList = NULL;

  while(n!=source){
    int* data = (int*)malloc(sizeof(int));
    data[0]=n;
    AuxList=(lList *)malloc(sizeof(lList));
    AuxList->data=data;
    AuxList->next=NewList;
    NewList=AuxList;
    n=prev[n];
  }
  *Path=NewList;
  return;
}

int searchMin(int n, int *visited, int *price){
    int min=INFINITY, i, v;

    for(i=0; i<n; i++){
        if(price[i]<min&&visited[i]==0){
            min=price[i];
            v=i;
        }
    }

    return v;
}

int vEmpty(int *Data, int n){
    int i=0;
    for(i=0; i<n; i++){
        if(Data[i]!=1)
            return 0;
    }
    return 1;
}
