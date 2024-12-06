#include "task2.h"

int dirs_task_2[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool will_loop(
    char input_grid[MAX_ROWS][MAX_COLS],
    int rows,
    int cols,
    int obstruction_i,
    int obstruction_j,
    int initial_i,
    int initial_j
) {
    if (input_grid[obstruction_i][obstruction_j] == '#') {
        return false;
    } 

    input_grid[obstruction_i][obstruction_j] = '#';

    int i = initial_i, j = initial_j;
    int dir = 0;
    bool seen[MAX_ROWS][MAX_COLS][4] = {{{false}}}; // [4] stems from the need to consider the dirs_task_2

    while (true) {
        if (seen[i][j][dir]) {
            input_grid[obstruction_i][obstruction_j] = '.';  
            return true;
        }
        seen[i][j][dir] = true;

        int next_i = i + dirs_task_2[dir][0];
        int next_j = j + dirs_task_2[dir][1];

        if (next_i < 0 || next_i >= rows || next_j < 0 || next_j >= cols) {
            input_grid[obstruction_i][obstruction_j] = '.';  
            return false;  
        }

        if (input_grid[next_i][next_j] == '#') {
            dir = (dir + 1) % 4;
        } else {
            i = next_i;
            j = next_j;
        }
    }
}

void task2(char input_grid[MAX_ROWS][MAX_COLS], int rows, int cols) {
    int ii, ij;
    bool found = false;

    // Get the starting position
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (input_grid[i][j] == '^') {
                ii = i;
                ij = j;
                found = true;
                break;
            }
        }
        if (found) break;
    }

    int i = ii, j = ij;
    int curr_dir = 0;
    bool original_seen[MAX_ROWS][MAX_COLS] = {{false}};
    int original_seen_count = 0;

    while (true) {
        if (!original_seen[i][j]) {
            original_seen[i][j] = true;
            original_seen_count++;
        }

        int next_i = i + dirs_task_2[curr_dir][0];
        int next_j = j + dirs_task_2[curr_dir][1];

        if (next_i < 0 || next_i >= rows || next_j < 0 || next_j >= cols) {
            break;
        }

        if (input_grid[next_i][next_j] == '#') {
            curr_dir = (curr_dir + 1) % 4;
        } else {
            i = next_i;
            j = next_j;
        }
    }

    int result = 0;
    for (int obstruction_i = 0; obstruction_i < rows; obstruction_i++) {
        for (int obstruction_j = 0; obstruction_j < cols; obstruction_j++) {
            if (original_seen[obstruction_i][obstruction_j]) {
                if (will_loop(input_grid, rows, cols, obstruction_i, obstruction_j, ii, ij)) {
                    result++;
                }
            }
        }
    }

    printf("%d\n", result);
}