#ifndef stack_h
#define stack_h

typedef void *Stack;

Stack createStack();
void push(Stack s, int n);
int pop(Stack s);
int sizeStack(Stack s);
void freeStack(Stack s);
int emptyStack(Stack s);
void printStack(Stack s);

#endif