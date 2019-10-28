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
    List edges;
} vertex;

Graph newGraph()
{
    graph *g = (graph *)malloc(sizeof(graph));
    g->id = -1;
    g->k = -1;
    g->vertexes = newList(printVertex, freeVertex, equalVertexes);
    return g;
}

void setGraphID(Graph gr, int id)
{
    graph *g = gr;
    g->id = id;
}

void setGraphK(Graph gr, int k)
{
    graph *g = gr;
    g->k = k;
}

void addVertexGraph(Graph gr, Vertex vtx)
{
    graph *g = gr;
    vertex *v = vtx;
    insertList(g->vertexes, v);
}

void freeGraph(Graph gr)
{
    graph *g = gr;
    List l = getVertexes(g);
    eraseList(l);
    free(g);
}

void printGraph(Graph gr)
{
    graph *g = gr;
    printf("Graph %d -> Physical Registers: %d", g->id, g->k);
    printf("\n----------------------------------------\n");

    Posic pv = getFirst(g->vertexes);
    while (pv != NULL)
    {
        Item it = getItem(g->vertexes, pv);
        printf("%d ", getVertexID(it));
        printf("---> ");
        List edges = getEdges(it);
        printList(edges);
        printf("\n");
        pv = getNext(g->vertexes, pv);
    }
}

List getVertexes(Graph gr)
{
    graph *g = gr;
    return g->vertexes;
}

Vertex newVertex(int id)
{
    vertex *v = (vertex *)malloc(sizeof(vertex));
    v->id = id;
    v->degree = 0;
    v->color = -1;
    v->valid = 1;
    v->edges = newList(printInteger, freeInteger, equalIntegers);
    return v;
}

List getEdges(Vertex vtx)
{
    vertex *v = vtx;
    return v->edges;
}

void printVertex(Vertex vtx)
{
    vertex *v = vtx;
    printf("VÉRTICE\nID:%d\nGRAU:%d\nCOLOR:%d\n\n", v->id, v->degree, v->color);
}

int equalVertexes(Vertex a, Vertex b)
{
    vertex *aa = a;
    vertex *bb = b;
    if (aa->id == bb->id)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int getVertexID(Vertex vtx)
{
    vertex *v = vtx;
    return v->id;
}

void upDegree(Vertex vtx)
{
    vertex *v = vtx;
    v->degree += 1;
}

void downDegree(Vertex vtx)
{
    vertex *v = vtx;
    v->degree -= 1;
}

void freeVertex(Vertex vtx)
{
    vertex *v = vtx;
    eraseList(getEdges(v));
    free(v);
}

void addEdgeVertex(Integer itg, Vertex vtx)
{
    vertex *v = vtx;
    int *e = itg;
    insertList(getEdges(v), e);
}