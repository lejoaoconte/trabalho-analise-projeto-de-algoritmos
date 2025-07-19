#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include <stdio.h>

// Defines the structure for a single movie rating record.
typedef struct MoveRating
{
    int userId;
    int moveId;
    float rating;
    int timestamp;
} MoveRating;

/**
 * @brief Imports rating data from a CSV file into a dynamic array.
 *
 * @param ratings A pointer to the array of MoveRating structures.
 * @param capacity A pointer to the current capacity of the array.
 * @param filename The name of the file to import data from.
 * @return The number of ratings successfully imported, or -1 on error.
 */
int importData(MoveRating **ratings, int *capacity, const char *filename);

/**
 * @brief Prints a specified number of rating records to the console.
 *
 * @param ratings A constant pointer to the array of MoveRating structures.
 * @param count The number of records to print from the start of the array.
 */
void showData(const MoveRating *ratings, int count);

#endif // DATA_HANDLER_H