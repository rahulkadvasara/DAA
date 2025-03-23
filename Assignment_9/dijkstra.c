#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 6  // Number of vertices

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (!sptSet[v] && dist[v] < min)
            min = dist[v], min_index = v;
    return min_index;
}

// Function to print the shortest distance from the source
void printSolution(int dist[]) {
    printf("Vertex \tDistance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t%d\n", i, dist[i]);
}

// Function implementing Dijkstra's algorithm
void dijkstra(int graph[V][V], int src) {
    int dist[V];  // Distance values
    bool sptSet[V]; // Shortest path tree set

    // Initialize all distances as infinite and sptSet[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[src] = 0; // Distance of source vertex from itself is always 0

    // Find the shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet); // Pick the minimum distance vertex
        sptSet[u] = true;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // Print the result
    printSolution(dist);
}

// Driver function
int main() {
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 10},
        {4, 0, 2, 0, 0, 0},
        {0, 2, 0, 1, 6, 0},
        {0, 0, 1, 0, 3, 0},
        {0, 0, 6, 3, 0, 5},
        {10, 0, 0, 0, 5, 0}
    };

    int src = 0; // Source vertex
    dijkstra(graph, src);

    return 0;
}
