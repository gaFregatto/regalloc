#ifndef graph_h
#define graph_h

#include "list.h"

typedef void *Graph;
typedef void *Vertex;

Graph newGraph(int id, int k);
Vertex newVertex(int id, int degree, int color, List adjVertxs);

#endif