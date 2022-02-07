#include <heap.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

static void
swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static int
parent (int position)
{
    return (position - 1) / 2;
}

struct HEAP
createHeap ()
{
    struct HEAP temp;
    memset (temp.internalArr, 0, sizeof (temp.internalArr));
    temp.size = 0;
    temp.capacity = sizeof(temp.internalArr)/sizeof(temp.internalArr[0]);
    return temp;
}

int isFullHeap(struct HEAP targetHeap)
{
    return targetHeap.size == targetHeap.capacity;
}

int
isEmptyHeap (struct HEAP targetHeap)
{
    return targetHeap.size == 0;
}

int
findMin (struct HEAP targetHeap)
{
    if (isEmptyHeap (targetHeap))
        {
            fprintf (stderr, "%s\n",
                     "Cannot find the min element in an empty heap.");
            exit (-1);
        }
    else
        {
            return targetHeap.internalArr[0];
        }
}

struct HEAP
extractMin (struct HEAP targetHeap)
{
    if (isEmptyHeap (targetHeap))
        {
            fprintf (stderr, "%s\n",
                     "Cannot extract minimum from an empty heap!");
            exit (-1);
        }
    int *internalArr = targetHeap.internalArr; // for convenience
    int *size = &targetHeap.size;              // for convenience

    // swap root and last leaf
    int temp = internalArr[0];
    internalArr[0] = internalArr[*size - 1];
    internalArr[*size - 1] = temp;

    (*size)--; // Decrement the size of the heap

    int currentPosition = 0; // Starting with the root of the heap

    // while the node we are currently looking at is valid
    while (currentPosition < *size)
        {
            int left_child = 2 * currentPosition + 1;
            int right_child = 2 * currentPosition + 2;
            if (right_child < *size
                && internalArr[left_child] > internalArr[right_child])
                {
                    swap (&internalArr[right_child],
                          &internalArr[currentPosition]);
                    currentPosition = right_child;
                }
            else if (left_child < *size
                     && internalArr[left_child] < internalArr[currentPosition])
                {
                    swap (&internalArr[left_child],
                          &internalArr[currentPosition]);
                    currentPosition = left_child;
                }
            else
                break;
        }
    return targetHeap;
}

struct HEAP
insertHeap (struct HEAP targetHeap, int value)
{
    if(isFullHeap(targetHeap))
    {
        fprintf(stderr, "%s\n", "Heap insertion failed because heap is full!");
        exit(-1);
    }
    int *size = &targetHeap.size;
    int *internalArr = targetHeap.internalArr;

    (*size)++;

    internalArr[*size - 1] = value;
    for (int currentPosition = *size - 1;
         currentPosition != parent (currentPosition)
         && internalArr[currentPosition]
                < internalArr[parent (currentPosition)];
         currentPosition = parent (currentPosition))
        {
            swap (&internalArr[currentPosition],
                  &internalArr[parent (currentPosition)]);
        }
    return targetHeap;
}
/*
static void fixNode(struct HEAP *targetHeap, int position) {
    int left_child = 2 * position + 1;
    int right_child = 2 * position + 2;
    int *internalArr = targetHeap->internalArr;
    if (left_child < targetHeap->size) {
        if (internalArr[left_child] < internalArr[position]) {
            int temp = internalArr[left_child];
            internalArr[left_child] = internalArr[position];
            internalArr[position] = temp;
        }
    }
    if (right_child < targetHeap->size) {
        if (internalArr[right_child] < internalArr[position]) {
            int temp = internalArr[right_child];
            internalArr[right_child] = internalArr[position];
            internalArr[position] = temp;
        }
    }
}
*/
