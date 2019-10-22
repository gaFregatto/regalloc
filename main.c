#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "integer.h"
#include "stack.h"
#include "list.h"

int main(int argc, char *argv[])
{
    FILE *arq;
    char aux[20];
    int graph_id;
    Integer integer;
    Item it;
    List l = newList(printInteger, freeInteger, equalIntegers);
    arq = fopen("lista.txt", "r");
    if (arq != NULL)
        printf("\nArquivo encontrado!");
    else
        printf("\nFalha na abertura do arquivo");

    while (!feof(arq))
    {
        fscanf(arq, "%d", &graph_id);
        integer = newInteger(graph_id);
        insertList(l, integer);
    }
    printList(l);

    printf("\nEncerrando programa..\n");

    eraseList(l);
    fclose(arq);
    return 0;
}