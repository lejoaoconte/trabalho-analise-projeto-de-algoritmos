#include "scenarioI.h"
#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- Constants ---
#define OUTPUT_FILE "scenarioI_results.txt"
#define MAX_RATINGS_IN_MEMORY 26024288 // From original code

// --- Static Helper Function Prototypes ---
static void runAndLogSort(int *data, int size, const char *metricName, FILE *logFile);
static int *createRandomSubset(const MoveRating *allRatings, int totalRatings, int subsetSize, int fieldSelector);

// --- Public Function Implementation ---

void runScenarioI(const MoveRating *ratings, int numRatings)
{
    if (numRatings <= 0)
    {
        printf("No ratings data to process for Scenario I.\n");
        return;
    }

    // Test sizes for the scenario
    int testSizes[] = {1000, 5000, 10000, 50000, 100000};
    int numTestSizes = sizeof(testSizes) / sizeof(testSizes[0]);

    // Seed the random number generator
    srand(time(NULL));

    // Open the log file once in write mode to clear it
    FILE *logFile = fopen(OUTPUT_FILE, "w");
    if (logFile == NULL)
    {
        perror("Error opening log file for writing");
        return;
    }

    for (int i = 0; i < numTestSizes; i++)
    {
        int currentSize = testSizes[i];
        if (currentSize > numRatings)
        {
            printf("\nSkipping size %d: not enough data available (have %d).\n", currentSize, numRatings);
            continue;
        }

        printf("\n--- Scenario I: Sorting with %d ratings ---\n", currentSize);
        fprintf(logFile, "\n--- Scenario I: Sorting with %d ratings ---\n", currentSize);

        // 0: userId, 1: moveId, 2: timestamp, 3: rating
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

    fclose(logFile);
    printf("\nScenario I completed successfully. Results saved to %s\n", OUTPUT_FILE);
}

// --- Static Helper Function Implementations ---

/**
 * Creates an array of integers by selecting a specific field from a random subset of ratings.
 * fieldSelector: 0=userId, 1=moveId, 2=timestamp, 3=rating
 */
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
            break; // Note: Casting float to int
        }
    }
    return subset;
}

/**
 * Sorts an array, measures performance, and logs the results to console and file.
 */
static void runAndLogSort(int *data, int size, const char *metricName, FILE *logFile)
{
    if (data == NULL)
        return;

    long long comparisons = 0, copies = 0;

    clock_t start = clock();
    mergeSort(data, 0, size - 1, &comparisons, &copies);
    clock_t end = clock();

    double timeSpent = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Print to console
    printf("\n--- Metrics from %s ---\n", metricName);
    printf("Key Comparisons: %lld\n", comparisons);
    printf("Register Copies: %lld\n", copies);
    printf("Total Time Spent: %.6f seconds\n", timeSpent);

    // Print to file
    fprintf(logFile, "\n--- Metrics from %s ---\n", metricName);
    fprintf(logFile, "Key Comparisons: %lld\n", comparisons);
    fprintf(logFile, "Register Copies: %lld\n", copies);
    fprintf(logFile, "Total Time Spent: %.6f seconds\n", timeSpent);
}