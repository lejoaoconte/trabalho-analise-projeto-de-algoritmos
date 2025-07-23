#ifndef SORTING_H
#define SORTING_H

#include "data_handler.h"

void mergeSort(MoveRating arr[], int left, int right, long long *comparisons, long long *copies);
void specialMergeSort(MoveRating arr[], int left, int right, long long *comparisons, long long *copies);

#endif