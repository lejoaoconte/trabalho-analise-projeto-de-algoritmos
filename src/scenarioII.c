// Importa as bibliotecas necessárias
#include "scenarioII.h"
// Importa as funções auxiliares
#include "utils.h"
// Importa as funções de ordenação
#include "sorting.h"
// Demais includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define os nomes dos arquivos de saída
#define OUTPUT_FILE "scenarioII_results.txt"
#define OUTPUT_CSV_FILE "running_scenarioII.csv"
// Define o tamanho máximo dos ratings que podem ser carregados na memória
#define MAX_RATINGS_IN_MEMORY 26024288
// Define a quantidade máxima de execuções para o cenário II
#define MAX_QUANTITY_EXECUTIONS 5

// Função para executar o cenário II
// Recebe os ratings e o número de ratings
// Verifica se há ratings para processar
// Se não houver ratings, imprime uma mensagem e retorna
void runScenarioII(const MoveRating *ratings, int numRatings)
{
    // Verifica se há ratings para processar
    if (numRatings <= 0)
    {
        printf("No ratings data to process for Scenario II.\n");
        return;
    }

    // Define os tamanhos de teste para o cenário II
    int testSizes[] = {1000, 5000, 10000, 50000, 100000};
    int numTestSizes = sizeof(testSizes) / sizeof(testSizes[0]);

    srand(time(NULL));

    // Abre o arquivo de log para escrita, este arquivo armazenará os resultados das execuções e é um .txt
    FILE *logFile = fopen(OUTPUT_FILE, "w");
    if (logFile == NULL)
    {
        perror("Error opening log file for writing");
        return;
    }
    // Cria um arquivo CSV para cada execução, este arquivo armazenará os resultados das execuções e é um .csv
    FILE *csvFile = fopen(OUTPUT_CSV_FILE, "w");
    if (csvFile == NULL)
    {
        perror("Error opening CSV file for writing");
        fclose(logFile);
        return;
    }

    // Itera sobre os tamanhos de teste definidos, para cada tamanho de teste
    for (int i = 0; i < numTestSizes; i++)
    {
        // Imprime no log o número da execução atual
        fprintf(logFile, "\n--- Execution %d of Scenario II ---\n", i + 1);
        // Executa o cenário II para a quantidade máxima de execuções, faz as 5 execuções definidas
        for (int count = 0; count < MAX_QUANTITY_EXECUTIONS; count++)
        {
            // Para cada tamanho de teste, verifica se há dados suficientes
            // Caso não haja dados suficientes, pula para o próximo tamanho
            int currentSize = testSizes[i];
            if (currentSize > numRatings)
            {
                fprintf(logFile, "\nSkipping size %d: not enough data available (have %d).\n", currentSize, numRatings);
                continue;
            }

            // Imprime no log o tamanho atual do teste
            fprintf(logFile, "\n--- Scenario II: Sorting with %d ratings ---\n", currentSize);

            // Cria um subconjunto aleatório dos ratings para o tamanho atual do teste
            MoveRating *subset = createRandomSubset(ratings, numRatings, currentSize);

            // Executa a ordenação e registra as métricas
            runAndLogSort(subset, currentSize, "userId", logFile, csvFile, count, 1);

            // Libera a memória alocada para o subconjunto
            free(subset);
        }
    }

    // Fecha o arquivo CSV após todas as execuções
    fclose(csvFile);
    // Fecha o arquivo de log após todas as execuções
    fclose(logFile);
    printf("\nScenario II completed successfully. Results saved to %s\n", OUTPUT_FILE);
}
