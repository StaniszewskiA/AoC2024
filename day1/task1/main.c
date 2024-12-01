#include <stdio.h>
#include <string.h>
#include "reconcile.h"

#define MAX_LINES 1001

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Failed to open input file");
        return 1;
    }

    int left_list[MAX_LINES], right_list[MAX_LINES];
    int size = 0;
        
    while (size < MAX_LINES && fscanf(file, "%d %d", &left_list[size], &right_list[size]) == 2) {
        size++;
    }

    fclose(file);

    int total_distance = calculate_total_dist(left_list, right_list, size);
    printf("Total Distance: %d\n", total_distance);

    return 0;
}