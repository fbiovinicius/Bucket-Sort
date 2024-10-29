#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENTS 100000

// Função auxiliar para quicksort
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void bucketSort(int arr[], int n) {
    int max_val = arr[0];
    int min_val = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) max_val = arr[i];
        if (arr[i] < min_val) min_val = arr[i];
    }

    int bucket_size = (max_val - min_val) / MAX_ELEMENTS + 1;

    int** buckets = (int**)malloc(MAX_ELEMENTS * sizeof(int*));
    int* bucket_sizes = (int*)calloc(MAX_ELEMENTS, sizeof(int));

    for (int i = 0; i < MAX_ELEMENTS; i++) {
        buckets[i] = (int*)malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        int index = (arr[i] - min_val) / bucket_size;
        buckets[index][bucket_sizes[index]++] = arr[i];
    }

    int index = 0;
    for (int i = 0; i < MAX_ELEMENTS; i++) {
        if (bucket_sizes[i] > 0) {
            qsort(buckets[i], bucket_sizes[i], sizeof(int), compare);
            for (int j = 0; j < bucket_sizes[i]; j++) {
                arr[index++] = buckets[i][j];
            }
        }
        free(buckets[i]);
    }

    free(buckets);
    free(bucket_sizes);
}

// Função para inicializar o vetor em diferentes estados
void initializeArray(int arr[], int n, int type) {
    switch (type) {
        case 1: // Ordenado decrescentemente
            for (int i = 0; i < n; i++) arr[i] = n - i;
            break;
        case 2: // Ordenado crescentemente
            for (int i = 0; i < n; i++) arr[i] = i + 1;
            break;
        case 3: // Primeira metade crescente, segunda metade decrescente
            for (int i = 0; i < n / 2; i++) arr[i] = i + 1;
            for (int i = n / 2; i < n; i++) arr[i] = n - i;
            break;
        case 4: // Primeira metade decrescente, segunda metade crescente
            for (int i = 0; i < n / 2; i++) arr[i] = n / 2 - i;
            for (int i = n / 2; i < n; i++) arr[i] = i - n / 2 + 1;
            break;
        case 5: // Totalmente desordenado
            for (int i = 0; i < n; i++) arr[i] = rand() % n;
            break;
    }
}

// Função para medir o tempo de execução do bucketSort
void measureSortTime(int arr[], int n, int type, const char* description) {
    initializeArray(arr, n, type);
    
    clock_t start = clock();
    bucketSort(arr, n);
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tempo para %s: %.6f segundos\n", description, time_spent);
}

int main() {
    int arr[MAX_ELEMENTS];

    printf("Avaliação de tempo para diferentes configurações do vetor:\n");

    measureSortTime(arr, MAX_ELEMENTS, 1, "vetor ordenado decrescentemente");
    measureSortTime(arr, MAX_ELEMENTS, 2, "vetor ordenado crescentemente");
    measureSortTime(arr, MAX_ELEMENTS, 3, "primeira metade crescente, segunda metade decrescente");
    measureSortTime(arr, MAX_ELEMENTS, 4, "primeira metade decrescente, segunda metade crescente");
    measureSortTime(arr, MAX_ELEMENTS, 5, "vetor totalmente desordenado");

    return 0;
}

