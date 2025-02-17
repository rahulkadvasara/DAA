// A thief enters a house for robbing it. He can carry a maximal weight of 60 kg into his bag.
// There are 5 items in the house with the following weights and values (LOOK AT THE PICTURE ATTACHED FOR THE DETAILS).
// What items should thief take if he can even take the fraction of any item with him?



#include <stdio.h>
#include <stdlib.h>

struct Item {
    int item;
    int weight;
    int profit;
};

void merge(struct Item arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    struct Item L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        double r1 = (double)L[i].profit / L[i].weight;
        double r2 = (double)R[j].profit / R[j].weight;
        if (r1 >= r2) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(struct Item arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

double fractionalKnapsack(int W, struct Item arr[], int n) {
    mergeSort(arr, 0, n - 1);

    int curWeight = 0;
    printf("Items taken:\n");
    printf("ID\tWeight\tProfit\tQuantity\tTotal Profit\n");
    double finalprofit = 0.0;

    for (int i = 0; i < n; i++) {
        if (curWeight + arr[i].weight <= W) {
            curWeight += arr[i].weight;
            finalprofit += arr[i].profit;
            printf("%d\t%d\t%d\t%d\t\t%.2f\n", arr[i].item, arr[i].weight, arr[i].profit, 1, (double)arr[i].profit);
        } else {
            int remain = W - curWeight;
            finalprofit += arr[i].profit * ((double)remain / arr[i].weight);
            printf("%d\t%d\t%d\t%.2f\t\t%.2f\n", arr[i].item, arr[i].weight, arr[i].profit, (double)remain / arr[i].weight, arr[i].profit * ((double)remain / arr[i].weight));
            break;
        }
    }

    return finalprofit;
}

int main() {
    int W = 60; // Maximum weight the thief can carry
    struct Item arr[] = {{1, 5, 30}, {2, 10, 40}, {3, 15, 45}, {4, 22, 77}, {5, 25, 90}};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Maximum profit we can obtain = %.2f\n", fractionalKnapsack(W, arr, n));
    return 0;
}