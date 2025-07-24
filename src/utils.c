#include "sorting.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função auxiliar para executar e registrar a ordenação
// Recebe o array de MoveRating, o tamanho, o nome da métrica, os arquivos de log e CSV, o contador de execução e o cenário
void runAndLogSort(MoveRating *data, int size, const char *metricName, FILE *logFile, FILE *csvFile, int count, int scenario)
{
    // Verifica se o array de dados é nulo
    if (data == NULL)
        return;

    // Inicializa as variáveis de comparação e cópia
    long long comparisons = 0, copies = 0;

    // Marca o tempo de início da ordenação
    clock_t start = clock();
    // Executa a ordenação de acordo com o cenário
    // Se for cenário 1, usa mergeSort, se for cenário 2, usa specialMergeSort
    // specialMergeSort é o merge sort com o insertion sort para pequenos arrays
    if (scenario == 1)
        mergeSort(data, 0, size - 1, &comparisons, &copies);
    else if (scenario == 2)
        specialMergeSort(data, 0, size - 1, &comparisons, &copies);
    clock_t end = clock();

    // Calcula o tempo gasto na ordenação
    // O tempo é calculado como a diferença entre o tempo de fim e o tempo de início, dividido pelo CLOCKS_PER_SEC
    // Isso converte o tempo de clock ticks para segundos
    // O resultado é armazenado na variável timeSpent
    double timeSpent = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Registra as métricas no arquivo de log
    fprintf(logFile, "\n--- Metrics from %s ---\n", metricName);
    fprintf(logFile, "Key Comparisons: %lld\n", comparisons);
    fprintf(logFile, "Register Copies: %lld\n", copies);
    fprintf(logFile, "Total Time Spent: %.6f seconds\n", timeSpent);

    // Registra as métricas no arquivo CSV
    fprintf(csvFile, "%d,%d,%s,%lld,%lld,%.6f\n", count + 1, size, metricName, comparisons, copies, timeSpent);
}

// Função auxiliar para criar um subconjunto aleatório de MoveRating
// Recebe o array completo de ratings, o total de ratings e o tamanho do subconjunto
// Retorna um novo array contendo o subconjunto aleatório
MoveRating *createRandomSubset(const MoveRating *allRatings, int totalRatings, int subsetSize)
{
    // Aloca memória para o subconjunto
    MoveRating *subset = malloc(subsetSize * sizeof(MoveRating));
    // Verifica se a alocação foi bem-sucedida
    if (subset == NULL)
    {
        fprintf(stderr, "Memory allocation failed for subset array.\n");
        return NULL;
    }

    // Preenche o subconjunto com elementos aleatórios do array original
    for (int i = 0; i < subsetSize; i++)
    {
        int randomIndex = rand() % totalRatings;
        subset[i] = allRatings[randomIndex];
    }
    // Retorna o subconjunto aleatório
    return subset;
}