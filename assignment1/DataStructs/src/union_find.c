#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <union_find.h>

struct UNION_FIND
createUF (int n)
{
    struct UNION_FIND temp;
    temp.arrayOfNodes = (NODE_PTR)malloc (n * sizeof (struct UF_NODE));
    for (int i = 0; i < n; i++)
        {
            temp.arrayOfNodes[i].parent = NULL;
            temp.arrayOfNodes[i].value = -1;
            temp.arrayOfNodes[i].sizeOfTree = 0;
        }
    temp.capacity = n;
    temp.numberOfElements = 0;
    return temp;
}

struct UNION_FIND
makeSetUF (struct UNION_FIND targetUF, int valueToBeStored, int *index)
{
    if (targetUF.numberOfElements >= targetUF.capacity)
        {
            fprintf (stderr, "%s\n",
                     "Cannot make another set. Capacity full!");
            exit (-1);
        }
    // set the node's parent to itself since it's a new set
    // and it is the root of its own tree
    targetUF.arrayOfNodes[targetUF.numberOfElements].parent
        = &(targetUF.arrayOfNodes[targetUF.numberOfElements]);

    // storing the value in the new node
    targetUF.arrayOfNodes[targetUF.numberOfElements].value = valueToBeStored;

    // set the size of the tree under this new node as 1
    // since it is a new tree with only this new node in it
    targetUF.arrayOfNodes[targetUF.numberOfElements].sizeOfTree = 1;

    // this is the location of this new node in the internal
    // array. Inserted right after the location of previous node insertion
    *index = targetUF.numberOfElements;

    // the number of valid elements in this structure is increased
    targetUF.numberOfElements++;

    assert (targetUF.numberOfElements <= targetUF.capacity);
    return targetUF;
}

NODE_PTR
findUF (struct UNION_FIND targetUF, int index)
{
    if (index >= targetUF.numberOfElements)
        {
            fprintf (stderr, "%s\n", "Index greater the number of elements!");
            exit (-1);
        }
    NODE_PTR currentNode = targetUF.arrayOfNodes + index;
    // condition for a node to be the root of a tree is that
    // its parent should be itself (self loop)
    while (currentNode->parent != currentNode)
        {
            currentNode = currentNode->parent;
        }
    return currentNode;
}

void
unionUF (struct UNION_FIND targetUF, int i, int j)
{
    if(i >= targetUF.numberOfElements || j >= targetUF.numberOfElements)
    {
        fprintf(stderr, "%s\n", "Invalid index provided in unionUF!");
    }
    NODE_PTR a = findUF (targetUF, i);
    NODE_PTR b = findUF (targetUF, j);
    // Ensuring that we have parents
    assert (a->parent == a);
    assert (b->parent == b);

    // Ensuring valid tree sizes
    assert (a->sizeOfTree <= targetUF.numberOfElements);
    assert (b->sizeOfTree <= targetUF.numberOfElements);

    // if both of them belong to the same set (have same parent),
    // no need to do anything.
    if (a != b)
        {
            if (a->sizeOfTree < b->sizeOfTree)
                {
                    a->parent = b;
                    b->sizeOfTree += a->sizeOfTree;
                }
            else
                {
                    b->parent = a;
                    a->sizeOfTree += b->sizeOfTree;
                }
        }
}
