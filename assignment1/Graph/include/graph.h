struct GRAPH
{
    int adjacency_matrix[100][100];
    int n;
    int m;
};

struct GRAPH readGraph(char *filename); 

void DFS(struct GRAPH targetGraph);
void BFS(struct GRAPH targetGraph);
void MST(struct GRAPH targetGraph);