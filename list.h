#ifndef list_h
#define list_h
#include "define.h"

typedef void * Item;
typedef struct _lList lList;

struct _lList{
  Item data;
  lList *next;
};

lList *InsertListNode(lList *, Item);
lList *freeNode(Item , lList *);
void freeAllPuzzle(Puzzles *);
void freePosition(Pos *);
void freeSolution(Sol *);

#endif
