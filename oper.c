#include "oper.h"

/** mainOper - computes and prints in exit file the solutions to the multiple
              Puzzles in the entry file

  \param Data - Pointer to the list of structs (Puzzles) wich contain the
                multiple Puzzles and all their info
  \param f - Pointer to the out file, wich will contains the solutions

*/
void mainOper(Puzzles *Data, FILE *f){
  int * new_sol = NULL;
  Puzzles *AuxP = NULL;
  lList *AllPoints = NULL, *new_solC=NULL, *AuxPos=NULL, *auxPoint=NULL;
  Pos *SinglePos=NULL;
  Graph *NewG = NULL;
  int ini = 0, fim = 0;
  Edge *AuxEd=NULL, *AuxEd1 = NULL;


  AuxP = Data;
  if (AuxP == NULL) exit(0);

  while (AuxP!=NULL){
    AuxPos = AuxP->Positions;
    /*Creates Graph to all the eligible points in the puzzle and their possible
    moves*/
    switch (AuxP->mode) {
      case 'A':
        if(AuxP->nmoves!=2){
          printSolutions(f, NULL, AuxP, 0, 0);
          break;
        }
        NewG = createGraph(AuxP);
        /*converts initial and final points of the intended path*/
        SinglePos=AuxPos->data;
        ini=convertV(SinglePos->line, SinglePos->col, AuxP);
        SinglePos=AuxPos->next->data;
        fim=convertV(SinglePos->line, SinglePos->col, AuxP);

        /*runs Dijkstra algorithm to search minimum cost path*/
        new_sol=searchPath(NewG, ini, fim);
        /*prints the solution in the exit file*/
        printSolutions(f, new_sol, AuxP, ini, fim);
        /*freeing of the memory used*/
        freeGraph(NewG);
        NewG=NULL;
        free(new_sol);

        break;

      case 'B':

        if(validateAllPoints(AuxP)==0 || AuxP->nmoves<2){
            printSolutions(f, NULL, AuxP, 0, 0);
            break;
        }

        NewG = createGraph(AuxP);
        AllPoints=convertAllPoints(AuxP);
        auxPoint=AllPoints;
        while (auxPoint->next!=NULL) {
          AuxEd=auxPoint->data;
          AuxEd1=auxPoint->next->data;
          new_sol=searchPath(NewG, AuxEd->v,AuxEd1->v);
          if(new_sol==NULL){
            printSolutions(f, NULL, AuxP, 0, 0);
            free(NewG);
            if(new_solC!=NULL){
              freelList(new_solC);
              new_solC=NULL;
              break;
            }
          }
          addPathSol(new_sol, &new_solC, AuxEd->v, AuxEd1->v);
          auxPoint=auxPoint->next;
          free(new_sol);
          new_sol=NULL;
        }
        if(new_solC==NULL)
            break;
        printSolutionsC(f, new_solC, AuxP);
        freelList(new_solC);
        new_solC=NULL;
        free(NewG);
        break;

      case 'C':
        /*reinitializing variables*/
        AllPoints=NULL;
        new_solC=NULL;
        /*if there are invalid points in the moves prints the invalid solution*/
        if(validateAllPoints(AuxP)==0 || AuxP->nmoves<2){
            printSolutions(f, NULL, AuxP, 0, 0);
            freeGraph(NewG);
            NewG=NULL;
        }else{
          /*converts al the points to an abstract list*/
          AllPoints = convertAllPoints(AuxP);
          /*searches the paths between all the points*/
          searchPathC(NewG, &AllPoints, &new_solC, AllPoints->data);
          /*prints the solutions found*/
          printSolutionsC(f, new_solC, AuxP);
          /*freeing all the memory used*/
          freelList(new_solC);
          freeGraph(NewG);
          NewG=NULL;
        }
        break;
      default:
        /*if the mode is invalid prints the invalid solution*/
        printSolutions(f, NULL, AuxP, 0, 0);
        break;
    }
    /*iterates to the next matrix*/
    AuxP=AuxP->nPuzzle;
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

  Edge *AuxE = NULL;
  lList *lPoints= NULL, *PosList = NULL;
  Pos *AuxPos=NULL;

  PosList=AuxP->Positions;
  while (PosList!=NULL){
    AuxE=(Edge *)malloc(sizeof(Edge));
    AuxPos=PosList->data;
    AuxE->v=convertV(AuxPos->line, AuxPos->col, AuxP);
    InsertListNode(&lPoints, AuxE);
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

void Hinsert(int **Heap, int hsize, int *free, int n, int *price, int **posInH){
  if((*free)<hsize){
    (*Heap)[*free]=n;
    (*posInH)[n]=*free;
    FixUp(Heap, *free, price, posInH);
    (*free)++;
  }
}

int HExtractMin(int **Heap, int hsize, int *price, int **posinH){
  int n=0;
  n=*Heap[0];
  swap(Heap, posinH, 0, hsize-1);
  FixDown(Heap, 0, hsize-1, price, posinH);
  return n;
}

void FixDown(int **Heap, int Idx, int N, int *price, int **posinH) {
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

void FixUp(int **Heap, int Idx, int *price, int **posInH){
  while (Idx > 0 && lessPri(price[(*Heap)[(Idx-1)/2]], price[(*Heap)[Idx]])){
    swap(Heap, posInH, Idx, (Idx-1)/2);
    Idx = (Idx-1)/2;
  }
}

int searchInHeap(int *heap, int hsize, int n){
  int i =0 ;
  for(i=0;i<hsize;i++){
    if(heap[i]==n)
      return i;
  }
  return 0;
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
int *searchPath(Graph *G, int source, int dest){
  int *price = NULL;
  int *prev = NULL;
  int *heap=NULL;
  int i=0, v=0, nfree=0, hsize=0;
  link *aux =NULL;
  lList *laux=NULL;

  if(G->adj[source]==NULL || G->adj[dest]==NULL) return NULL;

  if(source==dest){
    prev=NULL;
    return prev;
  } else{
    prev=(int *)malloc(G->V*sizeof(int));
    if(prev == NULL)
      exit(0);
  }
  int *posInH = (int *)malloc(G->V*sizeof(int));
  price=(int *)malloc(G->V*sizeof(int));
  if(price == NULL)
    exit(0);
  for(i=0; i<G->V; i++){
    price[i]=INFINITY;
    prev[i]=-1;
    posInH[i]=-1;
  }

  heap=IniHeap(G->V);
  hsize=G->V;
  price[source]=0;
  v=source;


  for(i=0; i<G->V; i++){
    Hinsert(&heap, hsize, &nfree, i, price, &posInH);
  }


  while (hsize>0){

    v=HExtractMin(&heap, hsize, price, &posInH);
    hsize--;
    laux=G->adj[v];
    if (laux==NULL){
      break;
    }
    aux=laux->data;

    while(laux!=NULL){
      aux=laux->data;
      if(price[aux->v]>aux->weight+price[v]){
        price[aux->v]=aux->weight+price[v];
        i=posInH[aux->v];
        if(price[heap[i]]<price[heap[(i-1)/2]])
          FixUp(&heap, i, price, &posInH);
        if((2*i)+1<hsize)
            if(price[heap[i]]>price[heap[(2*i)+1]])
                FixDown(&heap, i, hsize, price, &posInH);
        if(2*(i+1)<hsize)
            if(price[heap[i]]>price[heap[2*(i+1)]])
              FixDown(&heap, i, hsize, price, &posInH);
        prev[aux->v]=v;
      }

      laux=laux->next;
    }

    if(prev[dest]!=-1){
      free(heap);
      free(price);
      free(posInH);
      return prev;
    }
  }
  free(posInH);
  free(heap);
  free(price);
  free(prev);
  prev=NULL;
  return prev;
}
/** searchPathC - runs Dijkstra algorithm to find lowest cost path to caint
                  multiple points specified in the entry file

    \param G - Graph wich contain all points and their adjacent points
    \param Q - vertex wich contains in each position a single point and its
               adjacent points
    \param AllPoints - linked list of Edge structs wich contains all points the
                      path must have
    \param FullPath - linked list of Edge structs wich will contain the lowest
                      cost path
    \param ESource - Edge struct that contains the source point, in absolute
                    value, of the intended path
*/
void searchPathC(Graph *G, lList **AllPoints, lList **FullPath, Edge *ESource){
/*  int **prices = NULL;
  int **paths = NULL;

  prices=matrixInit(G->V, G->V, INFINITY);
  paths=matrixInit(G->V, G->V, G->V);

}

int **matrixInit(int cols, int lines, int n){

  int **aux = NULL;
  int i = 0, j=0;

  aux=(int **)malloc(lines*sizeof(int*));
  for(i=0;i<lines;i++){
    aux[i]=(int*)malloc(cols*sizeof(int *));
    if(aux[i]==NULL)
      exit(0);
  }

  for(i=0;i<lines;i++){
    for(j=0;j<cols;j++){
      aux[i][j]=n;
    }
  }

  return aux;*/
}

/* addPathPoint - add a single point to the Path list computed by the "searchPathC"
                fuction

  \param Path - linked list with Edge structs that contain all path points where
                a single path point will be inserted (at the end of the list)
  \param n - absolute value of the path point to be inserted in the path list
*/
void addPathPoint(lList **Path, int n){
  Edge *New = NULL;
  lList *NewList = *Path;
   New=(Edge *)malloc(sizeof(Edge));
    New->v=n;
    New->w=0;
    InsertListNode(&NewList, New);
    *Path=NewList;
}

void addPathSol(int *prev, lList **Path, int source, int n){

  if(n==source)
    return;

  addPathSol(prev, Path, source, prev[n]);
  addPathPoint(Path, n);

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
