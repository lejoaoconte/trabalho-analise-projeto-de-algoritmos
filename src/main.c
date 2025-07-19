#include <stdio.h>
#include <stdlib.h>
#include "data_handler.h"
#include "scenarioI.h"

#define INITIAL_CAPACITY 1000

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <filename.csv>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int capacity = INITIAL_CAPACITY;
    MoveRating *ratings = malloc(capacity * sizeof(MoveRating));

    if (ratings == NULL)
    {
        fprintf(stderr, "Initial memory allocation failed\n");
        return 1;
    }

    printf("Importing data from %s...\n", filename);
    int numRatings = importData(&ratings, &capacity, filename);

    if (numRatings > 0)
    {
        printf("Successfully imported %d ratings.\n", numRatings);

        runScenarioI(ratings, numRatings);
    }
    else if (numRatings == 0)
    {
        printf("No data was imported from the file.\n");
    }
    else
    {
        fprintf(stderr, "An error occurred during file import.\n");
    }

    free(ratings);
    printf("Program finished.\n");

    return 0;
}