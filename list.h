#ifndef list_h
#define list_h

typedef void *List;
typedef void *Posic;
typedef int Item;

List createList();
void insertList(List lt, Item item);
void removeItemList(List lt, Item item);
void printList(List lt);
void printReverseList(List lt);
void freeList(List lt);
int sizeList(List lt);

#endif
