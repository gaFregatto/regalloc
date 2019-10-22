#ifndef stack_h
#define stack_h

typedef void *Stack;
typedef void *Item;
typedef void (*fr)(Item);

Stack newStack(fr printItem, fr freeItem);
void push(Stack s, Item n);
Item pop(Stack s);
int sizeStack(Stack s);
void freeStack(Stack s);
void eraseStack(Stack s);
int emptyStack(Stack s);
void printStack(Stack s);

#endif