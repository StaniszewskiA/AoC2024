#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pattern_search.h"

void read_grid(const char *filename, char grid[MAX_ROWS][MAX_COLS], int *rows, int *cols) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    *rows = 0;
    while (fgets(grid[*rows], MAX_COLS, file)) {
        grid[*rows][strcspn(grid[*rows], "\n")] = '\0';
        *cols = strlen(grid[*rows]);
        (*rows)++;
    }
    fclose(file);
}

void count_patterns(char grid[MAX_ROWS][MAX_COLS], int rows, int cols) {
    int res1 = 0, res2 = 0;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (c + 3 < cols && grid[r][c] == 'X' && grid[r][c+1] == 'M' && grid[r][c+2] == 'A' && grid[r][c+3] == 'S') res1++;
            if (r + 3 < rows && grid[r][c] == 'X' && grid[r+1][c] == 'M' && grid[r+2][c] == 'A' && grid[r+3][c] == 'S') res1++;
            if (r + 3 < rows && c + 3 < cols && grid[r][c] == 'X' && grid[r+1][c+1] == 'M' && grid[r+2][c+2] == 'A' && grid[r+3][c+3] == 'S') res1++;
            if (c + 3 < cols && grid[r][c] == 'S' && grid[r][c+1] == 'A' && grid[r][c+2] == 'M' && grid[r][c+3] == 'X') res1++;
            if (r + 3 < rows && grid[r][c] == 'S' && grid[r+1][c] == 'A' && grid[r+2][c] == 'M' && grid[r+3][c] == 'X') res1++;
            if (r + 3 < rows && c + 3 < cols && grid[r][c] == 'S' && grid[r+1][c+1] == 'A' && grid[r+2][c+2] == 'M' && grid[r+3][c+3] == 'X') res1++;
            if (r - 3 >= 0 && c + 3 < cols && grid[r][c] == 'S' && grid[r-1][c+1] == 'A' && grid[r-2][c+2] == 'M' && grid[r-3][c+3] == 'X') res1++;
            if (r - 3 >= 0 && c + 3 < cols && grid[r][c] == 'X' && grid[r-1][c+1] == 'M' && grid[r-2][c+2] == 'A' && grid[r-3][c+3] == 'S') res1++;

            if (r + 2 < rows && c + 2 < cols) {
                if (grid[r][c] == 'M' && grid[r+1][c+1] == 'A' && grid[r+2][c+2] == 'S') {
                    if (grid[r+2][c] == 'M' && grid[r][c+2] == 'S') res2++;
                    if (grid[r+2][c] == 'S' && grid[r][c+2] == 'M') res2++;
                }
                if (grid[r][c] == 'S' && grid[r+1][c+1] == 'A' && grid[r+2][c+2] == 'M') {
                    if (grid[r+2][c] == 'M' && grid[r][c+2] == 'S') res2++;
                    if (grid[r+2][c] == 'S' && grid[r][c+2] == 'M') res2++;
                }
            }
        }
    }

    printf("%d\n", res1);
    printf("%d\n", res2);
}