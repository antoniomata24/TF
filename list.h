#ifndef list_h
#define list_h
#include "define.h"

void InsertListNode(lList **, Item);
void freeNode(Item , lList **);
void freelList(lList *);
void freeAllPuzzle(Puzzles *);
void freePosition(Pos *);
void freeGraph(Graph *);
void freeLink(link *);
void freePQ(PQueue **, Graph *);

#endif
