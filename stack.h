#ifndef stack_h
#define stack_h

typedef void *Stack;
typedef int Item;

Stack createStack();
void push(Stack s, Item n);
int pop(Stack s);
int sizeStack(Stack s);
void freeStack(Stack s);
int emptyStack(Stack s);
void printStack(Stack s);

#endif