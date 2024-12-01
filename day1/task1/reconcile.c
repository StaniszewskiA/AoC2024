#include <stdlib.h>
#include "reconcile.h"

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int calculate_total_dist(int left_list[], int right_list[], int size) {
    qsort(left_list, size, sizeof(int), compare);
    qsort(right_list, size, sizeof(int), compare);

    int total_dist = 0;
    for (int i = 0; i < size; i++) {
        total_dist += abs(left_list[i] - right_list[i]);
    }

    return total_dist;
}