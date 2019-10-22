#ifndef integer_h
#define integer_h

typedef void *Integer;

Integer newInteger(int i);
void printInteger(Integer it);
void freeInteger(Integer it);
int getInteger(Integer it);
int equalIntegers(Integer a, Integer b);

#endif