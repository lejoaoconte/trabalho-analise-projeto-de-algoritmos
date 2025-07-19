#ifndef SORTING_H
#define SORTING_H

/**
 * @brief Sorts an array of integers using the merge sort algorithm.
 *
 * @param arr The array to be sorted.
 * @param left The starting index of the array segment to be sorted.
 * @param right The ending index of the array segment to be sorted.
 * @param comparisons A pointer to a counter for the number of key comparisons.
 * @param copies A pointer to a counter for the number of element copies.
 */
void mergeSort(int arr[], int left, int right, long long *comparisons, long long *copies);

#endif // SORTING_H