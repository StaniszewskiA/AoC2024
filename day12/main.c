#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 150
#define MAX_COLS 150

typedef char Grid[MAX_ROWS][MAX_COLS];
typedef struct {
    int row, col;
} Position;

typedef struct {
    Position positions[MAX_ROWS * MAX_COLS];
    int size;
} Region;

int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int is_in_bounds(Grid grid, int row, int col, int rows, int cols) {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}

void bfs(Grid grid, int rows, int cols, int row, int col, char area, Region *region, int visited[MAX_ROWS][MAX_COLS]) {
    if (!is_in_bounds(grid, row, col, rows, cols)) return;
    if (grid[row][col] != area || visited[row][col] || region->size >= MAX_ROWS * MAX_COLS) return;

    visited[row][col] = 1;
    region->positions[region->size++] = (Position){row, col};

    for (int i = 0; i < 4; i++) {
        int new_row = row + dirs[i][0];
        int new_col = col + dirs[i][1];
        bfs(grid, rows, cols, new_row, new_col, area, region, visited);
    }

    printf("DONE");
}


void get_all_regions(Grid grid, int rows, int cols, Region regions[MAX_ROWS * MAX_COLS], int *region_count) {
    int visited[MAX_ROWS][MAX_COLS] = {{0}};
    *region_count = 0;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (!visited[row][col]) {
                Region region = {{0}, 0};
                bfs(grid, rows, cols, row, col, grid[row][col], &region, visited);
                regions[*region_count] = region;
                (*region_count)++;
            }
        }
    }
}

void parse_input(const char *filepath, Grid grid, int *rows, int *cols) {
    FILE *file = fopen(filepath, "r");
    if (!file) {
        perror("Failed to open file");
        exit(1);
    }

    *rows = 0;
    while (fgets(grid[*rows], MAX_COLS, file)) {
        grid[*rows][strcspn(grid[*rows], "\n")] = '\0'; 
        (*rows)++;
    }
    *cols = strlen(grid[0]);

    printf("Rows: %d, Cols: %d\n", *rows, *cols);  

    fclose(file);
}

long long solve_task_1(Grid grid, int rows, int cols) {
    Region regions[MAX_ROWS * MAX_COLS];
    int region_count = 0;
    get_all_regions(grid, rows, cols, regions, &region_count);

    long long result = 0;

    for (int i = 0; i < region_count; i++) {
        Region region = regions[i];
        int area = region.size;
        int perimeter = 0;

        for (int j = 0; j < region.size; j++) {
            Position p = region.positions[j];

            for (int d = 0; d < 4; d++) {
                int new_row = p.row + dirs[d][0];
                int new_col = p.col + dirs[d][1];

                if (!is_in_bounds(grid, new_row, new_col, rows, cols)) continue;
                if (grid[new_row][new_col] != grid[p.row][p.col]) {
                    perimeter++;
                }
            }
        }

        result += (long long)area * perimeter; 
    }

    return result;
}


int solve_task_2(Grid grid, int rows, int cols) {
    Region regions[MAX_ROWS * MAX_COLS];
    int region_count = 0;
    get_all_regions(grid, rows, cols, regions, &region_count);

    int result = 0;

    for (int i = 0; i < region_count; i++) {
        Region region = regions[i];
        int area = region.size;
        int corners = 0;

        for (int j = 0; j < region.size; j++) {
            Position p = region.positions[j];

            for (int d = 0; d < 4; d++) {
                int new_row = p.row + dirs[d][0];
                int new_col = p.col + dirs[d][1];

                if (!is_in_bounds(grid, new_row, new_col, rows, cols)) continue;
                if (grid[new_row][new_col] != grid[p.row][p.col]) {
                    corners++;
                }
            }
        }

        result += area * corners;
    }

    return result;
}

int main() {
    Grid grid;
    int rows, cols;

    parse_input("input.txt", grid, &rows, &cols);

    printf("Task 1 Result: %lld\n", solve_task_1(grid, rows, cols));
    printf("Task 2 Result: %d\n", solve_task_2(grid, rows, cols));

    return 0;
}
