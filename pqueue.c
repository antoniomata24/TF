#include "pqueue.h"


void GRAPHpfs(Graph *G, int s, int st[], double wt[])
{
  int v, w;
  link t;
  PQinit();
  for (v = 0; v < G->V; v++)
  {
    st[v] = -1;
    wt[v] = maxWT;
    PQinsert(v);
  }
  wt[s] = 0.0;
  PQdec(s);
  while (!PQempty())
    if (wt[v = PQdelmin()] != maxWT)
      for (t = G->adj[v]; t != NULL; t = t->next)
        if (wt[w = t->v] > P)
          {
            wt[w] = P;
            PQdec(w);
            st[w] = v;
          }
}
/* RELAXAÇÃO */

if (d[s][t] > d[s][x] + d[x][t])
{
d[s][t] = d[s][x] + d[x][t];
p[s][t] = p[s][x];
}
