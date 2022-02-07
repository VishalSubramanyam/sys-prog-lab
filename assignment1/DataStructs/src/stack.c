#include <llist.h>
#include <stack.h>
#include <stdlib.h>
struct STACK createStack()
{
    struct STACK temp;
    temp._stack = createList();
    return temp;
};

int isEmptyStack(struct STACK targetStack)
{
    return isEmptyList(targetStack._stack);
}

struct STACK push(struct STACK targetStack, int k)
{
    targetStack._stack = insertAtFront(targetStack._stack, k);
    return targetStack;
}

struct STACK pop(struct STACK targetStack, int *destination)
{
    targetStack._stack = deleteFromFront(targetStack._stack, destination);
    return targetStack;
}