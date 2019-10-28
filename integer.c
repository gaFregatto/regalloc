#include <stdio.h>
#include <stdlib.h>
#include "integer.h"

Integer newInteger(int i)
{
    int *x = malloc(sizeof(int));
    *x = i;
    return x;
}

void printInteger(Integer it)
{
    int *x = it;
    printf("%d ", *x);
}

void freeInteger(Integer it)
{
    int *x = it;
    free(x);
}

int getInteger(Integer it)
{
    int *x = it;
    return *x;
}

int equalIntegers(Integer a, Integer b)
{
    int *x = a;
    int *y = b;
    if (*x == *y)
        return 1;
    else
        return 0;
}