#include "task1.h"

int dirs_task_1[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void task1(char input_grid[MAX_ROWS][MAX_COLS], int rows, int cols) {
    int i, j;
    bool found = false;

    // Get the starting position
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (input_grid[i][j] == '^') {
                found = true;
                break;
            }
        }
        if (found) break;
    }

    int curr_dir = 0;

    bool seen[MAX_ROWS][MAX_COLS] = {{false}}; 
    int result = 0;

    while (true) {
        if (!seen[i][j]) {
            seen[i][j] = true;
            result++;
        }

        int next_i = i + dirs_task_1[curr_dir][0];
        int next_j = j + dirs_task_1[curr_dir][1];

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

    printf("%d\n", result);
}