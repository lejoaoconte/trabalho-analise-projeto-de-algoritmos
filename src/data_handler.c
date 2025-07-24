#include "data_handler.h"
#include <stdlib.h>
#include <string.h>

// Define o tamanho máximo da linha para leitura do arquivo
#define MAX_LINE_LENGTH 1024

// Função para importar dados de um arquivo CSV
// Retorna o número de ratings importados ou -1 em caso de erro
int importData(MoveRating **ratings, int *capacity, const char *filename)
{
    // Abre o arquivo CSV para leitura e verifica se foi aberto corretamente
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    int count = 0;

    // Lê a primeira linha do arquivo (cabeçalho) e ignora
    // Se a primeira linha não puder ser lida, retorna 0 ratings importados
    if (fgets(line, sizeof(line), fp) == NULL)
    {
        fclose(fp);
        return 0;
    }

    // Lê o arquivo linha por linha
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if (count == *capacity)
        {
            // Se o número de ratings atingir a capacidade, dobra a capacidade
            *capacity *= 2;
            MoveRating *temp = realloc(*ratings, *capacity * sizeof(MoveRating));
            // Se a realocação falhar, libera a memória e retorna o número de ratings importados
            if (temp == NULL)
            {
                fprintf(stderr, "Memory reallocation failed\n");
                fclose(fp);
                return count;
            }
            // Atualiza o ponteiro para os ratings
            *ratings = temp;
        }

        // Lê os dados da linha e armazena no array de ratings
        // Se a leitura falhar, imprime um aviso e continua para a próxima linha
        // Espera que a linha tenha o formato: userId,moveId,rating,timestamp
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

// Função para exibir os dados dos ratings (não utilizada no código principal, mas pode ser útil para depuração)
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