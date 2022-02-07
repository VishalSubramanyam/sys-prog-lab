#ifndef _LLIST_H
#define _LLIST_H

struct NODE{
    int value;
    struct NODE * next;
};

struct LLIST{
    struct NODE * head;
    struct NODE * rear;
};

struct LLIST createList();

int searchList(struct LLIST targetList, int value);

struct LLIST insertAtFront(struct LLIST targetList, int value);

struct LLIST insertAtEnd(struct LLIST targetList, int value);

struct LLIST deleteFromFront(struct LLIST targetList, int *k);

struct LLIST deleteFromEnd(struct LLIST targetList, int *k);

struct LLIST deleteList(struct LLIST targetList, int value);

int isEmptyList(struct LLIST targetList);

void printList(struct LLIST targetList);
#endif
