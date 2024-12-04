#include <stdio.h>
#include "pattern_search.h"

int main() {
    const char *filename = "input.txt";
    char grid[MAX_ROWS][MAX_COLS];
    int rows = 0, cols = 0;

    read_grid(filename, grid, &rows, &cols);
    count_patterns(grid, rows, cols);
    
    return 0;
}