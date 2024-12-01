#include <stdio.h>
#include <string.h>
#include "reconcile.h"

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

    int total_sim_score = calculate_sim_score(left_list, right_list, size);
    printf("Total Similarity Score: %d\n", total_sim_score);

    return 0;
}