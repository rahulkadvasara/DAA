// Suppose that you are the person who provides the servicing facility at the doorstep of customers for various Automobile Manufacturers.
// Now, different car's service cost varies from each other and so is the profit of yours. Again, different customers require their services at different times in a day. So, you need to calculate their waiting capabilities before they look for any other persons or companies for servicing resulting your lose. So look at the given details very carefully in the attachment and try to derive the followings -
// i) Write a code which can provide optimal schedule that gives maximum profit.
// ii) Are all the jobs completed in the optimal schedule?
// iii) What is the maximum earned profit?


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char car[30];
    int deadline;
    int profit;
} Job;

void merge(Job jobs[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    Job L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = jobs[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = jobs[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].profit >= R[j].profit) {
            jobs[k] = L[i];
            i++;
        } else {
            jobs[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        jobs[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        jobs[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(Job jobs[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(jobs, left, mid);
        mergeSort(jobs, mid + 1, right);
        merge(jobs, left, mid, right);
    }
}

int findMaxDeadline(Job jobs[], int n) {
    int maxDeadline = 0;
    for (int i = 0; i < n; i++) {
        if (jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;
    }
    return maxDeadline;
}

void jobScheduling(Job jobs[], int n) {
    mergeSort(jobs, 0, n - 1);

    int maxDeadline = findMaxDeadline(jobs, n);
    Job schedule[maxDeadline];
    int slot[maxDeadline]; 

    for (int i = 0; i < maxDeadline; i++) {
        slot[i] = 0;
    }

    int totalProfit = 0;

    for (int i = 0; i < n; i++) {
        for (int j = jobs[i].deadline - 1; j >= 0; j--) {
            if (slot[j] == 0) {
                slot[j] = 1;
                schedule[j] = jobs[i];
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }
    printf("Optimal Job Schedule: ");
    for (int i = 0; i < maxDeadline; i++) {
        if (slot[i] == 1) {
            printf("Slot %d -> %s (Profit: %d)\n", i + 1, schedule[i].car, schedule[i].profit);
        }
    }
    printf("\nMaximum Earned Profit: %d\n", totalProfit);
}

int main() {
    Job jobs[] = {
        {"Maruti WagonR", 5, 500},
        {"Nissan Micra", 3, 400},
        {"Toyota Innova", 3, 1200},
        {"TATA Nexon", 2, 700},
        {"Renault Kiger", 4, 750},
        {"Maruti Grand Vitara", 2, 1100}
    };

    int n = sizeof(jobs) / sizeof(jobs[0]);
    
    jobScheduling(jobs, n);
    printf("Are all jobs completed? %s\n", (findMaxDeadline(jobs,6) == n) ? "Yes" : "No");


    return 0;
}
