#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "integer.h"

typedef struct _nodeList
{
    Item item;
    struct _nodeList *previous, *next;
} nodeList;

typedef struct _list
{
    nodeList *head, *tail;
    fr printItem, freeItem;
    fe equalItens;
    int size;
} list;

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

List newList(fr printItem, fr freeItem, fe equalItens)
{
    list *newList = (list *)malloc(sizeof(list));
    newList->head = NULL;
    newList->tail = NULL;
    newList->printItem = printItem;
    newList->freeItem = freeItem;
    newList->equalItens = equalItens;
    newList->size = 0;
    return newList;
}

Item getItem(List lt, Posic p)
{
    list *l = lt;
    nodeList *n = p;
    if (isEmpty(l))
        return NULL;
    else
        return n->item;
}

Posic getNext(List lt, Posic p)
{
    list *l = lt;
    nodeList *n = p;
    if (isEmpty(l))
        return NULL;
    else
        return n->next;
}

Posic getPrevious(List lt, Posic p)
{
    list *l = lt;
    nodeList *n = p;
    if (isEmpty(l))
        return NULL;
    else
        return n->previous;
}

Posic getFirst(List lt)
{
    list *l = lt;
    return l->head;
}

Posic getLast(List lt)
{
    list *l = lt;
    if (isEmpty(l))
        return NULL;
    else
        return l->tail;
}

void insertList(List lt, Item item)
{
    list *l = lt;
    nodeList *n = newNodeList(item);
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

void removeList(List lt, Posic p)
{
    list *l = lt;
    nodeList *aux, *n = p;

    if (l->head == n && l->tail == n)
    {
        l->head = NULL;
        l->tail = NULL;
    }
    else if (l->head == n)
    {
        aux = n->next;
        aux->previous = NULL;
        l->head = aux;
    }
    else if (l->tail == n)
    {
        aux = n->previous;
        aux->next = NULL;
        l->tail = aux;
    }
    else
    {
        aux = n->previous;
        aux->next = n->next;
        aux = n->next;
        aux->previous = n->previous;
    }
    l->size -= 1;
    free(n);
}

void removeItemList(List lt, Posic p)
{
    list *l = lt;
    nodeList *aux, *n = p;

    if (l->head == n && l->tail == n)
    {
        l->head = NULL;
        l->tail = NULL;
    }
    else if (l->head == n)
    {
        aux = n->next;
        aux->previous = NULL;
        l->head = aux;
    }
    else if (l->tail == n)
    {
        aux = n->previous;
        aux->next = NULL;
        l->tail = aux;
    }
    else
    {
        aux = n->previous;
        aux->next = n->next;
        aux = n->next;
        aux->previous = n->previous;
    }
    l->size -= 1;
    l->freeItem(n->item);
    free(n);
}

void removeListByItem(List lt, Item item)
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

    if (left == right && l->equalItens(left->item, item))
    {
        freeAux = left;
        l->head = NULL;
        l->tail = NULL;
        l->size -= 1;
        l->freeItem(freeAux->item);
        free(freeAux);
    }
    else if (l->equalItens(left->item, item))
    {
        freeAux = left;
        nodeAux = left->next;
        nodeAux->previous = NULL;
        l->head = nodeAux;
        l->size -= 1;
        l->freeItem(freeAux->item);
        free(freeAux);
    }
    else if (l->equalItens(right->item, item))
    {
        freeAux = right;
        nodeAux = right->previous;
        nodeAux->next = NULL;
        l->tail = nodeAux;
        l->size -= 1;
        l->freeItem(freeAux->item);
        free(freeAux);
    }
    else
    {
        do
        {
            if (l->equalItens(left->item, item))
            {
                freeAux = left;
                nodeAux = left->previous;
                nodeAux->next = left->next;
                left->next->previous = nodeAux;
                l->size -= 1;
                l->freeItem(freeAux->item);
                free(freeAux);
                break;
            }
            else if (l->equalItens(right->item, item))
            {
                freeAux = right;
                nodeAux = right->previous;
                nodeAux->next = right->next;
                right->next->previous = nodeAux;
                l->size -= 1;
                l->freeItem(freeAux->item);
                free(freeAux);
                break;
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
    while (n != NULL)
    {
        l->printItem(n->item);
        n = getNext(l, n);
    }
}

void printReverseList(List lt)
{
    list *l = lt;
    nodeList *n = l->tail;
    printf("\nLISTA REVERSA: ");
    while (n != NULL)
    {
        l->printItem(n->item);
        n = getPrevious(l, n);
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

void eraseList(List lt)
{
    list *l = lt;
    nodeList *nAux, *n = l->head;
    while (n != NULL)
    {
        nAux = n;
        n = n->next;
        if (nAux->item != NULL)
            l->freeItem(nAux->item);
        free(nAux);
    }
    free(l);
}

int sizeList(List lt)
{
    list *l = lt;
    return l->size;
}

void printListAux(List lt)
{
    list *l = lt;
    nodeList *n = l->head;
    while (n != NULL)
    {
        if (getInteger(n->item) == -1)
        {
            printf("\n");
            n = getNext(l, n);
        }
        else if (getInteger(n->item) == -2)
        {
            printf("--> ");
            n = getNext(l, n);
        }
        l->printItem(n->item);
        n = getNext(l, n);
    }
    printf("\n");
}