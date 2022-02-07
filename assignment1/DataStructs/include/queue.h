#ifndef _QUEUE_H
#define _QUEUE_H

#include <llist.h>

struct QUEUE {
    struct LLIST _queue;
};

struct QUEUE createQueue();

struct QUEUE enqueue(struct QUEUE targetQueue, int value);

struct QUEUE dequeue(struct QUEUE targetQueue, int *destination);

int isEmptyQueue(struct QUEUE targetQueue);

#endif //_QUEUE_H