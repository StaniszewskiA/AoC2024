#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define FILENAME "input.txt"
#define ALPHABET 26
#define COMPUTERS 14

int checkAllCombinations(int arr[], int size, int combination[]);
int checkAllCombinationsOfR(int arr[], int n, int r, int idx, int data[], int i);
int checkCombination(int* combination, int size);
int compare(const void *a, const void *b);
void readInput();
void processClique(int *bestCliqueLength, int *bestCliqueidx);

int adj_mat[ALPHABET * ALPHABET][ALPHABET * ALPHABET] = {0};
int connectionLists[ALPHABET * ALPHABET][ALPHABET * ALPHABET];
int connectionListLenghts[ALPHABET * ALPHABET] = {0};
int cliques[ALPHABET * ALPHABET][COMPUTERS] = {0};
int cliqueLengths[ALPHABET * ALPHABET] = {0};


int main() {
    readInput();

    int bestCliqueLength = 0;
    int bestCliqueidx = 0;
    
    processClique(&bestCliqueLength, &bestCliqueidx);

    qsort(cliques[bestCliqueidx], bestCliqueLength, sizeof(int), compare);

    for (int i = 0; i < bestCliqueLength; i++) {
        printf("%c%c", (cliques[bestCliqueidx][i] / ALPHABET) + 'a', (cliques[bestCliqueidx][i] % ALPHABET) + 'a');
        if (i != bestCliqueLength-1) {
            printf(",");
        }
    }
    printf("\n");
}

void readInput() {
    FILE* fin = fopen(FILENAME, "r");

    while (!feof(fin)) {
        char label1[2];
        char label2[2];
        fscanf(fin, "%2c-%2c ", &label1, &label2);
        int idx1 = ALPHABET * (label1[0]-'a') + (label1[1]-'a');
        int idx2 = ALPHABET * (label2[0]-'a') + (label2[1]-'a');
        adj_mat[idx1][idx2] = 1;
        adj_mat[idx2][idx1] = 1;
        connectionLists[idx1][connectionListLenghts[idx1]++] = idx2;
        connectionLists[idx2][connectionListLenghts[idx2]++] = idx1;
    }

    fclose(fin);
}

void processClique(int *bestCliqueLength, int *bestCliqueidx) {
    for (int i = 0; i < ALPHABET*ALPHABET; i++) {
        if (connectionListLenghts[i] != 0) {
            cliqueLengths[i] = checkAllCombinations(connectionLists[i], connectionListLenghts[i], cliques[i]);
            cliques[i][cliqueLengths[i]++] = i;
            if (cliqueLengths[i] > *bestCliqueLength) {
                *bestCliqueLength = cliqueLengths[i];
                *bestCliqueidx = i;
            }
        }
    }
}

int checkAllCombinations(int arr[], int size, int combination[]) {
    for (int i = size; i >= 1; i--) {
        if (checkAllCombinationsOfR(arr, size, i, 0, combination, 0)) {
            return i;
        }
    }
    return 0;
}

int checkAllCombinationsOfR(int arr[], int n, int r, int idx, int data[], int i) {
    if (idx == r) {
        if (checkCombination(data, r)) {
            return 1;
        }
        return 0;
    }
 
    if (i >= n) {
        return 0;
    }
 
    data[idx] = arr[i];
    if (checkAllCombinationsOfR(arr, n, r, idx + 1, data, i + 1)) {
        return 1;
    }
 
    if (checkAllCombinationsOfR(arr, n, r, idx, data, i + 1)) {
        return 1;
    }
    return 0;
}

int checkCombination(int* combination, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i+1; j < size; j++) {
            if (!adj_mat[combination[i]][combination[j]]) {
                return 0;
            }
        }
    }
    return 1;
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}