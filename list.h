#ifndef list_h
#define list_h

typedef void *List;
typedef void *Posic;
typedef void *Item;
typedef void (*fr)(Item);
typedef int (*fe)(Item, Item);
typedef int (*sortKey)(Item);

List newList(fr printItem, fr freeItem, fe equalItens);
Item getItem(List lt, Posic p);
Posic getNext(List lt, Posic p);
Posic getPrevious(List lt, Posic p);
Posic getFirst(List lt);
Posic getLast(List lt);
void insertList(List lt, Item item);
void removeList(List lt, Posic p);
void removeItemList(List lt, Posic p);
void removeListByItem(List lt, Item item);
void printList(List lt);
void printReverseList(List lt);
void freeList(List lt);
void eraseList(List lt);
int sizeList(List lt);
void printListAux(List lt);

#endif
