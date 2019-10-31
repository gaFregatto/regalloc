#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"

typedef struct _graph
{
    int id, k, kColors;
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
    g->kColors = -1;
    g->vertexes = newList(printVertex, freeVertex, equalVertexes);
    return g;
}

int getGraphID(Graph gr)
{
    graph *g = gr;
    return g->id;
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

void setGraphKC(Graph gr, int k)
{
    graph *g = gr;
    g->kColors = k;
}

int getGraphKC(Graph gr)
{
    graph *g = gr;
    return g->kColors;
}

void downGraphKC(Graph gr)
{
    graph *g = gr;
    g->kColors = g->kColors - 1;
}

int getGraphK(Graph gr)
{
    graph *g = gr;
    return g->k;
}

void addVertexGraph(Graph gr, Vertex vtx, int assign)
{
    graph *g = gr;
    vertex *v = vtx;
    Vertex aux_v;
    Item it;
    if (vertexExists(g, getVertexID(v)))
    {
        aux_v = getVertexById(g, getVertexID(v));
        if (assign)
        {
            List edges = getEdges(aux_v);
            Posic p = getFirst(edges);
            // printf("\nREINSERINDO VERTICE\n");
            while (p != NULL)
            {
                it = getItem(edges, p);
                upDegree(it);
                // printf("%d ", getVertexID(it));
                p = getNext(edges, p);
            }
        }
        setValidVertex(v);
        return;
    }
    insertList(g->vertexes, v);
}

void printGraph(Graph gr)
{
    graph *g = gr;
    printf("Graph %d -> Physical Registers: %d", g->id, g->k);
    printf("\n----------------------------------------\n");

    // Posic pv = getFirst(g->vertexes);
    // while (pv != NULL)
    // {
    //     Item it = getItem(g->vertexes, pv);
    //     printf("%d(%d) ", getVertexID(it), getVertexDegree(it));
    //     printf("---> ");
    //     List edges = getEdges(it);
    //     printList(edges);
    //     printf("\n");
    //     pv = getNext(g->vertexes, pv);
    // }
}

void freeGraph(Graph gr)
{
    graph *g = gr;
    List l = getVertexes(g);
    eraseList(l);
    free(g);
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
    v->edges = newList(printVertex, freeVertex, equalVertexes);
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
    printf("%d ", v->id);
}

int getVertexID(Vertex vtx)
{
    vertex *v = vtx;
    return v->id;
}

int getVertexDegree(Vertex vtx)
{
    vertex *v = vtx;
    return v->degree;
}

void setVertexDegree(Vertex vtx, int d)
{
    vertex *v = vtx;
    v->degree = v->degree - d;
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
    freeList(getEdges(v));
    free(v);
}

void addVertexEdge(Vertex vtx, Vertex edge)
{
    vertex *v = vtx;
    vertex *e = edge;
    insertList(getEdges(v), e);
    upDegree(v);
    //upDegree(e);
}

int vertexExists(Graph gr, int id)
{
    graph *g = gr;
    List l = getVertexes(g);
    if (l == NULL)
        return 0;
    Posic pv = getFirst(getVertexes(g));
    Item it;

    while (pv != NULL)
    {
        it = getItem(l, pv);
        if (getVertexID(it) == id)
            return 1;
        pv = getNext(l, pv);
    }
    return 0;
}

int validVertex(Vertex vtx)
{
    vertex *v = vtx;
    return v->valid;
}

void disableVertex(Graph gr, Vertex vtx)
{
    graph *g = gr;
    vertex *v = vtx;
    List edges = getEdges(v);
    Posic p = getFirst(edges);
    Item it;
    while (p != NULL)
    {
        it = getItem(edges, p);
        downDegree(it);
        p = getNext(edges, p);
    }
    v->valid = 0;
}

int validVertexExists(Graph gr)
{
    graph *g = gr;
    List vertexes = getVertexes(g);
    Posic p = getFirst(vertexes);
    Item it;

    while (p != NULL)
    {
        it = getItem(vertexes, p);
        if (validVertex(it) && getVertexID(it) > getGraphK(g))
            return 1;
        p = getNext(vertexes, p);
    }
    return 0;
}

int minValidDegree(Graph gr)
{
    graph *g = gr;
    List l = getVertexes(g);
    Posic p = getFirst(l);
    Item it;
    int menor = INT_MAX, dgr;

    if (!validVertexExists(g))
        return INT_MAX;

    while (p != NULL)
    {
        it = getItem(l, p);
        dgr = getVertexDegree(it);
        if (dgr < menor && validVertex(it) && dgr < getGraphKC(g) && getVertexID(it) >= getGraphK(g))
            menor = dgr;
        p = getNext(l, p);
    }
    return menor;
}

int maxValidDegree(Graph gr)
{
    graph *g = gr;
    List l = getVertexes(g);
    Posic p = getFirst(l);
    Item it;
    int maior = INT_MIN, dgr;

    if (!validVertexExists(g))
        return INT_MIN;

    while (p != NULL)
    {
        it = getItem(l, p);
        dgr = getVertexDegree(it);
        if (dgr > maior && validVertex(it))
            maior = dgr;
        p = getNext(l, p);
    }
    return maior;
}

Vertex minValidID(Graph gr, int degree)
{
    graph *g = gr;
    List l = getVertexes(g);
    Posic p = getFirst(l);
    Item it, menor;
    int menorID = INT_MAX;

    while (p != NULL)
    {
        it = getItem(l, p);
        if (getVertexDegree(it) == degree && validVertex(it) && getVertexID(it) < menorID)
        {
            menor = getVertexById(g, getVertexID(it));
            menorID = getVertexID(it);
        }
        p = getNext(l, p);
    }
    if (menorID == INT_MAX)
        return NULL;
    else
        return menor;
}

void setValidVertex(Vertex vtx)
{
    vertex *v = vtx;
    v->valid = 1;
}

void setInvalidVertex(Vertex vtx)
{
    vertex *v = vtx;
    v->valid = 0;
}

Vertex getVertexById(Graph gr, int id)
{
    graph *g = gr;
    List l = getVertexes(g);
    Posic p = getFirst(l);
    Item it;
    while (p != NULL)
    {
        it = getItem(l, p);
        if (getVertexID(it) == id)
            return it;
        p = getNext(l, p);
    }
    return NULL;
}

int getAvailableColors(Graph gr, Vertex vtx)
{
    graph *g = gr;
    vertex *v = vtx;
    List edges;
    Posic p, pi;
    Item it;
    int i, k;
    k = getGraphKC(g);
    int *availableColors = malloc(sizeof(int) * k);

    for (i = 0; i < k; i++)
        availableColors[i] = 1;

    edges = getEdges(v);
    p = getFirst(edges);
    while (p != NULL)
    {
        it = getItem(edges, p);
        if (getVertexID(it) < k)
            availableColors[getVertexID(it)] = 0;
        else if (validVertex(it) && getVertexColor(it) != -1)
            availableColors[getVertexColor(it)] = 0;

        p = getNext(edges, p);
    }

    // printf("\nCORES DISPONIVEIS ");
    // for (i = 0; i < k; i++)
    // {
    //     printf("%d ", availableColors[i]);
    // }

    for (i = 0; i < k; i++)
    {
        if (availableColors[i])
        {
            // printf("\nRETORNANDO COR %d", i);
            return i;
        }
    }

    return -1;
}

int getVertexColor(Vertex vtx)
{
    vertex *v = vtx;
    return v->color;
}

int paintVertex(Graph gr, Vertex vtx, int color)
{
    graph *g = gr;
    vertex *v = vtx;
    if (!validVertex(v) || color >= getGraphKC(g))
        return -1;

    // printf("\nPINTANDO VERTICE %d com %d\n", getVertexID(v), color);
    setVertexColor(v, color);
    return 1;
}

void setVertexColor(Vertex vtx, int color)
{
    vertex *v = vtx;
    v->color = color;
}

void enableVertexes(Graph gr)
{
    graph *g = gr;
    List vertexes = getVertexes(g);
    Posic p = getFirst(vertexes);
    Item it;
    while (p != NULL)
    {
        it = getItem(vertexes, p);
        setValidVertex(it);
        p = getNext(vertexes, p);
    }
}