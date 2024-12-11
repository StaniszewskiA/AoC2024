#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solver.h"

#define MULTIPLIER 2024
#define MAX_DICT_SIZE 10000

typedef struct {
    int stone;
    int iters;
    int result;
} BlinkEntry;

BlinkEntry blink_dict[MAX_DICT_SIZE];
int blink_dict_size = 0;

int* parse_input(const char* filename, int* size) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int* numbers = malloc(1000 * sizeof(int));
    int num;
    *size = 0;

    while (fscanf(file, "%d", &num) == 1) {
        numbers[(*size)++] = num;
    }

    fclose(file);
    return numbers;
}

int find_in_dict(int stone, int iters) {
    for (int i = 0; i < blink_dict_size; i++) {
        if (blink_dict[i].stone == stone && blink_dict[i].iters == iters) {
            return i;
        }
    }
    return -1;
}

void add_to_dict(int stone, int iters, int result) {
    if (blink_dict_size < MAX_DICT_SIZE) {
        blink_dict[blink_dict_size].stone = stone;
        blink_dict[blink_dict_size].iters = iters;
        blink_dict[blink_dict_size].result = result;
        blink_dict_size++;
    }
}

int* update_stone(int stone, int* size) {
    char stone_str[20];
    snprintf(stone_str, sizeof(stone_str), "%d", stone);

    if (stone == 0) {
        int* result = malloc(sizeof(int));
        result[0] = 1;
        *size = 1;
        return result;
    }

    int len = strlen(stone_str);
    if (len % 2 == 1) {
        int* result = malloc(sizeof(int));
        result[0] = stone * MULTIPLIER;
        *size = 1;
        return result;
    }

    int mid = len / 2;
    int* result = malloc(2 * sizeof(int));
    char left[mid + 1];
    char right[len - mid + 1];
    strncpy(left, stone_str, mid);
    left[mid] = '\0';
    strcpy(right, stone_str + mid);

    result[0] = atoi(left);
    result[1] = atoi(right);
    *size = 2;
    return result;
}

int blink(int stone, int iters) {
    int dict_index = find_in_dict(stone, iters);
    if (dict_index != -1) {
        return blink_dict[dict_index].result;
    }

    int size;
    int* updated_stones = update_stone(stone, &size);

    if (iters == 0) {
        free(updated_stones);
        return size;
    }

    int result = 0;
    for (int i = 0; i < size; i++) {
        result += blink(updated_stones[i], iters - 1);
    }

    free(updated_stones);
    add_to_dict(stone, iters, result);
    return result;
}

int solve(int* stones, int num_stones, int iters) {
    int result = 0;
    for (int i = 0; i < num_stones; i++) {
        result += blink(stones[i], iters - 1);
    }
    return result;
}
