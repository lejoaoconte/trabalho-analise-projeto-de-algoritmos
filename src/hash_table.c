#include "hash_table.h"
#include <stdlib.h>
#include <string.h>

// Função de hash para calcular o índice baseado no userId e moveId
// Usa o algoritmo djb2 para gerar um hash único
// Recebe o userId, moveId e o tamanho da tabela
// Retorna o índice calculado
static int hash(int userId, int moveId, int size)
{
    unsigned long h = 5381;
    h = ((h << 5) + h) + userId;
    h = ((h << 5) + h) + moveId;
    return h % size;
}

// Função para criar uma tabela de hash com encadeamento
// Recebe o tamanho da tabela
// Aloca memória para a tabela e inicializa os valores
// Retorna um ponteiro para a tabela de hash criada
HashTableChaining *createHashTableChaining(int size)
{
    // Aloca memória para a tabela de hash
    HashTableChaining *ht = malloc(sizeof(HashTableChaining));
    if (!ht)
        return NULL;
    ht->table = calloc(size, sizeof(Node *));
    // Verifica se a alocação foi bem-sucedida
    if (!ht->table)
    {
        free(ht);
        return NULL;
    }
    // Inicializa o tamanho e as comparações
    ht->size = size;
    ht->comparisons = 0;
    return ht;
}

// Função para inserir um MoveRating na tabela de hash com encadeamento
// Recebe a tabela de hash e o MoveRating a ser inserido
// Calcula o índice usando a função hash
// Verifica se já existe um nó com o mesmo userId e moveId
// Se existir, não insere o novo nó
// Se não existir, cria um novo nó, inicializa com os dados e insere no
// início da lista encadeada
void insertChaining(HashTableChaining *ht, MoveRating data)
{
    // Calcula o índice usando a função hash
    int index = hash(data.userId, data.moveId, ht->size);
    // Verifica se já existe um nó com o mesmo userId e moveId
    Node *current = ht->table[index];
    // Itera pela lista encadeada para verificar se o nó já existe
    // Se encontrar um nó com os mesmos userId e moveId, não insere
    // Se não encontrar, cria um novo nó e o insere no início da lista
    while (current != NULL)
    {
        ht->comparisons++;
        if (current->data.userId == data.userId && current->data.moveId == data.moveId)
        {
            return;
        }
        current = current->next;
    }

    // Cria um novo nó, inicializa com os dados e insere no início da lista
    Node *newNode = malloc(sizeof(Node));
    if (!newNode)
        return;

    // Verifica se a alocação foi bem-sucedida
    newNode->data = data;
    newNode->next = ht->table[index];
    ht->table[index] = newNode;
}

// Função para liberar a memória da tabela de hash com encadeamento
// Itera por cada índice da tabela, libera os nós encadeados e a tabela
// Recebe a tabela de hash
// Libera a memória alocada para a tabela e os nós encadeados
void freeHashTableChaining(HashTableChaining *ht)
{
    if (!ht)
        return;
    for (int i = 0; i < ht->size; i++)
    {
        Node *current = ht->table[i];
        while (current != NULL)
        {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}

// Função para obter o número de comparações realizadas na tabela de hash com encadeamento
long long getComparisonsChaining(HashTableChaining *ht)
{
    return ht->comparisons;
}

// Função para obter o uso de memória da tabela de hash com encadeamento
long getMemoryUsageChaining(HashTableChaining *ht)
{
    // Calcula o uso de memória total
    long memory = sizeof(HashTableChaining) + ht->size * sizeof(Node *);
    // Itera por cada índice da tabela e soma o tamanho dos nós encadeados
    for (int i = 0; i < ht->size; i++)
    {
        Node *current = ht->table[i];
        // Soma o tamanho de cada nó encadeado
        while (current != NULL)
        {
            memory += sizeof(Node);
            current = current->next;
        }
    }
    return memory;
}

// Função para criar uma tabela de hash linear
// Recebe o tamanho da tabela
// Aloca memória para a tabela e inicializa os valores
// Retorna um ponteiro para a tabela de hash criada
HashTableLinear *createHashTableLinear(int size)
{
    // Aloca memória para a tabela de hash linear
    HashTableLinear *ht = malloc(sizeof(HashTableLinear));
    if (!ht)
        return NULL;
    ht->table = malloc(size * sizeof(MoveRating));
    // Verifica se a alocação foi bem-sucedida
    if (!ht->table)
    {
        free(ht);
        return NULL;
    }
    // Inicializa o tamanho e as comparações
    ht->size = size;
    ht->comparisons = 0;
    for (int i = 0; i < size; i++)
    {
        ht->table[i].userId = -1;
    }
    return ht;
}

// Função para inserir um MoveRating na tabela de hash linear
// Recebe a tabela de hash e o MoveRating a ser inserido
// Calcula o índice usando a função hash
// Verifica se já existe um elemento com o mesmo userId e moveId
// Se existir, não insere o novo elemento
// Se não existir, insere o elemento na posição livre
void insertLinearProbing(HashTableLinear *ht, MoveRating data)
{
    // Calcula o índice usando a função hash
    int index = hash(data.userId, data.moveId, ht->size);
    // Verifica se já existe um elemento com o mesmo userId e moveId
    // Se existir, não insere o novo elemento
    // Se não existir, insere o elemento na posição livre
    // Itera pela tabela até encontrar uma posição livre ou o elemento já existente
    // Incrementa o contador de comparações a cada iteração
    // Se encontrar uma posição livre, insere o elemento
    // Se encontrar o elemento já existente, não insere
    while (ht->table[index].userId != -1)
    {
        ht->comparisons++;
        if (ht->table[index].userId == data.userId && ht->table[index].moveId == data.moveId)
        {
            return;
        }
        index = (index + 1) % ht->size;
    }
    // Insere o elemento na posição livre
    ht->table[index] = data;
}

// Função para liberar a memória da tabela de hash linear
void freeHashTableLinear(HashTableLinear *ht)
{
    if (!ht)
        return;
    free(ht->table);
    free(ht);
}

// Função para obter o número de comparações realizadas na tabela de hash linear
long long getComparisonsLinear(HashTableLinear *ht)
{
    return ht->comparisons;
}

// Função para obter o uso de memória da tabela de hash linear
long getMemoryUsageLinear(HashTableLinear *ht)
{
    return sizeof(HashTableLinear) + ht->size * sizeof(MoveRating);
}
