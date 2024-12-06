#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ROWS 150
#define MAX_COLS 150

extern int dirs_task_2[4][2];

bool will_loop(
    char input_grid[MAX_ROWS][MAX_COLS],
    int rows,
    int cols,
    int obstacle_i,
    int obstacle_j,
    int initial_i,
    int initial_j
);

void task2(char input_grid[MAX_ROWS][MAX_COLS], int rows, int cols);