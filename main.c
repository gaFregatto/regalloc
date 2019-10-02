#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// Implementar Grafo, HashTable, List

int main(int argc, char *argv[])
{
    Stack s = createStack();
    push(s, 1);
    push(s, 2);
    push(s, 3);
    pop(s);
    printStack(s);
    freeStack(s);

    return 0;
}