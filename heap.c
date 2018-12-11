/* including the header files used */
#include "heap.h"

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
