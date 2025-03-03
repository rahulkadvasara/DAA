// Given a sorted array and a number X, search two elements of the array such that their sum is X. Expected time complexity is O(n).

#include <stdio.h>
void findPair(int arr[], int n, int X) {
    int left = 0, right = n - 1;
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == X) {
            printf("Pair found: (%d, %d)\n", arr[left], arr[right]);
            return;
        }
        else if (sum < X) {
            left++; 
        }
        else {
            right--;
        }
    }   
    printf("No pair found\n");
}
int main() {
    int arr[] = {1, 2, 3, 4, 6, 8, 9};
    int X = 10;
    int n = sizeof(arr) / sizeof(arr[0]);
    findPair(arr, n, X);
    return 0;
}
