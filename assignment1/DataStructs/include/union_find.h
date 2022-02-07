struct UF_NODE
{
    struct UF_NODE *parent;
    int value;
    int sizeOfTree;
};

typedef struct UF_NODE *NODE_PTR;

struct UNION_FIND
{
    NODE_PTR arrayOfNodes;
    int capacity;
    int numberOfElements;
};

struct UNION_FIND createUF (int n);
struct UNION_FIND makeSetUF (struct UNION_FIND targetUF, int valueToBeStored,
                             int *index);

// Returns the ID of the set to which the the value at the i-th position
// belongs. The ID of the set is defined as the pointer to the root node
// of the tree representing the set.
NODE_PTR findUF (struct UNION_FIND targetUF, int index);

// Merge sets containing the elements pointed to by the i-th and
// j-th pointers of the targetUF
void unionUF (struct UNION_FIND targetUF, int i, int j);
