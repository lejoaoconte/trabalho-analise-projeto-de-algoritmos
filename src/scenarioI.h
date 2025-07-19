#ifndef SCENARIOI_H
#define SCENARIOI_H

#include "data_handler.h"

/**
 * @brief Runs Scenario I: sorts different fields from the dataset and logs performance.
 *
 * This function takes a random subset of the imported ratings for various sizes,
 * sorts them by different fields (userId, moveId, etc.), and records the time,

 * comparisons, and copies for each sort into a file.
 *
 * @param ratings A constant pointer to the array of MoveRating data.
 * @param numRatings The total number of ratings available in the array.
 */
void runScenarioI(const MoveRating *ratings, int numRatings);

#endif // SCENARIOI_H