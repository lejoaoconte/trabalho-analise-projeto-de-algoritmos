#include "sorting.h"
#include <stdlib.h>
#include <stdio.h> // <-- Add this line to fix the error

// Helper function for mergeSort, confined to this file.
static void merge(int arr[], int left, int mid, int right, long long *comparisons, long long *copies) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    if (!L || !R) {
        fprintf(stderr, "Failed to allocate memory in merge.\n");
        free(L);
        free(R);
        return;
    }

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++) {
        L[i] = arr[left + i];
        (*copies)++;
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
        (*copies)++;
    }

    // Merge the temporary arrays back into arr[left..right]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        (*comparisons)++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        (*copies)++;
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        (*copies)++;
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        (*copies)++;
        j++;
        k++;
    }
    
    free(L);
    free(R);
}

void mergeSort(int arr[], int left, int right, long long *comparisons, long long *copies) {
    if (left < right) {
        // Same as (left+right)/2, but avoids overflow for large left and right
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid, comparisons, copies);
        mergeSort(arr, mid + 1, right, comparisons, copies);

        // Merge the sorted halves
        merge(arr, left, mid, right, comparisons, copies);
    }
}