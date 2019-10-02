#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

typedef struct _nodeStack
{
    struct _nodeStack *next;
    int data;
} nodeStack;

typedef struct _stack
{
    struct _nodeStack *top;
    int size;
} stack;

Stack createStack()
{
    stack *s = (stack *)malloc(sizeof(stack));
    s->top = NULL;
    return s;
}

nodeStack *newNode(int data)
{
    nodeStack *node = (nodeStack *)malloc(sizeof(nodeStack));
    node->data = data;
    node->next = NULL;
    return node;
}

void push(Stack stk, int data)
{
    stack *s = stk;
    nodeStack *node = newNode(data);
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

int pop(Stack stk)
{
    stack *s = stk;
    nodeStack *node = s->top;
    if (emptyStack(s))
        printf("\nNão é possível desempilhar de uma pilha vazia");
    int data = node->data;
    s->top = node->next;
    s->size -= 1;
    free(node);
    return data;
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
        while (n != NULL)
        {
            printf("-> %d", n->data);
            n = n->next;
        }
}