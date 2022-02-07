#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <llist.h>

struct LLIST createList()
{
    struct LLIST temp;
    temp.head = NULL;
    temp.rear = NULL;
    return temp;
}

int searchList(struct LLIST targetList, int value)
{
	for(struct NODE * currentNode = targetList.head;
        currentNode != NULL;
        currentNode=currentNode->next)
	{
        if(currentNode->value == value){
            return 1;
        }
	}
    return 0;
}

struct LLIST insertAtFront(struct LLIST targetList, int value)
{
    struct NODE * new_node = (struct NODE *) malloc(sizeof(struct NODE));
    new_node->value = value;
    new_node->next = targetList.head;
    targetList.head = new_node;
    if(targetList.rear == NULL)
    {
        targetList.rear = new_node;
    }
    return targetList;
}

struct LLIST insertAtEnd(struct LLIST targetList, int value)
{
    struct NODE * new_node = (struct NODE *) malloc(sizeof(struct NODE));
    new_node->value = value;
    new_node->next = NULL;
    if(targetList.rear == NULL){
        targetList.head = new_node;
    }
    else{
        targetList.rear->next = new_node;
    }
    targetList.rear = new_node;
    return targetList;
}

struct LLIST deleteFromFront(struct LLIST targetList, int *k)
{
    assert(targetList.head != NULL);
    assert(targetList.head != NULL);

    *k = targetList.head->value;

    struct NODE * temp = targetList.head;
    targetList.head = targetList.head->next;
    // if the rear pointer points to the original head,
    // it means that the list had length 1.
    // Therefore, after deletion of this one node, rear
    // should be NULLIFIED.
    if(targetList.rear == temp) targetList.rear = NULL;
    free(temp);
    return targetList;
}

struct LLIST deleteFromEnd(struct LLIST targetList, int *k)
{
    assert(targetList.head != NULL);
    assert(targetList.rear != NULL);

    *k = targetList.rear->value;

    if(targetList.head == targetList.rear)
    {
        free(targetList.rear);
        targetList.head = targetList.rear = NULL;
    }
    else
    {
        struct NODE *currentNode;
        for(currentNode = targetList.head;
            currentNode->next != targetList.rear;
            currentNode = currentNode->next);
        currentNode->next = NULL;
        free(targetList.rear);
        targetList.rear = currentNode;
    }
    return targetList;
}

struct LLIST deleteList(struct LLIST targetList, int value)
{
    if(targetList.head->value == value)
    {
        int tmp; // just a temp variable
        return deleteFromFront(targetList, &tmp);
    }
    else
    {
        struct NODE * currentNode;
        for(currentNode = targetList.head;
            currentNode && currentNode->next && currentNode->next->value != value;
            currentNode = currentNode->next);
        if(currentNode)
        {
            struct NODE * temp = currentNode->next;
            currentNode->next = currentNode->next->next;
            if(currentNode->next == NULL) targetList.rear = currentNode;
            free(temp);
        } 
        return targetList;
    }
}

int isEmptyList(struct LLIST targetList)
{
    return (targetList.head == NULL) ? 1 : 0;
}

void printList(struct LLIST targetList)
{
    for(struct NODE * currentNode = targetList.head;
        currentNode;
        currentNode = currentNode->next)
    {
        printf("Node value: %d\n", currentNode->value);
    }
}
