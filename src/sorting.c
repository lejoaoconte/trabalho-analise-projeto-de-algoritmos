#include "sorting.h"
#include <stdlib.h>
#include <stdio.h>

static void merge(MoveRating arr[], int left, int mid, int right, long long *comparisons, long long *copies)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    MoveRating *L = (MoveRating *)malloc(n1 * sizeof(MoveRating));
    MoveRating *R = (MoveRating *)malloc(n2 * sizeof(MoveRating));
    if (!L || !R)
    {
        fprintf(stderr, "Failed to allocate memory in merge.\n");
        free(L);
        free(R);
        return;
    }

    for (i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
        (*copies)++;
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = arr[mid + 1 + j];
        (*copies)++;
    }

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        (*comparisons)++;
        if (L[i].moveId <= R[j].userId)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        (*copies)++;
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        (*copies)++;
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        (*copies)++;
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(MoveRating arr[], int left, int right, long long *comparisons, long long *copies)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid, comparisons, copies);
        mergeSort(arr, mid + 1, right, comparisons, copies);
        merge(arr, left, mid, right, comparisons, copies);
    }
}

void insertionSort(MoveRating arr[], int n, long long *comparisons, long long *copies)
{
    for (int i = 1; i < n; i++)
    {
        MoveRating key = arr[i];
        int j = i - 1;

        (*comparisons)++;
        while (j >= 0 && arr[j].userId > key.userId)
        {
            (*comparisons)++;
            arr[j + 1] = arr[j];
            (*copies)++;
            j--;
        }
        arr[j + 1] = key;
        (*copies)++;
    }
}


void specialMergeSort(MoveRating arr[], int left, int right, long long *comparisons, long long *copies)
{
    if (right - left <= 100)
    {
        insertionSort(arr + left, right - left + 1, comparisons, copies);
        return;
    }

    if (left < right)
    {
        int mid = left + (right - left) / 2;

        specialMergeSort(arr, left, mid, comparisons, copies);
        specialMergeSort(arr, mid + 1, right, comparisons, copies);
        merge(arr, left, mid, right, comparisons, copies);
    }
}