#include "day10.h"

int main() {
    memset(memo, -1, sizeof(memo));

    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    while (fgets(grid[n], MAX_N, file) != NULL) {
        grid[n][strcspn(grid[n], "\n")] = '\0'; 
        n++;
    }
    fclose(file);

    int total_score = 0;
    int total_rating = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < strlen(grid[i]); j++) {
            if (grid[i][j] == '0') {
                total_score += score(i, j);
                total_rating += rating(i, j);
            }
        }
    }

    printf("Total score: %d\n", total_score);
    printf("Total rating: %d\n", total_rating);

    return EXIT_SUCCESS;
}