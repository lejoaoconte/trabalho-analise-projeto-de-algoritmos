#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include <stdio.h>

// Estruturas de dados para armazenar os ratings
typedef struct MoveRating
{
    int userId;
    int moveId;
    float rating;
    int timestamp;
} MoveRating;

// Declara as das funções para manipulação de dados
int importData(MoveRating **ratings, int *capacity, const char *filename);
void showData(const MoveRating *ratings, int count);

#endif