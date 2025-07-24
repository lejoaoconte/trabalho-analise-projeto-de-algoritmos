#ifndef SORTING_H
#define SORTING_H

// Importa o data_handler.h para usar a estrutura MoveRating
#include "data_handler.h"

// Declara as funções de ordenação
void mergeSort(MoveRating arr[], int left, int right, long long *comparisons, long long *copies);
void specialMergeSort(MoveRating arr[], int left, int right, long long *comparisons, long long *copies);

#endif