// Suppose that you are the person who provides the servicing facility at the doorstep of customers for various Automobile Manufacturers.
// Now, different car's service cost varies from each other and so is the profit of yours. Again, different customers require their services at different times in a day. So, you need to calculate their waiting capabilities before they look for any other persons or companies for servicing resulting your lose. So look at the given details very carefully in the attachment and try to derive the followings -
// i) Write a code which can provide optimal schedule that gives maximum profit.
// ii) Are all the jobs completed in the optimal schedule?
// iii) What is the maximum earned profit?


#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int profit;
    int deadline;
} Job;

void merge(Job arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    Job L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].profit >= R[j].profit) {
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

void mergeSort(Job arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}
void printJobScheduling(Job arr[], int n) {
    mergeSort(arr, 0, n - 1);
    int maxDeadline = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i].deadline > maxDeadline) {
            maxDeadline = arr[i].deadline;
        }
    }
    int result[n];
    int slot[n];

    for (int i = 0; i < n; i++) {
        slot[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int deadline = (arr[i].deadline < n ? arr[i].deadline : n) - 1;
        while (deadline >= 0 && slot[deadline] != 0) {
            deadline--;
        }
        if (deadline >= 0) {
            result[deadline] = i;
            slot[deadline] = 1;
        }
    }

    int totalProfit = 0;
    printf("Job sequence for maximum profit:\n");
    for (int i = 0; i < n; i++) {
        if (slot[i]) {
            printf("Job %d\n", arr[result[i]].id);
            totalProfit += arr[result[i]].profit;
        }
    }
    printf("Maximum earned profit: %d\n", totalProfit);
}

int main() {
    Job arr[] = {{1, 500, 5}, {2, 400, 3}, {3, 1200, 3}, {4, 700, 2}, {5, 750, 4}, {6, 1100, 2}};
    int n = sizeof(arr) / sizeof(arr[0]);
    printJobScheduling(arr, n);
    return 0;
}