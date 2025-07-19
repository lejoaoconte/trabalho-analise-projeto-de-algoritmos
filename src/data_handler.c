#include "data_handler.h"
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int importData(MoveRating **ratings, int *capacity, const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    int count = 0;

    // Skip the header line
    if (fgets(line, sizeof(line), fp) == NULL)
    {
        fclose(fp);
        return 0; // File is empty or contains only a header
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // Grow the array if it's full
        if (count == *capacity)
        {
            *capacity *= 2;
            MoveRating *temp = realloc(*ratings, *capacity * sizeof(MoveRating));
            if (temp == NULL)
            {
                fprintf(stderr, "Memory reallocation failed\n");
                fclose(fp);
                return count; // Return what was successfully read
            }
            *ratings = temp;
        }

        // Parse the CSV line
        if (sscanf(line, "%d,%d,%f,%d",
                   &(*ratings)[count].userId,
                   &(*ratings)[count].moveId,
                   &(*ratings)[count].rating,
                   &(*ratings)[count].timestamp) == 4)
        {
            count++;
        }
        else
        {
            fprintf(stderr, "Warning: Error parsing line, skipping: %s", line);
        }
    }

    fclose(fp);
    return count;
}

void showData(const MoveRating *ratings, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("User ID: %d, Move ID: %d, Rating: %.1f, Timestamp: %d\n",
               ratings[i].userId,
               ratings[i].moveId,
               ratings[i].rating,
               ratings[i].timestamp);
    }
}