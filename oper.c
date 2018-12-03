#include "oper.h"

/** mainOper - computes and prints in exit file the solutions to the multiple
              Puzzles in the entry file

  \param Data - Pointer to the list of structs (Puzzles) wich contain the
                multiple Puzzles and all their info
  \param f - Pointer to the out file, wich will contains the solutions

*/
void mainOper(Puzzles *Data, FILE *f){
  int * new_sol = NULL, *iniB =NULL, *fimB = NULL;
  int **new_solB = NULL;
  PQueue **Queue = NULL;
  Puzzles *AuxP = NULL;
  Pos *AuxPos = NULL;
  lList *AllPoints = NULL, *new_solC=NULL;
  Graph *NewG = NULL;
  int i=0, ini = 0, fim = 0, contador = 0, n=0, custo=0, passos=0, x, y, inv=0;
  int tallocs=0;

  AuxP = Data;
  if (AuxP == NULL) exit(0);

  while (AuxP!=NULL){
    AuxPos = AuxP->Positions;
    /*Creates Graph to all the eligible points in the puzzle and their possible
    moves*/
    NewG = createGraph(AuxP);
    contador = 0;

    switch (AuxP->mode) {
      case 'A':
        /*converts initial and final points of the intended path*/
        ini=convertV(AuxP->Positions->line, AuxP->Positions->col, AuxP);
        fim=convertV(AuxP->Positions->nPos->line, AuxP->Positions->nPos->col, AuxP);
        /*runs Dijkstra algorithm to search minimum cost path*/
        new_sol=searchPath(NewG, (Queue = iniPQ(NewG)), ini, fim);
        /*prints the solution in the exit file*/
        printSolutions(f, new_sol, AuxP, ini, fim);

        freePQ(Queue, NewG);
        freeGraph(NewG);
        NewG=NULL;
        free(new_sol);

        break;

      case 'B':

        new_solB = (int**)malloc((AuxP->nmoves)*sizeof(int*));
        if (new_solB==NULL) exit(0);
        iniB = (int*)malloc((AuxP->nmoves)*sizeof(int));
        if (iniB==NULL) exit(0);
        fimB = (int*)malloc((AuxP->nmoves)*sizeof(int));
        if (fimB==NULL) exit(0);

        contador=0;
        custo=0;
        passos=0;
        inv=0;
        tallocs=0;

        while (AuxPos->nPos!=NULL){
          new_solB[contador]=NULL;
          iniB[contador]=convertV(AuxPos->line, AuxPos->col, AuxP);
          fimB[contador]=convertV(AuxPos->nPos->line, AuxPos->nPos->col, AuxP);
          new_solB[contador]=searchPath(NewG, (Queue = iniPQ(NewG)), iniB[contador], fimB[contador]);
          freePQ(Queue, NewG);
          if(new_solB[contador]==NULL) break;
          AuxPos = AuxPos->nPos;
          contador++;
          tallocs++;
        }

        for (contador=0; contador<AuxP->nmoves-1; contador++){
          if(new_solB[contador]==NULL) {
            printSolutions(f, NULL, AuxP, 0, 0);
            inv=1;
            break;
          }
        }

        if(inv==0){
          for (contador = (AuxP->nmoves)-2; contador >= 0; contador--){
            n = fimB[contador];
            while(n!=iniB[contador]){
              invertConvertV(n, AuxP, &x, &y);
              custo += AuxP->board[x][y];
              passos++;
              n = new_solB[contador][n];
            }
          }
          for (contador=0; contador<AuxP->nmoves-1; contador++){
            if (contador == 0){
              printSolutionsB(f, new_solB[contador], AuxP, iniB[contador], fimB[contador], custo, passos);
              printSolutionsBSteps(f, new_solB[contador], AuxP, iniB[contador], fimB[contador]);
            } else {
              printSolutionsBSteps(f, new_solB[contador], AuxP, iniB[contador], fimB[contador]);
            }
          }
          fprintf(f,"\n");
        }

        for (i=0; i<tallocs; i++){
          free(new_solB[i]);
        }
        freeGraph(NewG);
        NewG=NULL;
        free(new_solB);
        free(iniB);
        free(fimB);
        break;

      case 'C':
        AllPoints=NULL;
        new_solC=NULL;

        if(validateAllPoints(AuxP)==0){
            printSolutions(f, NULL, AuxP, 0, 0);
            freeGraph(NewG);
            NewG=NULL;
        }else{
          AllPoints = convertAllPoints(AuxP);
          searchPathC(NewG, (Queue = iniPQ(NewG)), &AllPoints, &new_solC, AllPoints->data);
          printSolutionsC(f, new_solC, AuxP);

          freePQ(Queue, NewG);
          freelList(new_solC);
          freeGraph(NewG);
          NewG=NULL;
        }
        break;
      default:
        printSolutions(f, NULL, AuxP, 0, 0);
        break;
    }

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

    Pos *AuxPos=AuxP->Positions;
    while(AuxPos!=NULL){
        if(AuxPos->col>=AuxP->cols||AuxPos->line>=AuxP->lines||AuxPos->line<0||AuxPos->col<0)
            return 0;
        if(AuxP->board[AuxPos->line][AuxPos->col]==0)
            return 0;
        AuxPos=AuxPos->nPos;
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
  lList *lPoints = NULL;
  Pos *AuxPos=NULL;
  AuxPos = AuxP->Positions;

  while (AuxPos!=NULL){
    AuxE=(Edge *)malloc(sizeof(Edge));
    AuxE->v=convertV(AuxPos->line, AuxPos->col, AuxP);
    AuxE->w=AuxP->board[AuxPos->line][AuxPos->col];
    InsertListNode(&lPoints, AuxE);
    AuxPos=AuxPos->nPos;
  }
  return lPoints;
}

PQueue **iniPQ(Graph *G){
  PQueue **New = NULL;
  link *Aux = NULL;
  int i = 0, j =0;

  New = (PQueue **)malloc(G->V*sizeof(PQueue*));
  if(New == NULL) exit(0);

  for(i=0; i<G->V; i++){
    New[i]=(PQueue *)malloc(sizeof(PQueue ));
    if (New[i] == NULL) exit(0);
  }

  for(i=0; i<G->V; i++){
    Aux=G->adj[i];

    if(Aux!=NULL){
      New[j]->v=i;
      New[j]->adj=Aux;
      j++;
    }else{
      New[j]->v=i;
      New[j]->adj=NULL;
      j++;
    }
  }

  return New;
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
int *searchPath(Graph *G, PQueue **Q, int source, int dest){
  int *price = NULL;
  int *prev = NULL, *visited = NULL;
  int i=0, v=0;
  link *aux =NULL;

  if(G->adj[source]==NULL || G->adj[dest]==NULL) return NULL;

  price=(int *)malloc(G->V*sizeof(int));
  if(price == NULL)
    exit(0);
  for(i=0; i<G->V; i++){
    price[i]=INFINITY;
  }

  visited=(int *)malloc(G->V*sizeof(int));
  if(visited == NULL)
    exit(0);
  for(i=0; i<G->V; i++){
    visited[i]=0;
  }
  prev=(int *)malloc(G->V*sizeof(int));
  if(prev == NULL)
    exit(0);
  for(i=0; i<G->V; i++){
    prev[i]=-1;
  }

  price[source]=0;
  v=source;

  if (source==dest){
    free(visited);
    free(price);
    return prev;
  }

  while (vEmpty(visited, G->V)==0){

    v=searchMin(G->V, visited, price);
    aux=Q[v]->adj;
    visited[v]=1;

    while(aux!=NULL){

      if(price[aux->v]>aux->weight+price[v]){
        price[aux->v]=aux->weight+price[v];
        prev[aux->v]=v;
      }

      aux=aux->next;
    }
    if(prev[dest]!=-1){
      free(visited);
      free(price);
      return prev;
    }
  }
  free(visited);
  free(price);
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
void searchPathC(Graph *G, PQueue **Q, lList **AllPoints, lList **FullPath, Edge *ESource){
  int *price = NULL;
  int *prev = NULL, *visited = NULL;
  int i=0, v=0, prevS=0;
  link *aux =NULL;
  lList *Point = *AllPoints;
  lList *AuxPoints = *AllPoints;
  lList *FinalPath = *FullPath;
  Edge *AuxE=NULL;

  if(AllPoints==NULL)
    return;

  AuxE=Point->data;


  if(G->adj[AuxE->v]==NULL) return;

  price=(int *)malloc(G->V*sizeof(int));
  if(price == NULL) exit(0);
  for(i=0; i<G->V; i++){
    price[i]=INFINITY;
  }

  visited=(int *)malloc(G->V*sizeof(int));
  if(visited == NULL) exit(0);
  for(i=0; i<G->V; i++){
    visited[i]=0;
  }

  prev=(int *)malloc(G->V*sizeof(int));
  if(prev == NULL) exit(0);
  for(i=0; i<G->V; i++){
    prev[i]=-1;
  }

  AuxE=ESource;
  price[AuxE->v]=0;
  v=AuxE->v;
  prevS=v;
  freeNode(AuxE, &Point);

  if(Point==NULL){
    free(prev);
    free(visited);
    free(price);
    return;
  }

  while(Point!=NULL||vEmpty(visited, G->V)==0){

    v=searchMin(G->V, visited, price);
    aux=Q[v]->adj;
    visited[v]=1;

    while(aux!=NULL){

      if(price[aux->v]>aux->weight+price[v]){
        price[aux->v]=aux->weight+price[v];
        prev[aux->v]=v;
      }

      aux=aux->next;
    }
    AuxPoints=Point;
    while (AuxPoints!=NULL){
      AuxE=AuxPoints->data;
      if(prev[AuxE->v]!=-1){
        addPathSol(prev, FullPath, prevS, AuxE->v);
        prevS=AuxE->v;
        searchPathC(G, Q, &Point, FullPath, AuxE);
        free(prev);
        free(visited);
        free(price);
        return;
      }
      AuxPoints=AuxPoints->next;
    }
  }
  free(prev);
  free(visited);
  free(price);
  return;
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
  Edge *New = NULL;
  lList *NewList = *Path;

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
