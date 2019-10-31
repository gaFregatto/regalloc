#ifndef aloc_h
#define aloc_h

#include "graph.h"
#include "stack.h"

void build(Graph g);
void simplify(Graph g, List l);
Vertex potentialSpill(Graph gr);
int assign(Graph gr, Stack stk);

#endif