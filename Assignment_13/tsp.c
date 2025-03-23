#include <stdio.h>
#include <limits.h>

#define N 4         // Number of cities
#define INF INT_MAX // Represents infinity

int dp[16][N]; // Memoization table for DP
int cost[N][N] = {  // Given cost matrix from the image
    {0, 10, 15, 20}, // Costs from City A
    {10, 0, 35, 25}, // Costs from City B
    {15, 35, 0, 30}, // Costs from City C
    {20, 25, 30, 0}  // Costs from City D
};

// Function to find the minimum cost using Dynamic Programming
int tsp(int mask, int pos) {
    if (mask == (1 << N) - 1) // All cities visited
        return cost[pos][0];  // Return to starting city

    if (dp[mask][pos] != -1)  // Already computed
        return dp[mask][pos];

    int ans = INF;
    
    for (int city = 0; city < N; city++) {
        if ((mask & (1 << city)) == 0) { // If city is not visited
            int newAns = cost[pos][city] + tsp(mask | (1 << city), city);
            if (newAns < ans)
                ans = newAns;
        }
    }

    return dp[mask][pos] = ans; // Store result in DP table
}

// Main function
int main() {
    // Initialize DP table with -1 (uncomputed states)
    for (int i = 0; i < (1 << N); i++)
        for (int j = 0; j < N; j++)
            dp[i][j] = -1;

    int minCost = tsp(1, 0); // Start from City A (index 0)
    
    printf("Minimum Travelling Cost: %d\n", minCost);
    return 0;
}
