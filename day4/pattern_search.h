#ifndef PATTERN_SEARCH_h
#define PATTERN_SEARCH_h

#define MAX_ROWS 1000
#define MAX_COLS 1000

void read_grid(const char *filename, char grid[MAX_ROWS][MAX_COLS], int *rows, int *cols);
void count_patterns(char grid[MAX_ROWS][MAX_COLS], int rows, int cols);

#endif