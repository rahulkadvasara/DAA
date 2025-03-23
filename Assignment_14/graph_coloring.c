#include <stdio.h>
#include <stdbool.h>

#define V 11  // Number of vertices (radio stations)

// Function to check if coloring is valid
bool isSafe(int v, int graph[V][V], int color[], int c) {
    for (int i = 0; i < V; i++)
        if (graph[v][i] && color[i] == c) // Adjacent node has same color
            return false;
    return true;
}

// Recursive function to color the graph
bool graphColoringUtil(int graph[V][V], int m, int color[], int v) {
    if (v == V) // All vertices are colored
        return true;

    for (int c = 1; c <= m; c++) { // Try different colors
        if (isSafe(v, graph, color, c)) {
            color[v] = c; // Assign color
            if (graphColoringUtil(graph, m, color, v + 1)) // Recur for next vertex
                return true;
            color[v] = 0; // Backtrack
        }
    }
    return false;
}

// Function to solve Graph Coloring problem
void graphColoring(int graph[V][V], int m) {
    int color[V] = {0}; // Initialize colors to 0

    if (!graphColoringUtil(graph, m, color, 0)) {
        printf("Solution does not exist\n");
        return;
    }

    // Print assigned colors (frequencies)
    printf("Vertex\tColor\n");
    for (int i = 0; i < V; i++)
        printf("%d\t%d\n", i, color[i]);
}

// Main function
int main() {
    // Adjacency matrix representing the graph (edges show interference)
    int graph[V][V] = {
        {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0},
        {1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0},
        {0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1},
        {0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0}
    };

    int m = 3; // Number of colors (frequencies)
    graphColoring(graph, m);

    return 0;
}
