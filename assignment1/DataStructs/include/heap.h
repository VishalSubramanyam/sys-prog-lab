#ifndef _HEAP_H
#define _HEAP_H
#define _HEAP_CAPACITY 100
struct HEAP {
    int internalArr[_HEAP_CAPACITY];
    int size;
    int capacity;
};

struct HEAP createHeap();
int findMin(struct HEAP targetHeap);
struct HEAP extractMin(struct HEAP targetHeap);
struct HEAP insertHeap(struct HEAP targetHeap, int value);
int isFullHeap(struct HEAP targetHeap);
int isEmptyHeap(struct HEAP targetHeap);
#endif //_HEAP_H
