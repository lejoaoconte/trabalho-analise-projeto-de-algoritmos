#include "sorting.h"
#include <stdlib.h>
#include <stdio.h>

// Função auxiliar para mesclar dois subarrays
// Recebe o array, os índices esquerdo, meio e direito, e ponteiros para
// as variáveis de comparação e cópia
// Realiza a mesclagem dos subarrays e atualiza as métricas de comparação e cópia
static void merge(MoveRating arr[], int left, int mid, int right, long long *comparisons, long long *copies)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Aloca memória para os subarrays L e R
    // Verifica se a alocação foi bem-sucedida
    // Se falhar, imprime uma mensagem de erro e retorna
    MoveRating *L = (MoveRating *)malloc(n1 * sizeof(MoveRating));
    MoveRating *R = (MoveRating *)malloc(n2 * sizeof(MoveRating));
    if (!L || !R)
    {
        fprintf(stderr, "Failed to allocate memory in merge.\n");
        free(L);
        free(R);
        return;
    }

    // Preenche o subarray L
    for (i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
        (*copies)++;
    }
    // Preenche o subarray R
    for (j = 0; j < n2; j++)
    {
        R[j] = arr[mid + 1 + j];
        (*copies)++;
    }

    i = 0;
    j = 0;
    k = left;
    // Mescla os subarrays L e R de volta ao array original
    // Compara os elementos e atualiza as métricas de comparação e cópia
    // Continua até que todos os elementos de L e R sejam processados
    while (i < n1 && j < n2)
    {
        (*comparisons)++;
        if (L[i].moveId <= R[j].userId)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        (*copies)++;
        k++;
    }

    // Copia os elementos restantes de L e R, se houver
    // Atualiza as métricas de cópia
    while (i < n1)
    {
        arr[k] = L[i];
        (*copies)++;
        i++;
        k++;
    }

    // Copia os elementos restantes de R, se houver
    // Atualiza as métricas de cópia
    while (j < n2)
    {
        arr[k] = R[j];
        (*copies)++;
        j++;
        k++;
    }

    free(L);
    free(R);
}

// Função de ordenação merge sort
// Recebe o array, os índices esquerdo e direito, e ponteiros para, as variáveis de comparação e cópia
// Realiza a ordenação recursiva do array
void mergeSort(MoveRating arr[], int left, int right, long long *comparisons, long long *copies)
{
    // Verifica se o array tem mais de um elemento
    // Se sim, divide o array em dois subarrays e chama mergeSort recursivamente
    // Se não, retorna, pois o array já está ordenado
    if (left < right)
    {
        // Calcula o índice do meio
        // Divide o array em dois subarrays e chama mergeSort recursivamente
        // Mescla os subarrays de volta ao array original
        // Se não, retorna, pois o array já está ordenado
        int mid = left + (right - left) / 2;

        // Recursivamente ordena o subarray esquerdo
        mergeSort(arr, left, mid, comparisons, copies);
        // Recursivamente ordena o subarray direito
        mergeSort(arr, mid + 1, right, comparisons, copies);
        // Mescla os subarrays de volta ao array original
        merge(arr, left, mid, right, comparisons, copies);
    }
}

// Função de ordenação insertion sort
// Recebe o array, o tamanho, e ponteiros para as variáveis de comparação e cópia
// Realiza a ordenação do array usando o algoritmo de insertion sort
// Atualiza as métricas de comparação e cópia
void insertionSort(MoveRating arr[], int n, long long *comparisons, long long *copies)
{
    // Itera sobre o array, começando do segundo elemento
    // Compara o elemento atual com os anteriores e insere na posição correta
    // Atualiza as métricas de comparação e cópia
    // Continua até que todos os elementos estejam ordenados
    for (int i = 1; i < n; i++)
    {
        MoveRating key = arr[i];
        int j = i - 1;

        (*comparisons)++;
        while (j >= 0 && arr[j].userId > key.userId)
        {
            (*comparisons)++;
            arr[j + 1] = arr[j];
            (*copies)++;
            j--;
        }
        arr[j + 1] = key;
        (*copies)++;
    }
}

// Função de ordenação especial que combina merge sort e insertion sort
// Recebe o array, os índices esquerdo e direito, e ponteiros para as variveis de comparação e cópia
// Realiza a ordenação recursiva do array
// Se o tamanho do subarray for menor ou igual a 100, usa insertion sort
// Caso contrário, usa merge sort
// Atualiza as métricas de comparação e cópia
void specialMergeSort(MoveRating arr[], int left, int right, long long *comparisons, long long *copies)
{
    // Verifica se o tamanho do subarray é menor ou igual a 100
    // Se sim, usa insertion sort para ordenar o subarray
    // Se não, continua com merge sort
    if (right - left <= 100)
    {
        insertionSort(arr + left, right - left + 1, comparisons, copies);
        return;
    }

    // Se o tamanho do subarray for maior que 100, usa merge sort
    // Verifica se o array tem mais de um elemento
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        specialMergeSort(arr, left, mid, comparisons, copies);
        specialMergeSort(arr, mid + 1, right, comparisons, copies);
        merge(arr, left, mid, right, comparisons, copies);
    }
}