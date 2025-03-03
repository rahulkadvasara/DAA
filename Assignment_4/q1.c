// 1. The students have to take an unsorted integer array of size at least 300 elements. They have to write a program in such a way
// that the user will be able to choose between any of existing sorting techniques to sort the given array (at least you have to provide 3 options - Merge sort, quick sort, bubble sort). From that sorted array the student has to ask the user for an integer number which the user wants to search. The program should be able to search the particular number and if the number is present then the index value of the number is to be returned. Finally calculate the time complexity of the entire program.

#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
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

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int binarySearch(int arr[], int l, int r, int x) {
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x)
            return mid;
        if (arr[mid] < x)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return -1;
}

int main() {
    int arr[300];
    for (int i = 0; i < 300; i++) {
        arr[i] = rand() % 1000 + 1;
    }

    int choice;
    

    printf("Choose sorting algorithm:\n");
    printf("1. Merge Sort\n2. Quick Sort\n3. Bubble Sort\n");
    printf("Enter choice (1/2/3):\n");
    scanf("%d", &choice);
    switch(choice){
        case 1: mergeSort(arr, 0, 299);
            break;
        case 2: quickSort(arr, 0, 299);
            break;
        case 3: bubbleSort(arr, 300);
            break;
        default: printf("Invalid choice!!");
    }
    printf("Sorted Array:\n");
    for (int i = 0; i < 300; i++) {
        printf("%d ", arr[i]);
    }

    int target;
    printf("\n\nEnter number to search:\n");
    scanf("%d", &target);
    int index = binarySearch(arr, 0, 299, target);

    if (index != -1) {
        printf("\nNumber found at index %d\n", index);
    } else {
        printf("\nNumber not found\n");
    }

    return 0;
}
