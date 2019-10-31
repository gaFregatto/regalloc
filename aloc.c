#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aloc.h"
#include "graph.h"
#include "stack.h"
#include "integer.h"
#include "list.h"

char *resetNum(char vet[])
{
    vet[0] = '\0';
    vet[1] = '\0';
    vet[2] = '\0';
    vet[3] = '\0';
    vet[4] = '\0';
    return vet;
}

void build(Graph g)
{
    int graph_id, i, k, n, f, cont = 0, id, id2 = -5;
    char a[6], stringK[10], num[10], auxNum[10], aaNum[10], c = '\0';
    char *auxK;
    List l = newList(printInteger, freeInteger, equalIntegers);
    Vertex v, aux_v, adj;
    Integer itg, itg2;
    Posic p;
    Item it;

    scanf("%s %d", a, &graph_id);
    scanf("%s", stringK);
    scanf("%s", stringK);

    n = strlen(stringK) - 2;
    auxK = calloc(sizeof(n) + 1, sizeof(char));

    i = 0;
    while (stringK[i + 2] != '\0')
    {
        auxK[i] = stringK[i + 2];
        i += 1;
    }
    k = atoi(auxK);
    free(auxK);

    scanf("%s", auxNum);
    strcpy(num, auxNum);
    while (scanf("%s", auxNum) != EOF)
    {
        n = atoi(num);
        if (strcmp(auxNum, "-->") == 0)
        {
            // printf("\n%d %s ", n, auxNum);
            itg2 = newInteger(-1);
            insertList(l, itg2);
            itg = newInteger(n);
            insertList(l, itg);
            itg2 = newInteger(-2);
            insertList(l, itg2);
            scanf("%s", auxNum);
        }
        else
        {
            // printf("%d ", n);
            itg = newInteger(n);
            insertList(l, itg);
        }
        strcpy(num, auxNum);
    }
    strcpy(num, auxNum);
    n = atoi(num);
    // printf("%d\n\n\n", n);
    itg = newInteger(n);
    insertList(l, itg);

    setGraphID(g, graph_id);
    setGraphK(g, k);
    //printListAux(l);

    p = getFirst(l);
    while (p != NULL)
    {
        it = getItem(l, p);
        id = getInteger(it);
        if (id == -1 || id == -2)
        {
            p = getNext(l, p);
            it = getItem(l, p);
            id = getInteger(it);
            if (!vertexExists(g, id))
            {
                v = newVertex(id);
                addVertexGraph(g, v, 0);
            }
        }
        if (!vertexExists(g, id))
        {
            v = newVertex(id);
            addVertexGraph(g, v, 0);
        }
        p = getNext(l, p);
    }

    p = getFirst(l);
    while (p != NULL)
    {
        it = getItem(l, p);
        id = getInteger(it);
        if (id == -1)
        {
            p = getNext(l, p);
            it = getItem(l, p);
            id = getInteger(it);
            v = getVertexById(g, id);
            // printf("\nENCONTROU VERTICE %d", getVertexID(v));
            id = -3;
        }
        else if (id == -2)
        {
            p = getNext(l, p);
            it = getItem(l, p);
            id = getInteger(it);
            adj = getVertexById(g, id);
            addVertexEdge(v, adj);
            //printf("\nINSERIU ARESTA %d NO VERTICE %d\n\n", getVertexID(adj), getVertexID(v));
            id = -3;
        }
        else
        {
            it = getItem(l, p);
            id = getInteger(it);
            adj = getVertexById(g, id);
            addVertexEdge(v, adj);
            // printf("\nINSERIU ARESTA %d NO VERTICE %d\n\n", getVertexID(adj), getVertexID(v));
        }
        p = getNext(l, p);
    }
    //printListAux(l);
    eraseList(l);
    printGraph(g);
}

void simplify(Graph g, List l)
{
    Stack s = newStack(printVertex, freeVertex);
    int removed, i, degree, aux;
    Vertex v, vPS, auxv;
    List vertexes;
    Posic p;
    Item it;
    int r;
    int *result;
    int k = getGraphKC(g);

    printf("----------------------------------------\n");
    printf("K = %d\n\n", k);
    vertexes = getVertexes(g);

    removed = 1;
    while (removed)
    {
        removed = 0;

        v = minValidID(g, minValidDegree(g));
        if (v != NULL)
        {
            disableVertex(g, v);
            push(s, v);
            printf("Push: %d\n", getVertexID(v));
            removed = 1;
        }

        if (!removed && validVertexExists(g))
        {
            // printf("\nTA ENTRANDO NO POTENTIAL SPILLLLLLLLLLLLLLLLLLLLL");
            vPS = potentialSpill(g);
            if (vPS != NULL)
            {
                disableVertex(g, vPS);
                push(s, vPS);
                printf("Push: %d *\n", getVertexID(vPS));
                removed = 1;
            }
        }
    }
    // Vertex it = pop(s);
    // printf("\nDESEMPILHANDO!!");
    // printVertex(it);
    r = assign(g, s);
    result = newInteger(r);
    insertList(l, result);
    freeStack(s);
    enableVertexes(g);
    vertexes = getVertexes(g);
    p = getFirst(vertexes);
    while (p != NULL)
    {
        it = getItem(vertexes, p);
        if (getVertexID(it) < getGraphK(g))
            setInvalidVertex(it);
        p = getNext(vertexes, p);
    }
}

Vertex potentialSpill(Graph g)
{
    Vertex v;
    List vertexes;
    Posic p;

    vertexes = getVertexes(g);
    v = minValidID(g, maxValidDegree(g));
    if (v != NULL)
        return v;
    return NULL;
}

int assign(Graph gr, Stack stk)
{
    Graph *g = gr;
    Stack *s = stk;
    Vertex v, aux_v;
    Posic p;
    int color;
    int k = getGraphKC(g);

    v = pop(s);
    while (v != NULL)
    {
        addVertexGraph(g, v, 1);
        color = getAvailableColors(g, v);
        //printf("\nCOLOR: %d", color);
        if (color == -1)
        {
            printf("Pop: %d -> NO COLOR AVAILABLE\n", getVertexID(v));
            v = pop(s);
            while (v != NULL)
            {
                addVertexGraph(g, v, 1);
                v = pop(s);
            }
            return 0;
        }
        aux_v = getVertexById(g, getVertexID(v));
        paintVertex(g, aux_v, color);
        v = pop(s);
        printf("Pop: %d -> %d\n", getVertexID(aux_v), getVertexColor(aux_v));
    }
    return 1;
}