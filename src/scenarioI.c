#include "scenarioI.h"
#include "utils.h"
#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OUTPUT_FILE "scenarioI_results.txt"
#define OUTPUT_CSV_FILE "running_scenarioI"
#define MAX_RATINGS_IN_MEMORY 26024288
#define MAX_QUANTITY_EXECUTIONS 5

void runScenarioI(const MoveRating *ratings, int numRatings)
{
    if (numRatings <= 0)
    {
        printf("No ratings data to process for Scenario I.\n");
        return;
    }

    int testSizes[] = {1000, 5000, 10000, 50000, 100000};
    int numTestSizes = sizeof(testSizes) / sizeof(testSizes[0]);

    srand(time(NULL));

    FILE *logFile = fopen(OUTPUT_FILE, "w");
    if (logFile == NULL)
    {
        perror("Error opening log or CSV file for writing");
        return;
    }

    for (int count = 0; count < MAX_QUANTITY_EXECUTIONS; count++)
    {
        char fileName[256];
        snprintf(fileName, sizeof(fileName), OUTPUT_CSV_FILE "_%d.csv", count+1);
        FILE *csvFile = fopen(fileName, "w");
        if (csvFile == NULL)
        {
            perror("Error opening CSV file for writing");
            fclose(logFile);
            return;
        }

        fprintf(logFile, "\n--- Execution %d of Scenario I ---\n", count + 1);
        for (int i = 0; i < numTestSizes; i++)
        {
            int currentSize = testSizes[i];
            if (currentSize > numRatings)
            {
                fprintf(logFile, "\nSkipping size %d: not enough data available (have %d).\n", currentSize, numRatings);
                continue;
            }

            fprintf(logFile, "\n--- Scenario I: Sorting with %d ratings ---\n", currentSize);

            MoveRating *subset = createRandomSubset(ratings, numRatings, currentSize);

            runAndLogSort(subset, currentSize, "userId", logFile, csvFile, count, 2);

            free(subset);
        }
    }

    fclose(logFile);
    printf("\nScenario I completed successfully. Results saved to %s\n", OUTPUT_FILE);
}