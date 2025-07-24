// Importa as bibliotecas necessárias
#include "scenarioIII.h"
// Importa as funções de hashing
#include "hash_table.h"
// Importa as funções auxiliares
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define os nomes dos arquivos de saída
#define OUTPUT_FILE_CHAINING "scenarioIII_results_chaining.txt"
#define OUTPUT_FILE_LINEAR "scenarioIII_results_linear.txt"
#define OUTPUT_CSV_CHAINING "running_scenarioIII_chaining.csv"
#define OUTPUT_CSV_LINEAR "running_scenarioIII_linear.csv"
// Define o tamanho máximo dos ratings que podem ser carregados na memória
#define MAX_QUANTITY_EXECUTIONS 3

// Função para executar o cenário III
// Recebe os ratings e o número de ratings
// Verifica se há ratings para processar
// Se não houver ratings, imprime uma mensagem e retorna
void runScenarioIII(const MoveRating *ratings, int numRatings)
{
    // Verifica se há ratings para processar
    if (numRatings <= 0)
    {
        printf("No ratings data to process for Scenario III.\n");
        return;
    }

    // Define os tamanhos de teste para o cenário III
    // Estes tamanhos são usados para testar a eficiência dos algoritmos de hashing
    // A lista de tamanhos inclui 1000, 5000, 10000, 50000, 100000, 500000 e 1000000
    int testSizes[] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    int numTestSizes = sizeof(testSizes) / sizeof(testSizes[0]);
    int seeds[] = {123, 456, 789};

    // Abre os arquivos de log para escrita para armazenar os dados do hashing encadeado
    FILE *logFileChaining = fopen(OUTPUT_FILE_CHAINING, "w");
    if (logFileChaining == NULL)
    {
        perror("Error opening log file for writing");
        return;
    }

    // Abre os arquivos de log para escrita para armazenar os dados do hashing linear
    FILE *logFileLinear = fopen(OUTPUT_FILE_LINEAR, "w");
    if (logFileLinear == NULL)
    {
        perror("Error opening log file for writing");
        fclose(logFileChaining);
        return;
    }

    // Cria arquivos CSV para armazenar os resultados das execuções do hashing encadeado
    FILE *csvFileChaining = fopen(OUTPUT_CSV_CHAINING, "w");
    if (csvFileChaining == NULL)
    {
        perror("Error opening CSV file for chaining");
        fclose(logFileChaining);
        fclose(logFileLinear);
        fclose(csvFileChaining);
        return;
    }

    // Cria arquivos CSV para armazenar os resultados das execuções do hashing linear
    FILE *csvFileLinear = fopen(OUTPUT_CSV_LINEAR, "w");
    if (csvFileLinear == NULL)
    {
        perror("Error opening CSV file for linear probing");
        fclose(logFileChaining);
        fclose(logFileLinear);
        fclose(csvFileChaining);
        fclose(csvFileLinear);
        return;
    }

    // Itera sobre os tamanhos de teste definidos, para cada tamanho de teste
    // Para cada tamanho de teste, verifica se há dados suficientes
    // Caso não haja dados suficientes, pula para o próximo tamanho
    // Para cada tamanho de teste, executa o hashing encadeado e o hashing linear
    // Armazena os resultados de comparação e uso de memória em arquivos CSV
    // Imprime os resultados médios de comparação e uso de memória no log
    for (int i = 0; i < numTestSizes; i++)
    {
        // Define o tamanho atual do teste
        // Verifica se o tamanho atual é maior que o número de ratings disponíveis
        // Se for, imprime uma mensagem e pula para o próximo tamanho
        int currentSize = testSizes[i];
        if (currentSize > numRatings)
        {
            fprintf(logFileChaining, "\nSkipping size %d: not enough data available (have %d).\n", currentSize, numRatings);
            continue;
        }

        // Inicializa as variáveis de comparação e uso de memória para o hashing encadeado e linear
        long long totalComparisonsChaining = 0;
        long totalMemoryChaining = 0;
        long long totalComparisonsLinear = 0;
        long totalMemoryLinear = 0;

        // Imprime no log o tamanho atual do teste
        fprintf(logFileLinear, "\n--- Scenario III: Hashing with N = %d ---\n", currentSize);
        fprintf(logFileChaining, "\n--- Scenario III: Hashing with N = %d ---\n", currentSize);
        

        // Executa o hashing encadeado e o hashing linear para cada semente definida, no caso 3 vezes
        for (int j = 0; j < MAX_QUANTITY_EXECUTIONS; j++)
        {
            // Define a semente para a geração de números aleatórios
            srand(seeds[j]);
            // Cria um subconjunto aleatório dos ratings para o tamanho atual do teste
            MoveRating *subset = createRandomSubset(ratings, numRatings, currentSize);

            // Executa o hashing encadeado e o hashing linear
            // Armazena os resultados de comparação e uso de memória em arquivos CSV
            HashTableChaining *htc = createHashTableChaining(currentSize);
            for (int k = 0; k < currentSize; k++)
            {
                insertChaining(htc, subset[k]);
            }
            long long comparisonsChaining = getComparisonsChaining(htc);
            long memoryChaining = getMemoryUsageChaining(htc);
            totalComparisonsChaining += comparisonsChaining;
            totalMemoryChaining += memoryChaining;
            fprintf(csvFileChaining, "%d,%d,%lld,%ld\n", currentSize, seeds[j], comparisonsChaining, memoryChaining);

            // Libera a memória alocada para o hashing encadeado
            // Armazena os resultados de comparação e uso de memória em arquivos CSV
            HashTableLinear *htl = createHashTableLinear(currentSize);
            for (int k = 0; k < currentSize; k++)
            {
                insertLinearProbing(htl, subset[k]);
            }
            long long comparisonsLinear = getComparisonsLinear(htl);
            long memoryLinear = getMemoryUsageLinear(htl);
            totalComparisonsLinear += comparisonsLinear;
            totalMemoryLinear += memoryLinear;
            fprintf(csvFileLinear, "%d,%d,%lld,%ld\n", currentSize, seeds[j], comparisonsLinear, memoryLinear);

            // Libera a memória alocada para o hashing encadeado
            freeHashTableChaining(htc);
            // Libera a memória alocada para o hashing linear
            freeHashTableLinear(htl);
            // Libera a memória alocada para o subconjunto
            free(subset);
        }

        // Imprime os resultados médios de comparação e uso de memória no log
        // Calcula a média de comparações e uso de memória para o hashing encadeado
        // Calcula a média de comparações e uso de memória para o hashing linear
        fprintf(logFileChaining, "Chaining - Avg Comparisons: %lld, Avg Memory: %ld\n", totalComparisonsChaining / MAX_QUANTITY_EXECUTIONS, totalMemoryChaining / MAX_QUANTITY_EXECUTIONS);
        fprintf(logFileLinear, "Linear Probing - Avg Comparisons: %lld, Avg Memory: %ld\n", totalComparisonsLinear / MAX_QUANTITY_EXECUTIONS, totalMemoryLinear / MAX_QUANTITY_EXECUTIONS);
    }

    // Fecha o arquivo CSV e log após todas as execuções
    fclose(logFileChaining);
    fclose(logFileLinear);
    fclose(csvFileChaining);
    fclose(csvFileLinear);
    printf("\nScenario III completed successfully. Results saved to %s, %s\n", OUTPUT_FILE_CHAINING, OUTPUT_FILE_LINEAR);
}
