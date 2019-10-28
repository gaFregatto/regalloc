#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "list.h"
#include "graph.h"
#include "aloc.h"

// Tratar corretamente as funções de inserção do grafo

int main(int argc, char *argv[])
{
    Graph graph = newGraph();
    build(graph);
    freeGraph(graph);
    return 0;
}