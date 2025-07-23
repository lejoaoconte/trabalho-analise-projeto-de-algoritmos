#ifndef UTILS_H
#define UTILS_H

#include "data_handler.h"

void runAndLogSort(int *data, int size, const char *metricName, FILE *logFile, FILE *csvFile, int count, int scenario);
int *createRandomSubset(const MoveRating *allRatings, int totalRatings, int subsetSize, int fieldSelector);

#endif