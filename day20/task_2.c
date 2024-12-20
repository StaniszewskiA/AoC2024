#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX 143
#define THRESHOLD 100
#define CHEAT_LIMIT 20
#define FILEPATH "input.txt"

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

char grid[MAX][MAX];
unsigned int rows, cols;
int startRow, startCol, endRow, endCol;

int distStart[MAX][MAX];
int distEnd[MAX][MAX];

bool visited[MAX][MAX];
bool foundPaths[MAX][MAX][MAX][MAX];

typedef struct {
    unsigned int r, c;
} Point;

typedef struct {
    Point points[MAX * MAX];
    size_t size;
} Queue;

typedef struct {
    int r, c, steps;
} State;

typedef struct {
    State states[CHEAT_LIMIT * 4];
    int top;
} Stack;

bool is_valid(int r, int c) {
    return r >= 0 && r < rows && c >= 0 && c < cols;
}

void init_queue(Queue* q) {
    q->size = 0;
}

void q_push(Queue* q, int r, int c) {
    q->points[q->size++] = (Point){r, c};
}

Point q_pop(Queue* q) {
    return q->points[--q->size];
}

void calculate_dists(int dist[MAX][MAX], int startR, int startC) {
    Queue q;
    init_queue(&q);
    memset(dist, -1, sizeof(int) * MAX * MAX);
    dist[startR][startC] = 0;
    q_push(&q, startR, startC);

    while (q.size > 0) {
        Point curr = q_pop(&q);
        unsigned int distance = dist[curr.r][curr.c];

        for (int i = 0; i < 4; i++) {
            unsigned int newR = curr.r + dx[i];
            unsigned int newC = curr.c + dy[i];

            if (is_valid(newR, newC) && grid[newR][newC] == '.' && dist[newR][newC] == -1) {
                dist[newR][newC] = distance + 1;
                q_push(&q, newR, newC);
            }
        }
    }
}

void read_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    char line[MAX];
    int r = 0;

    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0; 
        strcpy(grid[r], line);

        for (int c = 0; c < strlen(line); c++) {
            if (grid[r][c] == 'S') {
                startRow = r; startCol = c;
                grid[r][c] = '.'; 
            }
            if (grid[r][c] == 'E') {
                endRow = r; endCol = c;
                grid[r][c] = '.'; 
            }
        }
        r++;
    }

    rows = r;
    cols = strlen(grid[0]);
    fclose(fp);
}

size_t find_paths() {
    size_t result = 0;
    memset(foundPaths, 0, sizeof(foundPaths));

    size_t time = distStart[endRow][endCol];

    for (int sr = 0; sr < rows; sr++) {
        for (int sc = 0; sc < cols; sc++) {
            if (grid[sr][sc] != '.' || distStart[sr][sc] == -1) continue;

            for (int er = 0; er < rows; er++) {
                for (int ec = 0; ec < cols; ec++) {
                    if (grid[er][ec] != '.' || distEnd[er][ec] == -1 || foundPaths[sr][sc][er][ec]) continue;

                    unsigned int manDist = abs(sr - er) + abs(sc - ec);
                    if (manDist > CHEAT_LIMIT) continue;

                    unsigned int cheatT = distStart[sr][sc] + manDist + distEnd[er][ec];
                    int cheat = time - cheatT;

                    if (cheat >= THRESHOLD) {
                        result++;
                        foundPaths[sr][sc][er][ec] = true;
                    }
                }
            }
        }
    }

    return result;
}

int main(int argc, char *argv[]) {
    read_file("input.txt");

    calculate_dists(distStart, startRow, startCol);
    calculate_dists(distEnd, endRow, endCol);

    size_t result = find_paths();
    printf("%d\n", result);

    return 0;
}
