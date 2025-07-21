#include "scenarioI.h"
#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OUTPUT_FILE "scenarioII_results.txt"
#define MAX_RATINGS_IN_MEMORY 26024288
#define MAX_QUANTITY_EXECUTIONS 5

static void runAndLogSort(int *data, int size, const char *metricName, FILE *logFile);
static int *createRandomSubset(const MoveRating *allRatings, int totalRatings, int subsetSize, int fieldSelector);

void runScenarioII(const MoveRating *ratings, int numRatings)
{
    if (numRatings <= 0)
    {
        printf("No ratings data to process for Scenario II.\n");
        return;
    }

    int testSizes[] = {1000, 5000, 10000, 50000, 100000};
    int numTestSizes = sizeof(testSizes) / sizeof(testSizes[0]);

    srand(time(NULL));

    FILE *logFile = fopen(OUTPUT_FILE, "w");
    if (logFile == NULL)
    {
        perror("Error opening log file for writing");
        return;
    }

    for (int count = 0; count < MAX_QUANTITY_EXECUTIONS; count++)
    {
        fprintf(logFile, "\n--- Execution %d of Scenario II ---\n", count + 1);
        for (int i = 0; i < numTestSizes; i++)
        {
            int currentSize = testSizes[i];
            if (currentSize > numRatings)
            {
                fprintf(logFile, "\nSkipping size %d: not enough data available (have %d).\n", currentSize, numRatings);
                continue;
            }

            fprintf(logFile, "\n--- Scenario II: Sorting with %d ratings ---\n", currentSize);

            int *userIds = createRandomSubset(ratings, numRatings, currentSize, 0);
            int *moveIds = createRandomSubset(ratings, numRatings, currentSize, 1);
            int *timestamps = createRandomSubset(ratings, numRatings, currentSize, 2);
            int *ratingValues = createRandomSubset(ratings, numRatings, currentSize, 3);

            runAndLogSort(userIds, currentSize, "UserId", logFile);
            runAndLogSort(moveIds, currentSize, "MoveId", logFile);
            runAndLogSort(timestamps, currentSize, "Timestamp", logFile);
            runAndLogSort(ratingValues, currentSize, "Rating", logFile);

            free(userIds);
            free(moveIds);
            free(timestamps);
            free(ratingValues);
        }
    }

    fclose(logFile);
    printf("\nScenario II completed successfully. Results saved to %s\n", OUTPUT_FILE);
}

static int *createRandomSubset(const MoveRating *allRatings, int totalRatings, int subsetSize, int fieldSelector)
{
    int *subset = malloc(subsetSize * sizeof(int));
    if (subset == NULL)
    {
        fprintf(stderr, "Memory allocation failed for subset array.\n");
        return NULL;
    }

    for (int i = 0; i < subsetSize; i++)
    {
        int randomIndex = rand() % totalRatings;
        switch (fieldSelector)
        {
        case 0:
            subset[i] = allRatings[randomIndex].userId;
            break;
        case 1:
            subset[i] = allRatings[randomIndex].moveId;
            break;
        case 2:
            subset[i] = allRatings[randomIndex].timestamp;
            break;
        case 3:
            subset[i] = (int)allRatings[randomIndex].rating;
            break;
        }
    }
    return subset;
}

static void runAndLogSort(int *data, int size, const char *metricName, FILE *logFile)
{
    if (data == NULL)
        return;

    long long comparisons = 0, copies = 0;

    clock_t start = clock();
    mergeSort(data, 0, size - 1, &comparisons, &copies);
    clock_t end = clock();

    double timeSpent = ((double)(end - start)) / CLOCKS_PER_SEC;

    fprintf(logFile, "\n--- Metrics from %s ---\n", metricName);
    fprintf(logFile, "Key Comparisons: %lld\n", comparisons);
    fprintf(logFile, "Register Copies: %lld\n", copies);
    fprintf(logFile, "Total Time Spent: %.6f seconds\n", timeSpent);
}