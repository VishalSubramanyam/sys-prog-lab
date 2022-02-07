#include "llist.h"
#include <queue.h>

struct QUEUE createQueue()
{
    struct QUEUE temp;
    temp._queue = createList();
    return temp;
}

struct QUEUE enqueue(struct QUEUE targetQueue, int value)
{
    targetQueue._queue = insertAtEnd(targetQueue._queue, value);
    return targetQueue;
}

struct QUEUE dequeue(struct QUEUE targetQueue, int *destination)
{
    targetQueue._queue = deleteFromFront(targetQueue._queue, destination);
    return targetQueue;
}

int isEmptyQueue(struct QUEUE targetQueue)
{
    return isEmptyList(targetQueue._queue);
}

