#include <stdio.h>

#define V 5
#define INF 99999 // Represents infinity

// Function to print the distance matrix
void printSolution(int dist[][V]) {
    printf("Shortest distances between every pair of vertices:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("%4s", "INF");
            else
                printf("%4d", dist[i][j]);
        }
        printf("\n");
    }
}

// Function to implement Floyd-Warshall Algorithm
void floydWarshall(int graph[][V]) {
    int dist[V][V];

    // Initialize the solution matrix with the given graph
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    // Apply Floyd-Warshall algorithm
    for (int k = 0; k < V; k++) { // Intermediate vertex
        for (int i = 0; i < V; i++) { // Source vertex
            for (int j = 0; j < V; j++) { // Destination vertex
                // Update dist[i][j] if a shorter path is found through k
                if (dist[i][k] != INF && dist[k][j] != INF && 
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Print the final shortest distance matrix
    printSolution(dist);
}

// Main function
int main() {
    int graph[V][V] = {
        {0, 2, INF, INF, INF},
        {1, 0, INF, -3, INF},
        {INF, 1, 0, 9, 2},
        {INF, INF, INF, 0, 3},
        {INF, INF, INF, INF, 0}
    };

    floydWarshall(graph);
    
    return 0;
}
