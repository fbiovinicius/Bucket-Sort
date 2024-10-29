#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUCKETS 10  // Número de buckets
#define MAX 10      // Número de elementos

// Estrutura para o nó da lista ligada (usada nos buckets)
struct Node {
    int data;
    struct Node* next;
};

// Função para inserir um elemento em um bucket, mantendo-o ordenado
void insert(struct Node** bucket, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    // Se o bucket está vazio ou o novo valor é menor que o primeiro, insere na frente
    if (*bucket == NULL || (*bucket)->data >= value) {
        newNode->next = *bucket;
        *bucket = newNode;
    } else {
        // Encontrar a posição correta para inserir
        struct Node* current = *bucket;
        while (current->next != NULL && current->next->data < value) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Função para ordenar o array usando Bucket Sort
void bucketSort(int array[], int n) {
    struct Node* buckets[BUCKETS] = {NULL};

    // Distribuir os elementos nos buckets
    for (int i = 0; i < n; i++) {
        int bucketIndex = array[i] / (100 / BUCKETS);  // Converte o valor em índice (0-9)
        insert(&buckets[bucketIndex], array[i]);
    }

    // Reunir os elementos dos buckets de volta no array original
    int index = 0;
    for (int i = 0; i < BUCKETS; i++) {
        struct Node* node = buckets[i];
        while (node != NULL) {
            array[index++] = node->data;
            node = node->next;
        }
    }

    // Liberar a memória alocada
    for (int i = 0; i < BUCKETS; i++) {
        struct Node* node = buckets[i];
        while (node != NULL) {
            struct Node* temp = node;
            node = node->next;
            free(temp);
        }
    }
}

// Função para gerar números aleatórios
void generateRandomNumbers(int array[], int size, int maxValue) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % maxValue;  // Gera um número aleatório entre 0 e maxValue-1
    }
}

// Função principal para teste
int main() {
    srand(time(NULL));  // Define a semente para números aleatórios
    int array[MAX];

    generateRandomNumbers(array, MAX, 100);  // Gera números aleatórios entre 0 e 99

    printf("Array original:\n");
    for (int i = 0; i < MAX; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    bucketSort(array, MAX);

    printf("\nArray ordenado:\n");
    for (int i = 0; i < MAX; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}

