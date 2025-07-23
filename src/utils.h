#ifndef UTILS_H
#define UTILS_H

#include "data_handler.h"

void runAndLogSort(MoveRating *data, int size, const char *metricName, FILE *logFile, FILE *csvFile, int count, int scenario);
MoveRating *createRandomSubset(const MoveRating *allRatings, int totalRatings, int subsetSize);

#endif