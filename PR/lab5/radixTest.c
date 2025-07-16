#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void radixCompDown(int count[], int* arr, int output[], int size, int exp) {
    for (int i = 17; i >= 0; i--) {
        count[i] += count[i + 1];
    }
    for (int i = size - 1; i >= 0; i--) {
        long index = count[((arr[i] / exp) % 10) + 9] - 1;
        output[index] = arr[i];
        count[((arr[i] / exp) % 10) + 9]--;
    }
    for (int i = 0; i < size; i++) {
        arr[i] = output[i];
    }
}

void radixCompUp(int count[], int* arr, int output[], int size, int exp) {
    for (int i = 1; i < 19; i++) {
        count[i] += count[i - 1];
    }
    for (int i = size - 1; i >= 0; i--) {
        long index = count[((arr[i] / exp) % 10) + 9] - 1;
        output[index] = arr[i];
        count[((arr[i] / exp) % 10) + 9]--;
    }
    for (int i = 0; i < size; i++) {
        arr[i] = output[i];
    }
}

void countSort(int* arr, int size, int exp, void (*comparator)(int[], int*, int[], int, int)) {
    int output[size];
    int count[19] = {0};
    for (int i = 0; i < size; i++) {
        count[((arr[i] / exp) % 10) + 9]++;
    }
    comparator(count, arr, output, size, exp);
}

void radixSort(int* arr, int size, FILE* outputFile, void (*comparator)(int[], int*, int[], int, int)) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    for (int exp = 1; max / exp > 0; exp*=10) {
        countSort(arr, size, exp, comparator);
    }
    for (int i = 0; i < size; i++) {
        fprintf(outputFile, "%d ", arr[i]);
    }
}

int main(void) {
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w+");
    int n;
    fscanf(inputFile, "%d", &n);
    int array[n];
    for (int i = 0; i < n; i++) {
        fscanf(inputFile, "%d", &array[i]);
    }
    radixSort(array, n, outputFile, radixCompDown);
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}