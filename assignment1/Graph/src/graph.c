#include <assert.h>
#include <graph.h>
#include <memory.h>
#include <queue.h>
#include <stack.h>
#include <stdio.h>
#include <stdlib.h>
#include <union_find.h>
struct GRAPH
readGraph (char *filename)
{
    struct GRAPH temp;
    for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
                {
                    temp.adjacency_matrix[i][j] = 0;
                }
        }

    FILE *file = fopen (filename, "r");
    if (file == NULL)
        {
            fprintf (stderr, "%s\n", "Could not open graph file!");
            exit (-1);
        }

    int n;
    int m;

    fscanf (file, "%d", &n);
    fscanf (file, "%d", &m);
    assert (n <= 100);               // maximum capacity is 100
    assert (m <= (n * (n - 1)) / 2); // cannot have multiple edges

    temp.n = n;
    temp.m = m;

    for (int i = 0; i < m; i++)
        {
            int u, v, w;
            fscanf (file, "%d", &u);
            fscanf (file, "%d", &v);
            fscanf (file, "%d", &w);

            assert (u < n && v < n); // Range of u/v is from 0 to n-1
            assert (temp.adjacency_matrix[u][v]
                    == 0); // ensuring no repeated edges
            assert (temp.adjacency_matrix[v][u] == 0);
            temp.adjacency_matrix[u][v] = w;
            temp.adjacency_matrix[v][u] = w;
        }
    return temp;
}

static void
doDFS (struct GRAPH const *targetGraph, int visited[100], int node)
{
    assert (node < targetGraph->n);
    assert (visited[node] == 0);

    struct STACK stack = createStack ();
    stack = push (stack, node);
    visited[node] = 1;
    while (!isEmptyStack (stack))
        {
            int currentNode;
            stack = pop (stack, &currentNode);
            printf ("Node: %d\n", currentNode);
            for (int i = 0; i < targetGraph->n; i++)
                {
                    if (visited[i] == 0
                        && targetGraph->adjacency_matrix[i][currentNode] != 0)
                        {
                            stack = push (stack, i);
                            visited[i] = 1;
                        }
                }
        }
}

static void
doBFS (struct GRAPH const *targetGraph, int visited[100], int node)
{
    assert (node < targetGraph->n);
    assert (visited[node] == 0);

    struct QUEUE queue = createQueue ();
    visited[node] = 1;
    queue = enqueue (queue, node);
    while (!isEmptyQueue (queue))
        {
            int currentNode;
            queue = dequeue (queue, &currentNode);
            printf ("Node: %d\n", currentNode);
            for (int i = 0; i < targetGraph->n; i++)
                {
                    if (visited[i] == 0
                        && targetGraph->adjacency_matrix[i][currentNode] != 0)
                        {
                            queue = enqueue (queue, i);
                            visited[i] = 1;
                        }
                }
        }
}

void
DFS (struct GRAPH targetGraph)
{
    int visited[100];
    memset (visited, 0, sizeof (visited));
    int count = 1;
    for (int i = 0; i < targetGraph.n; i++)
        {
            if (visited[i] != 1)
                {
                    printf ("%s %d\n", "DFS Forest", count);
                    count++;

                    doDFS (&targetGraph, visited, i);
                }
        }
}

void
BFS (struct GRAPH targetGraph)
{
    int visited[100];
    memset (visited, 0, sizeof (visited));
    int count = 1;
    for (int i = 0; i < targetGraph.n; i++)
        {
            if (visited[i] != 1)
                {
                    printf ("%s %d\n", "BFS Forest", count);
                    count++;

                    doBFS (&targetGraph, visited, i);
                }
        }
}

struct EDGE
{
    int u, v, w;
};

typedef struct EDGE EDGE;

static void
merge (EDGE arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    EDGE *L = (EDGE *)malloc (n1 * sizeof (EDGE));
    EDGE *R = (EDGE *)malloc (n2 * sizeof (EDGE));

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        {
            if (L[i].w <= R[j].w)
                {
                    arr[k] = L[i];
                    i++;
                }
            else
                {
                    arr[k] = R[j];
                    j++;
                }
            k++;
        }

    while (i < n1)
        {
            arr[k] = L[i];
            i++;
            k++;
        }

    while (j < n2)
        {
            arr[k] = R[j];
            j++;
            k++;
        }
    free (L);
    free (R);
}

static void
merge_sort (EDGE arr[], int l, int r)
{
    if (l < r)
        {
            int m = l + (r - l) / 2; // to avoid overflow during addition

            merge_sort (arr, l, m);
            merge_sort (arr, m + 1, r);

            merge (arr, l, m, r);
        }
}

void
MST (struct GRAPH targetGraph)
{
    printf("MST\n");
    EDGE *edges = (EDGE *)malloc (targetGraph.m * sizeof (EDGE));

    int cost = 0;

    struct UNION_FIND uf = createUF (targetGraph.n);

    for (int i = 0; i < targetGraph.n; i++)
        {
            int temp;
            uf = makeSetUF (uf, i, &temp);
            assert(temp == i);
        }
    assert(uf.numberOfElements == uf.capacity);
    int count = 0;
    // read the edges
    for(int i = 0; i < targetGraph.n; i++)
    {
        for(int j = i; j < targetGraph.n; j++)
        {
            if(targetGraph.adjacency_matrix[i][j] != 0){
                assert(count < targetGraph.m);
                edges[count].u = i;
                edges[count].v = j;
                edges[count].w = targetGraph.adjacency_matrix[i][j];
                count++;
            }
        }
    }
    assert(count == targetGraph.m);
    merge_sort(edges, 0, count-1);

    //DEBUG
    for(int i = 0; i < count - 1; i++){
        assert(edges[i].w <= edges[i+1].w);
    }

    for(int i = 0; i < count; i++)
    {
        EDGE currentEdge = edges[i];
        if(findUF(uf, currentEdge.u) != findUF(uf, currentEdge.v)){
            cost += currentEdge.w;
            printf("%d %d %d\n", currentEdge.u, currentEdge.v, currentEdge.w);
            unionUF(uf, currentEdge.u, currentEdge.v);
        }
    }
    printf("Minimum spanning tree cost: %d\n", cost);
    free (edges);
}