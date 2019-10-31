#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "list.h"
#include "graph.h"
#include "aloc.h"
#include "integer.h"

int main(int argc, char *argv[])
{
    Graph graph = newGraph();
    List result = newList(printInteger, freeInteger, equalIntegers);
    List vertexes;
    Posic p;
    Item it;
    int k;

    build(graph);

    vertexes = getVertexes(graph);
    p = getFirst(vertexes);
    while (p != NULL)
    {
        it = getItem(vertexes, p);
        if (getVertexID(it) < getGraphK(graph))
            setInvalidVertex(it);
        p = getNext(vertexes, p);
    }
    setGraphKC(graph, getGraphK(graph));

    //simplify(graph, result);
    while (getGraphKC(graph) > 1)
    {
        simplify(graph, result);
        downGraphKC(graph);
    }

    printf("----------------------------------------\n----------------------------------------\n");
    p = getFirst(result);
    k = getGraphK(graph);
    while (p != NULL)
    {
        it = getItem(result, p);
        if (k < 10)
        {
            printf("Graph %d -> K =  %d: ", getGraphID(graph), k);
        }
        else
        {
            printf("Graph %d -> K = %d: ", getGraphID(graph), k);
        }
        if (getInteger(it))
        {
            printf("Successful Allocation\n");
        }
        else
        {
            if (k == 2)
            {
                printf("SPILL");
            }
            else
            {
                printf("SPILL\n");
            }
        }
        k -= 1;
        p = getNext(result, p);
    }

    freeGraph(graph);
    eraseList(result);
    return 0;
}