#include <stdio.h>
#include <limits.h>

#define N 4  // Number of matrices

// Function to print the optimal parenthesization
void printOptimalParens(int s[N][N], int i, int j) {
    if (i == j)
        printf("M%d", i + 1);
    else {
        printf("(");
        printOptimalParens(s, i, s[i][j]);
        printOptimalParens(s, s[i][j] + 1, j);
        printf(")");
    }
}

// Function to compute the optimal order of matrix multiplication
void matrixChainOrder(int p[], int n) {
    int m[N][N], s[N][N];

    // Initialize matrices
    for (int i = 0; i < n; i++)
        m[i][i] = 0;

    // Chain length from 2 to n
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i < n - len + 1; i++) {
            int j = i + len - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int cost = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }

    // Print results
    printf("Minimum number of multiplications: %d\n", m[0][n - 1]);
    printf("Optimal parenthesization: ");
    printOptimalParens(s, 0, n - 1);
    printf("\n");
}

// Main function
int main() {
    int p[] = {2, 6, 4, 5, 1};  // Dimensions
    matrixChainOrder(p, N);
    return 0;
}
