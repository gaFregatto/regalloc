#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct _nodeList
{
    Item item;
    struct _nodeList *previous;
    struct _nodeList *next;
} nodeList;

typedef struct _list
{
    nodeList *head;
    nodeList *tail;
    int size;
} list;

// Declaração das funções privadas
int isEmpty(List lt);
nodeList *newNodeList(Item item);

List createList()
{
    list *newList = (list *)malloc(sizeof(list));
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
}

void insertList(List lt, Item item)
{
    list *l = lt;
    nodeList *nAux, *n = newNodeList(item);
    if (isEmpty(l))
    {
        l->head = n;
        l->tail = n;
    }
    else
    {
        n->previous = l->tail;
        l->tail->next = n;
        l->tail = n;
    }
    l->size += 1;
}

void removeItemList(List lt, Item item)
{
    list *l = lt;
    if (isEmpty(l))
    {
        printf("\nNão é possível remover item de uma pilha vazia.\n");
        freeList(l);
        exit(1);
    }
    nodeList *left = l->head;
    nodeList *right = l->tail;
    nodeList *freeAux, *nodeAux;
    int cl = 0, cr = 0;

    if (left == right && left->item == item)
    {
        freeAux = left;
        l->head = NULL;
        l->tail = NULL;
        l->size -= 1;
        free(freeAux);
    }
    else if (left->item == item)
    {
        freeAux = left;
        nodeAux = left->next;
        nodeAux->previous = NULL;
        l->head = nodeAux;
        l->size -= 1;
        free(freeAux);
    }
    else if (right->item == item)
    {
        freeAux = right;
        nodeAux = right->previous;
        nodeAux->next = NULL;
        l->tail = nodeAux;
        l->size -= 1;
        free(freeAux);
    }
    else
    {
        do
        {
            if (left->item == item)
            {
                freeAux = left;
                nodeAux = left->previous;
                nodeAux->next = left->next;
                left->next->previous = nodeAux;
                l->size -= 1;
                free(freeAux);
            }
            else if (right->item == item)
            {
                freeAux = right;
                nodeAux = right->previous;
                nodeAux->next = right->next;
                right->next->previous = nodeAux;
                l->size -= 1;
                free(freeAux);
            }
            left = left->next;
            right = right->previous;
            cl++;
            cr++;
        } while (left != NULL && right != NULL && cl + cr <= sizeList(l));
    }
}

void printList(List lt)
{
    list *l = lt;
    nodeList *n = l->head;
    printf("\nLISTA: ");
    while (n != NULL)
    {
        printf(" %d ", n->item);
        n = n->next;
    }
}

void printReverseList(List lt)
{
    list *l = lt;
    nodeList *n = l->tail;
    printf("\nLISTA REVERSA: ");
    while (n != NULL)
    {
        printf("%d ", n->item);
        n = n->previous;
    }
}

void freeList(List lt)
{
    list *l = lt;
    nodeList *nAux, *n = l->head;
    while (n != NULL)
    {
        nAux = n;
        n = n->next;
        free(nAux);
    }
    free(l);
}

int sizeList(List lt)
{
    list *l = lt;
    return l->size;
}

// ################## Funções privadas ##################

int isEmpty(List lt)
{
    list *l = lt;
    if (l->head == NULL && l->tail == NULL)
        return 1;
    else
        return 0;
}

nodeList *newNodeList(Item item)
{
    nodeList *n = (nodeList *)malloc(sizeof(nodeList));
    n->item = item;
    n->previous = NULL;
    n->next = NULL;
    return n;
}