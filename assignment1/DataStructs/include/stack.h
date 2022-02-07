#ifndef _STACK_H
#define _STACK_H

#include <llist.h>
struct STACK
{
    struct LLIST _stack;
};

struct STACK createStack();

int isEmptyStack(struct STACK targetStack);

struct STACK push(struct STACK targetStack, int k);

struct STACK pop(struct STACK targetStack, int *destination);

#endif
