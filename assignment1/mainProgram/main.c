#include <graph.h>
#include <stdio.h>

int main()
{
    printf("Enter filename: ");
    char fname[100]; //absolute filename advised
    scanf("%s", fname);
    struct GRAPH g = readGraph(fname);
    DFS(g);
    BFS(g);
    MST(g);
    return 0;
}