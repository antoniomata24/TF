#ifndef oper_h
#define oper_h

#include "define.h"

Sol *mainOper(Puzzles *Data);
Sol *operA(Puzzles *Data);
Sol *operB(Puzzles *);
int ValidateMoveA(int , int, int , int, Puzzles *);
Sol *InicializeSolution(Puzzles *);
void computeSolutionA(int , int , Puzzles *, Sol *);
int ValidateMoveB(int , int , int , int , Puzzles *);
void computeSolutionB(int , int , Puzzles *, Sol *);
#endif
