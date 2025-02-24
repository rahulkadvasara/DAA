// A thief enters a house for robbing it. He can carry a maximal weight of 60 kg into his bag.
// There are 5 items in the house with the following weights and values (LOOK AT THE PICTURE ATTACHED FOR THE DETAILS).
// What items should thief take if he can even take the fraction of any item with him?



#include <stdio.h>

typedef struct {
    int weight;
    int value;
    double ratio;
    int index;
} Item;

void merge(Item items[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Item L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = items[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = items[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i].ratio >= R[j].ratio) {
            items[k] = L[i];
            i++;
        } else {
            items[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        items[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        items[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(Item items[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(items, left, mid);
        mergeSort(items, mid + 1, right);
        merge(items, left, mid, right);
    }
}

double fractionalKnapsack(Item items[], int n, int capacity) {
    mergeSort(items, 0, n - 1);

    double totalValue = 0.0;
    int currentWeight = 0;

    for (int i = 0; i < n; i++) {
        if (currentWeight + items[i].weight <= capacity) {
            currentWeight += items[i].weight;
            totalValue += items[i].value;
            printf("Taking full item %d (Weight: %d, Value: %d)\n", items[i].index, items[i].weight, items[i].value);
        } else {
            int remainingWeight = capacity - currentWeight;
            double fraction = (double)remainingWeight / items[i].weight;
            totalValue += items[i].value * fraction;
            printf("Taking %.2f%% of item %d (Weight: %d, Value: %d)\n", fraction * 100, items[i].index, items[i].weight, items[i].value);
            break;
        }
    }

    return totalValue;
}

int main() {
    Item items[] = {
        {5, 30, 0, 1},
        {10, 40, 0, 2},
        {15, 45, 0, 3},
        {22, 77, 0, 4},
        {25, 90, 0, 5}
    };

    int n = sizeof(items) / sizeof(items[0]);
    int capacity = 60;

    for (int i = 0; i < n; i++) {
        items[i].ratio = (double)items[i].value / items[i].weight;
    }

    double maxValue = fractionalKnapsack(items, n, capacity);
    printf("Maximum Value in Knapsack = %.2f\n", maxValue);

    return 0;
}
