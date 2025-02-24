// Suppose that you are the person who provides the servicing facility at the doorstep of customers for various Automobile Manufacturers.
// Now, different car's service cost varies from each other and so is the profit of yours. Again, different customers require their services at different times in a day. So, you need to calculate their waiting capabilities before they look for any other persons or companies for servicing resulting your lose. So look at the given details very carefully in the attachment and try to derive the followings -
// i) Write a code which can provide optimal schedule that gives maximum profit.
// ii) Are all the jobs completed in the optimal schedule?
// iii) What is the maximum earned profit?


#include <stdio.h>
#include <stdbool.h>

// Structure to represent a job
typedef struct {
    int id;
    int profit;
    int deadline;
} Job;

// Merge function for Merge Sort
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

// Merge Sort function
void mergeSort(Job jobs[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(jobs, left, mid);
        mergeSort(jobs, mid + 1, right);
        merge(jobs, left, mid, right);
    }
}

// Function to find the maximum deadline
int findMaxDeadline(Job jobs[], int n) {
    int maxDeadline = 0;
    for (int i = 0; i < n; i++) {
        if (jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;
    }
    return maxDeadline;
}

// Function to schedule jobs for maximum profit
void jobScheduling(Job jobs[], int n) {
    // Sort jobs based on profit in descending order
    mergeSort(jobs, 0, n - 1);

    int maxDeadline = findMaxDeadline(jobs, n);
    int slot[maxDeadline];  // To store job ID scheduled at each time slot
    bool slotFilled[maxDeadline];  // To check if the slot is filled

    for (int i = 0; i < maxDeadline; i++) {
        slotFilled[i] = false;
        slot[i] = -1;
    }

    int totalProfit = 0, jobsCompleted = 0;

    for (int i = 0; i < n; i++) {
        for (int j = jobs[i].deadline - 1; j >= 0; j--) {
            if (!slotFilled[j]) {
                slot[j] = jobs[i].id;
                slotFilled[j] = true;
                totalProfit += jobs[i].profit;
                jobsCompleted++;
                break;
            }
        }
    }

    // Print scheduled jobs
    printf("Optimal Job Schedule: ");
    for (int i = 0; i < maxDeadline; i++) {
        if (slotFilled[i])
            printf("Job %d ", slot[i]);
    }
    printf("\n");

    // Print results
    printf("Are all jobs completed? %s\n", (jobsCompleted == n) ? "Yes" : "No");
    printf("Maximum Earned Profit: %d\n", totalProfit);
}

// Driver function
int main() {
    Job jobs[] = {
        {1, 500, 2},
        {2, 400, 1},
        {3, 1200, 1},
        {4, 700, 1},
        {5, 750, 2},
        {6, 1100, 3}
    };

    int n = sizeof(jobs) / sizeof(jobs[0]);

    jobScheduling(jobs, n);

    return 0;
}
