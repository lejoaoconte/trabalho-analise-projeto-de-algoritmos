#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "data_handler.h"
#include <stdio.h>

typedef struct Node
{
    MoveRating data;
    struct Node *next;
} Node;

typedef struct HashTableChaining
{
    Node **table;
    int size;
    long long comparisons;
} HashTableChaining;

typedef struct HashTableLinear
{
    MoveRating *table;
    int size;
    long long comparisons;
} HashTableLinear;

HashTableChaining *createHashTableChaining(int size);
void insertChaining(HashTableChaining *ht, MoveRating data);
void freeHashTableChaining(HashTableChaining *ht);
long long getComparisonsChaining(HashTableChaining *ht);
long getMemoryUsageChaining(HashTableChaining *ht);

HashTableLinear *createHashTableLinear(int size);
void insertLinearProbing(HashTableLinear *ht, MoveRating data);
void freeHashTableLinear(HashTableLinear *ht);
long long getComparisonsLinear(HashTableLinear *ht);
long getMemoryUsageLinear(HashTableLinear *ht);

#endif
