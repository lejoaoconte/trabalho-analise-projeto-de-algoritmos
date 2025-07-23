#include "sorting.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void runAndLogSort(MoveRating *data, int size, const char *metricName, FILE *logFile, FILE *csvFile, int count, int scenario)
{
    if (data == NULL)
        return;

    long long comparisons = 0, copies = 0;

    clock_t start = clock();
    if (scenario == 1)
        mergeSort(data, 0, size - 1, &comparisons, &copies);
    else if (scenario == 2)
        specialMergeSort(data, 0, size - 1, &comparisons, &copies);
    clock_t end = clock();

    double timeSpent = ((double)(end - start)) / CLOCKS_PER_SEC;

    fprintf(logFile, "\n--- Metrics from %s ---\n", metricName);
    fprintf(logFile, "Key Comparisons: %lld\n", comparisons);
    fprintf(logFile, "Register Copies: %lld\n", copies);
    fprintf(logFile, "Total Time Spent: %.6f seconds\n", timeSpent);

    fprintf(csvFile, "%d,%d,%s,%lld,%lld,%.6f\n", count + 1, size, metricName, comparisons, copies, timeSpent);
}

MoveRating *createRandomSubset(const MoveRating *allRatings, int totalRatings, int subsetSize)
{
    MoveRating *subset = malloc(subsetSize * sizeof(MoveRating));
    if (subset == NULL)
    {
        fprintf(stderr, "Memory allocation failed for subset array.\n");
        return NULL;
    }

    for (int i = 0; i < subsetSize; i++)
    {
        int randomIndex = rand() % totalRatings;
        subset[i] = allRatings[randomIndex];
    }
    return subset;
}