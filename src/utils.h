#ifndef UTILS_H
#define UTILS_H

// Importa o data_handler.h para usar a estrutura MoveRating
#include "data_handler.h"

// Declara as funções auxiliares
void runAndLogSort(MoveRating *data, int size, const char *metricName, FILE *logFile, FILE *csvFile, int count, int scenario);
MoveRating *createRandomSubset(const MoveRating *allRatings, int totalRatings, int subsetSize);

#endif