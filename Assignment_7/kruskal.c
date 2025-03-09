// Find Minimum Cost Spanning Tree of a given undirected graph using Kruskal’s algorithm.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_EDGES 10
#define MAX_VERTICES 10

struct Edge {
    char src, dest;
    int weight;
};

struct Subset {
    int parent, rank;
};

int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void unionSet(struct Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);
    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

void shuffleEdges(struct Edge edges[], int E) {
    srand(time(NULL));
    for (int i = E - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        struct Edge temp = edges[i];
        edges[i] = edges[j];
        edges[j] = temp;
    }
}

void merge(struct Edge edges[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    struct Edge L[n1], R[n2];
    
    for (int i = 0; i < n1; i++)
        L[i] = edges[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = edges[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].weight <= R[j].weight)
            edges[k++] = L[i++];
        else
            edges[k++] = R[j++];
    }
    while (i < n1)
        edges[k++] = L[i++];
    while (j < n2)
        edges[k++] = R[j++];
}

void mergeSort(struct Edge edges[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(edges, left, mid);
        mergeSort(edges, mid + 1, right);
        merge(edges, left, mid, right);
    }
}

void kruskal(struct Edge edges[], int V, int E) {
    struct Edge result[MAX_VERTICES];
    int e = 0, i = 0;
    
    shuffleEdges(edges, E);
    mergeSort(edges, 0, E - 1);
    
    struct Subset subsets[MAX_VERTICES];
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    while (e < V - 1 && i < E) {
        struct Edge nextEdge = edges[i++];
        int x = find(subsets, nextEdge.src - 'A');
        int y = find(subsets, nextEdge.dest - 'A');
        
        if (x != y) {
            result[e++] = nextEdge;
            unionSet(subsets, x, y);
        }
    }
    printf("Minimum Cost Spanning Tree using Kruskal's Algorithm: \n");
    int minCost = 0;
    for (i = 0; i < e; i++) {
        printf("%c -- %c == %d\n", result[i].src, result[i].dest, result[i].weight);
        minCost += result[i].weight;
    }
    printf("Total Minimum Cost: %d\n", minCost);
}

int main() {
    int V = 5, E = 7;
    struct Edge edges[] = {
        {'A', 'C', 1}, {'A', 'B', 3}, {'B', 'E', 3}, {'A', 'D', 4},
        {'C', 'D', 5}, {'D', 'E', 2}, {'B', 'D', 6}
    };
    
    kruskal(edges, V, E);
    return 0;
}
