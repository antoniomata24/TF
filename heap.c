/*******************************************************************
* TouristKnights - Projeto AED 2018/2019 MEEC - IST
*
* Author: António da Mata nº90022
*         Rafael Abranches nº90174
*
* File name: heap.c
*
* Release date: 2018/12/11
*
* Description: file that has the funtions initialize and manage the heap
*
*******************************************************************/
/* including the header files used */
#include "heap.h"

/******************************************************************************
* IniHeap()
*
* Arguments: n - size that is going to be initialized for the heap
*
* Returns: the heap, not initialized
*
* Side-Effects: creates a vector of integers with the size of n*(int)
*
* Description: allocates the memory for the heap and returns it
*
*****************************************************************************/
int *IniHeap(int n){
  /* General Initializations */
  int *Heap = NULL; /* heap pointer */

  Heap=(int *)malloc(n*sizeof(int)); /* allocates memory for the heap */
  if(Heap==NULL) /* verification of the allocation */
    exit(0);

  return Heap;
}

/******************************************************************************
* swap()
*
* Arguments: heap - heap with the point values
*            posInH - position of each point in the heap
*            n1 - absolute value of the first point
*            n2 - absolute value of the second point
*
* Returns: none
*
* Side-Effects: changes the positions of n1 and n2 in the heap and
*               updates its position in the heap (posInH)
*
* Description: changes the positions of n1 and n2 in the heap and
*              updates its position in the heap (posInH)
*
*****************************************************************************/
void swap(int **heap, int **posInH, int n1, int n2){
  /* General Initializations */
  int i=0, j=0; /* auxiliary integers */
  int *auxH = *heap;  /* heap auxiliary */
  int *auxP = *posInH;  /* position vector auxiliary */
  /* initialize i and j as the values of n1 and n2 in the heap */
  i=auxH[n1];
  j=auxH[n2];

  /* swaps the position in the heap and updates its position */
  auxP[i]=n2;
  auxP[j]=n1;
  auxH[n1]=j;
  auxH[n2]=i;
}

/******************************************************************************
* Hinsert()
*
* Arguments: Heap - heap with the point values
*            free - number of positions used in the heap
*            n - absolute value of the turist point
*            price - cost of the path
*            posInH - position of each point in the heap
*
* Returns: none
*
* Side-Effects: increases the heap size and inserts the vertex in the heap
*
* Description: insert a vertex on the free position of the heap and increase
*             the heap size, updates the position of that vertex in the heap
*
*****************************************************************************/
void Hinsert(int **Heap, int *free, int n, unsigned int *price, int **posInH){
  /* insert the new vertex in the heap */
  (*Heap)[*free]=n;
  (*posInH)[n]=*free;
  /* updates the positions on the heap */
  FixUp(Heap, *free, price, posInH);
  /* increases heap usage size */
  (*free)++;
}

/******************************************************************************
* HExtractMin()
*
* Arguments: Heap - heap with the point values
*            price - cost of the path
*            posInH - position of each point in the heap
*            nfree - number of positions used in the heap
*
* Returns: the vertex of the lowest cost in the heap
*
* Side-Effects: decreases the heap size and removes the vertex of the heap with the lowest cost
*
* Description: removes the vertex with the lowest value and updates all the Positions
*             in the heap, decreases the usage size in the heap
*
*****************************************************************************/
int HExtractMin(int **Heap, unsigned int *price, int **posInH, int *nfree){
  /* General Initializations */
  int n=0; /* absolute value of the vertex of the lowest cost point in the heap */
  if(nfree==0) /* if the heap is empty returns invalid (-1)*/
    return -1;

  n=*Heap[0]; /* gets the absolute value of the lowest cost point */
  (*posInH)[(*Heap)[0]]=-2; /* updates the position to a position out of the heap */

  (*Heap)[0]=(*Heap)[(*nfree)-1]; /* brings the last point in the heap to the top */
  (*posInH)[(*Heap)[0]]=0; /* updates its position */
  FixDown(Heap, 0, (*nfree)-1, price, posInH); /* updates all the positions in the heap */
  (*nfree)--; /* decreases the heap usage size */
  return n;
}

/******************************************************************************
* FixDown()
*
* Arguments: Heap - heap with the point values
*            Idx - index from which to fix down
*            N - index that it will stop the fix down
*            price - cost of the path
*            posInH - position of each point in the heap
*
* Returns: none
*
* Side-Effects: changes the order of the heap and updates the positions of the vertexes
*
* Description: changes the order of the heap from Idx to N and updates
*             the positions of those vertexes on the heap
*
*****************************************************************************/
void FixDown(int **Heap, int Idx, int N, unsigned int *price, int **posInH) {
  /* General Initializations */
  int Child; /* auxiliary integer to the index of the fix down */
  while(2*Idx < N-1) { /* while there are still branches to be verified */
    Child = 2*Idx+1; /* gets the branch index */
    /* if the child isn't in the end of the heap, and has higher priority than the next one */
    if (Child < (N-1) && lessPri(price[(*Heap)[Child]], price[(*Heap)[Child+1]]))
      Child++; /* goes to next position */
    if (!lessPri(price[(*Heap)[Idx]], price[(*Heap)[Child]])) /* if the index has lower priority then the child */
      break;
    swap(Heap, posInH, Idx, Child); /* changes the positions of the index and the child */
    Idx = Child; /* changes the index */
  }
}

/******************************************************************************
* FixUp()
*
* Arguments: Heap - heap with the point values
*            Idx - index from which to fix down
*            price - cost of the path
*            posInH - position of each point in the heap
*
* Returns: none
*
* Side-Effects: changes the order of the heap and updates the positions of the vertexes
*
* Description: changes the order of the heap from Idx to N and updates
*             the positions of those vertexes on the heap
*
*****************************************************************************/
void FixUp(int **Heap, int Idx, unsigned int *price, int **posInH){
  /* while the index is more then 0 and has higher priority than the root swaps it */
  while (Idx > 0 && lessPri(price[(*Heap)[(Idx-1)/2]], price[(*Heap)[Idx]])){
    swap(Heap, posInH, Idx, (Idx-1)/2);
    Idx = (Idx-1)/2;
  }
}
