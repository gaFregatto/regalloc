#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "list.h"

// Implementar Grafo, HashTable

int main(int argc, char *argv[])
{
    Stack s = createStack();
    push(s, 15);
    pop(s);
    pop(s);
    printStack(s);
    freeStack(s);

    return 0;
}