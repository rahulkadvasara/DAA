Here is the updated C code for the Job Sequencing Problem using Merge Sort while ensuring we only allocate slots up to the maximum deadline.


---

Updated C Code

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store job details
typedef struct {
    char car[30];  // Car name
    int deadline;  // Deadline for the job
    int profit;    // Profit associated with the job
} Job;

// Function to merge two sorted halves
void merge(Job jobs[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Job L[n1], R[n2];

    // Copy data to temp arrays
    for (int i = 0; i < n1; i++)
        L[i] = jobs[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = jobs[mid + 1 + i];

    // Merge the two sorted halves (Descending order by profit)
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].profit >= R[j].profit) {
            jobs[k++] = L[i++];
        } else {
            jobs[k++] = R[j++];
        }
    }

    // Copy remaining elements
    while (i < n1) jobs[k++] = L[i++];
    while (j < n2) jobs[k++] = R[j++];
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
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (jobs[i].deadline > max) {
            max = jobs[i].deadline;
        }
    }
    return max;
}

// Function to schedule jobs for maximum profit
void jobScheduling(Job jobs[], int n) {
    // Step 1: Sort jobs by profit using Merge Sort
    mergeSort(jobs, 0, n - 1);

    // Step 2: Find the maximum deadline
    int maxDeadline = findMaxDeadline(jobs, n);

    // Step 3: Create an array to store scheduled jobs
    Job schedule[maxDeadline];  // Slots up to max deadline
    int slot[maxDeadline];      // Slot availability tracker
    for (int i = 0; i < maxDeadline; i++) {
        slot[i] = 0; // Initialize all slots as free
    }

    int totalProfit = 0; // Variable to store total profit

    // Step 4: Assign jobs to slots
    for (int i = 0; i < n; i++) {
        for (int j = jobs[i].deadline - 1; j >= 0; j--) { // Slot index is (deadline - 1)
            if (slot[j] == 0) {  // If slot is available
                slot[j] = 1;
                schedule[j] = jobs[i];
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    // Step 5: Display scheduled jobs and total profit
    printf("Scheduled Jobs:\n");
    for (int i = 0; i < maxDeadline; i++) {
        if (slot[i] == 1) {
            printf("Slot %d -> %s (Profit: %d)\n", i + 1, schedule[i].car, schedule[i].profit);
        }
    }
    printf("Total Maximum Profit: %d\n", totalProfit);
}

// Main function
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

    return 0;
}


---

Key Fixes and Updates

1. Corrected Slot Allocation

Previously, maxDeadline + 1 slots were allocated unnecessarily. Now, only maxDeadline slots are used.



2. Corrected Slot Indexing

Instead of using slot[j], we now use slot[j-1] (zero-based index).



3. Improved Merge Sort Implementation

Sorting ensures the highest profit jobs are scheduled first.





---

Expected Output:

Scheduled Jobs:
Slot 1 -> TATA Nexon (Profit: 700)
Slot 2 -> Maruti Grand Vitara (Profit: 1100)
Slot 3 -> Toyota Innova (Profit: 1200)
Slot 4 -> Renault Kiger (Profit: 750)
Slot 5 -> Maruti WagonR (Profit: 500)
Total Maximum Profit: 4250


---

Time Complexity:

Merge Sort: 

Job Scheduling:  (worst case)

Overall Complexity:  for small n.


Would you like me to optimize the scheduling further?