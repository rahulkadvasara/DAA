#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 4 // Number of vertices

// Function to find the vertex with the minimum key value
int minKey(int key[], bool mstSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (!mstSet[v] && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

// Function to construct MST using Prim's Algorithm
void primMST(int graph[V][V]) {
    int parent[V]; // Stores constructed MST
    int key[V];    // Key values to pick the minimum weight edge
    bool mstSet[V];// To represent the set of vertices included in MST

    // Initialize all keys as infinite and mstSet[] as false
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    key[0] = 0;      // Make key 0 so that this vertex is picked first
    parent[0] = -1;  // First node is always the root of MST

    // Construct MST
    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet); // Pick the minimum key vertex
        mstSet[u] = true;

        for (int v = 0; v < V; v++)
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    // Printing the MST
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

// Driver function
int main() {
    int graph[V][V] = {
        {0, 4, 5, 0},
        {4, 0, 6, 2},
        {5, 6, 0, 1},
        {0, 2, 1, 0}
    };

    primMST(graph);
    return 0;
}
