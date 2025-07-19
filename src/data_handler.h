#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include <stdio.h>
typedef struct MoveRating
{
    int userId;
    int moveId;
    float rating;
    int timestamp;
} MoveRating;

int importData(MoveRating **ratings, int *capacity, const char *filename);
void showData(const MoveRating *ratings, int count);

#endif // DATA_HANDLER_H