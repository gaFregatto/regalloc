#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aloc.h"
#include "graph.h"
#include "integer.h"

char *resetNum(char vet[])
{
    vet[0] = '\0';
    vet[1] = '\0';
    vet[2] = '\0';
    vet[3] = '\0';
    vet[4] = '\0';
    return vet;
}

int build(Graph g)
{
    int graph_id, i, k, n, f = 1;
    char a[6], stringK[10], num[5], c = '\0';
    char *auxK;
    Vertex v;
    Integer itg;

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

    i = 0;
    resetNum(num);
    c = getchar();
    while ((c = getchar()) != EOF)
    {
        if (c <= '9' && c >= '0')
        {
            num[i] = c;
            i++;
        }
        else if (c == ' ')
        {
            n = atoi(num);
            printf(" %d", n);
            if (f)
            {
                // antes do -->
                v = newVertex(n);
                addVertexGraph(g, v);
            }
            else
            {
                itg = newInteger(n);
                addEdgeVertex(itg, v);
            }
            resetNum(num);
            i = 0;
        }
        else if (c == '-')
        {
            scanf("%c", &c);
            scanf("%c", &c);
            scanf("%c", &c);
            printf(" ---> ");
            f = 0;
        }
        else if (c == '\n')
        {
            n = atoi(num);
            printf(" %d\n", n);
            itg = newInteger(n);
            addEdgeVertex(itg, v);
            resetNum(num);
            i = 0;
            f = 1;
        }
    }
    n = atoi(num);
    printf(" %d\n", n);
    itg = newInteger(n);
    addEdgeVertex(itg, v);

    setGraphID(g, graph_id);
    setGraphK(g, k);
    printGraph(g);

    return 0;
}