#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 50

char map[SIZE][SIZE];

void read_map_from_file(FILE *file) {
    for (int i = 0; i < SIZE; i++) {
        fscanf(file, "%s ", map[i]);
    }
}

void find_initial_position(int *x, int *y) {
    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < SIZE; i++) {
            if (map[j][i] == '@') {
                *x = i;
                *y = j;
                return;
            }
        }
    }
}

bool move(int x, int y, int vx, int vy) {
    switch (map[y+vy][x+vx]) {
        case 'O': {
            bool result = move(x+vx, y+vy, vx, vy);
            if (!result) return false;
        }
        case '.':
            map[y+vy][x+vx] = map[y][x];
            map[y][x] = '.';
            return true;
        case '#':
            return false;
    }
    return true;
}

long calculate_sum() {
    long sum = 0;
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            if (map[y][x] == 'O') sum += 100 * y + x;
        }
    }
    return sum;
}

void process_moves(FILE *file, int *x, int *y) {
    char c;
    while ((c = fgetc(file)) != EOF) {
        int vx = 0, vy = 0;
        switch (c) {
            case '<': vx = -1, vy = 0; break;
            case '>': vx = +1, vy = 0; break;
            case '^': vx = 0, vy = -1; break;
            case 'v': vx = 0, vy = +1; break;
        }
        if (move(*x, *y, vx, vy)) {
            *x += vx;
            *y += vy;
        }
    }
}

int main() {
    FILE *file = fopen("input.txt", "r");
    read_map_from_file(file);

    int x, y;
    find_initial_position(&x, &y);
    process_moves(file, &x, &y);

    long sum = calculate_sum();
    printf("Result: %li\n", sum);

    fclose(file);
    return 0;
}