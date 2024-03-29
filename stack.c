#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

typedef struct _nodeStack
{
    struct _nodeStack *next;
    Item item;
} nodeStack;

typedef struct _stack
{
    struct _nodeStack *top;
    fr printItem, freeItem;
    int size;
} stack;

Stack newStack(fr printItem, fr freeItem)
{
    stack *s = (stack *)malloc(sizeof(stack));
    s->top = NULL;
    s->size = 0;
    s->printItem = printItem;
    s->freeItem = freeItem;
    return s;
}

nodeStack *newNodeStack(Item item)
{
    nodeStack *node = (nodeStack *)malloc(sizeof(nodeStack));
    node->item = item;
    node->next = NULL;
    return node;
}

void push(Stack stk, Item item)
{
    stack *s = stk;
    nodeStack *node = newNodeStack(item);
    if (emptyStack(s))
    {
        s->top = node;
    }
    else
    {
        node->next = s->top;
        s->top = node;
    }
    s->size += 1;
}

Item pop(Stack stk)
{
    stack *s = stk;
    nodeStack *node = s->top;
    if (emptyStack(s))
    {
        //printf("\nNão é possível desempilhar de uma pilha vazia\n");
        //free(s);
        return NULL;
    }

    Item item = node->item;
    s->top = node->next;
    s->size -= 1;
    free(node);
    return item;
}

int sizeStack(Stack stk)
{
    stack *s = stk;
    return s->size;
}

void freeStack(Stack stk)
{
    stack *s = stk;
    nodeStack *aux, *node = s->top;
    while (node != NULL)
    {
        aux = node;
        node = node->next;
        free(aux);
    }
    free(s);
}

void eraseStack(Stack stk)
{
    stack *s = stk;
    nodeStack *aux, *node = s->top;
    while (node != NULL)
    {
        aux = node;
        node = node->next;
        s->freeItem(aux->item);
        free(aux);
    }
    free(s);
}

int emptyStack(Stack stk)
{
    stack *s = stk;
    if (s->top == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void printStack(Stack stk)
{
    stack *s = stk;
    nodeStack *n = s->top;
    if (n != NULL)
    {
        printf("\nPilha (topo à esquerda): ");
        while (n != NULL)
        {
            s->printItem(n->item);
            n = n->next;
        }
    }
}