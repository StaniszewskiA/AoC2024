#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 101
#define HEIGHT 103
#define NUM_ROBOTS 500
#define STEPS 100
#define FILEPATH "input.txt"

typedef struct {
    int px, py, vx, vy;
} Robot;

void parse_input(const char *filepath, Robot **robots, int *robot_count) {
    FILE *file = fopen(filepath, "r");

    char line[NUM_ROBOTS];
    *robot_count = 0;
        while (fgets(line, sizeof(line), file)) {
            int px, py, vx, vy;
            int scanned = sscanf(line, "p=%d,%d v=%d,%d", &px, &py, &vx, &vy);

            (*robots) = realloc(*robots, sizeof(Robot) * (*robot_count + 1));
            (*robots)[*robot_count].px = px;
            (*robots)[*robot_count].py = py;
            (*robots)[*robot_count].vx = vx;
            (*robots)[*robot_count].vy = vy;
            (*robot_count)++;
        }

    fclose(file);
}

void run_simulation(Robot robot, int steps, int* x, int* y) {
    int px = robot.px;
    int py = robot.py;
    int vx = robot.vx;
    int vy = robot.vy;

    *x = (px + vx * steps) % WIDTH;
    *y = (py + vy * steps) % HEIGHT;

    if (*x < 0) {
        *x += WIDTH; 
    }
    if (*y < 0) {
        *y += HEIGHT;  
    }
}


long long int count_by_quad(
    int *robot_positions, 
    int robot_count
) {
    int mid_x = WIDTH / 2;
    int mid_y = HEIGHT / 2;
    int quad_counts[4] = {0};

    for (int i = 0; i < robot_count; i++) {
        int x = robot_positions[i * 2];
        int y = robot_positions[i * 2 + 1];
        if (x != mid_x && y != mid_y) {
            int quad_id = 2 * (x < mid_x) + (y < mid_y);
            quad_counts[quad_id]++;
        }
    }

    return quad_counts[0] * quad_counts[1] * quad_counts[2] * quad_counts[3];
}

int get_lowest_entropy(
    Robot *robots,
    int robot_count
) {
    int lines[HEIGHT][WIDTH];
    memset(lines, 0, sizeof(lines));

    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        int robot_positions[robot_count * 2];
        int robot_positions_count = 0;

        for (int j = 0; j < robot_count; j++) {
            int x, y;
            run_simulation(robots[j], i, &x, &y);
            robot_positions[robot_positions_count * 2] = x;
            robot_positions[robot_positions_count * 2 + 1] = y;
            robot_positions_count++;
        }

        int max_line = 0, y_pos = -1;
        for (int y = 0; y < HEIGHT; y++) {
            int count = 0;
            for (int j = 0; j < robot_positions_count; j++) {
                if (robot_positions[j * 2 + 1] == y) {
                    count++;
                }
            }
            if (count > max_line) {
                max_line = count;
                y_pos =y;
            }
        }

        if (max_line >= 30) {
            int contiguous = 0;
            for (int x = 0; x < WIDTH; x++) {
                int found = 0;
                for (int j = 0; j < robot_positions_count; j++) {
                    if (robot_positions[j * 2] == x && robot_positions[j * 2 + 1] == y_pos) {
                        found = 1;
                        break;
                    }
                }
                if (found) {
                    contiguous++;
                } else {
                    contiguous = 0;
                }
                if (contiguous == 30) {
                    return i;
                }
            }
        }
    }

    return -1;
}

int main() {
    Robot *robots = NULL;
    int robot_count = 0;
    parse_input(FILEPATH, &robots, &robot_count);

    int robot_positions[robot_count * 2];
    for (int i = 0; i < robot_count; i++) {
        int x, y;
        run_simulation(robots[i], STEPS, &x, &y);
        robot_positions[i * 2] = x;
        robot_positions[i * 2 + 1] = y;
    }

    printf("Result 1: %lld\n", count_by_quad(robot_positions, robot_count));
    printf("Result 2: %d\n", get_lowest_entropy(robots, robot_count));
}