#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUCKETS 10  // N�mero de buckets
#define MAX 10      // N�mero de elementos

// Estrutura para o n� da lista ligada (usada nos buckets)
struct Node {
    int data;
    struct Node* next;
};

// Fun��o para inserir um elemento em um bucket, mantendo-o ordenado
void insert(struct Node** bucket, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    // Se o bucket est� vazio ou o novo valor � menor que o primeiro, insere na frente
    if (*bucket == NULL || (*bucket)->data >= value) {
        newNode->next = *bucket;
        *bucket = newNode;
    } else {
        // Encontrar a posi��o correta para inserir
        struct Node* current = *bucket;
        while (current->next != NULL && current->next->data < value) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Fun��o para ordenar o array usando Bucket Sort
void bucketSort(int array[], int n) {
    struct Node* buckets[BUCKETS] = {NULL};

    // Distribuir os elementos nos buckets
    for (int i = 0; i < n; i++) {
        int bucketIndex = array[i] / (100 / BUCKETS);  // Converte o valor em �ndice (0-9)
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

    // Liberar a mem�ria alocada
    for (int i = 0; i < BUCKETS; i++) {
        struct Node* node = buckets[i];
        while (node != NULL) {
            struct Node* temp = node;
            node = node->next;
            free(temp);
        }
    }
}

// Fun��o para gerar n�meros aleat�rios
void generateRandomNumbers(int array[], int size, int maxValue) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % maxValue;  // Gera um n�mero aleat�rio entre 0 e maxValue-1
    }
}

// Fun��o principal para teste
int main() {
    srand(time(NULL));  // Define a semente para n�meros aleat�rios
    int array[MAX];

    generateRandomNumbers(array, MAX, 100);  // Gera n�meros aleat�rios entre 0 e 99

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

