#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "integer.h"

typedef struct _graph
{
    int id, k;
    List vertexes;
} graph;

typedef struct _vertex
{
    int id, degree, color, valid;
    List adjacentVertexes;
} vertex;

Graph newGraph(int id, int k)
{
    graph *g = (graph *)malloc(sizeof(graph));
    g->id = id;
    g->k = k;
    g->vertexes = newList(printInteger, freeInteger, equalIntegers);
    return g;
}

Vertex newVertex(int id, int degree, int color, List adjVertxs)
{
    vertex *v = (vertex *)malloc(sizeof(vertex));
    v->id = id;
    v->degree = degree;
    v->color = color;
    v->adjacentVertexes = adjVertxs;
    return v;
}