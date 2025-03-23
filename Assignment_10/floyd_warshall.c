#include <stdio.h>

#define V 5
#define INF 99999  // Large value representing infinity

// Floyd-Warshall Algorithm
void floydWarshall(int graph[V][V]) {
    int dist[V][V], i, j, k;

    // Initialize distance matrix same as the input graph matrix
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    // Dynamic Programming: Compute shortest paths
    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][j] > dist[i][k] + dist[k][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Print the shortest distance matrix
    printf("Shortest distances between every pair of vertices:\n");
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("%4s", "INF");
            else
                printf("%4d", dist[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int graph[V][V] = {
        {0, 3, INF, 2, 4},
        {INF, 0, 4, INF, 7},
        {INF, INF, 0, 8, INF},
        {INF, INF, 1, 0, 6},
        {INF, INF, INF, INF, 0}
    };

    floydWarshall(graph);
    return 0;
}
