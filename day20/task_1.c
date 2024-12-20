#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 150
#define THRESHOLD 100
#define FILENAME "input.txt"

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

char grid[MAX][MAX];
unsigned int rows, cols;
int startR, startC, endR, endC;
int distStart[MAX][MAX];
int distEnd[MAX][MAX];

typedef struct {
    unsigned int r, c;
} Point;

typedef struct {
    Point points[MAX * MAX];
    size_t size;
} Queue;

bool is_valid(int r, int c) {
    return r >= 0 && 
        r < rows && 
        c >= 0 && 
        c < cols;
}

void init_queue(Queue *q) {
    q->size = 0;
}

void q_push(Queue *q, int r, int c) {
    q->points[q->size++] = (Point){r, c};
}

Point q_pop(Queue *q) {
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
        int distance = dist[curr.r][curr.c];

        for (int i = 0; i < 4; i++) {
            int newR = curr.r + dx[i];
            int newC = curr.c + dy[i];

            if (is_valid(newR, newC) && grid[newR][newC] == '.' && dist[newR][newC] == -1) {
                dist[newR][newC] = distance + 1;
                q_push(&q, newR, newC);
            }
        }
    }
}

bool check_cheat(int startR, int startC, int midR, int midC, int newEndR, int newEndC, int time, size_t *res) {
    if (grid[midR][midC] == '.' ||
        (startC < endC && newEndC > endC) ||
        (startC > endC && newEndC < endC) ||
        (startR > endR && newEndR < endR) ||
        (startR < endR && newEndR > endR)) {
        return false;
    }

    int cheatT = distStart[startR][startC] + 2 + distEnd[newEndR][newEndC];
    int cheat = time - cheatT;

    if (cheat >= THRESHOLD) {
        (*res)++;
        return true;
    }

    return false;
}

void read_file(char *filename) {
    FILE *fp = fopen(filename, "r");

    char line[MAX];
    int r = 0;
    
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0; 
        strcpy(grid[r], line);
        
        r++;
    }

    rows = r;
    cols = strlen(grid[0]);
    fclose(fp);
}

void find_start_end() {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 'S') {
                startR = r; startC = c;
                grid[r][c] = '.';
            }
            if (grid[r][c] == 'E') {
                endR = r; endC = c;
                grid[r][c] = '.';
            }
        }
    }
}

int main() {
    read_file(FILENAME);
    find_start_end();

    calculate_dists(distStart, startR, startC);
    calculate_dists(distEnd, endR, endC);

    size_t time = distStart[endR][endC];
    size_t res = 0;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] != '.' || distStart[r][c] == -1) continue;

            for (int d1 = 0; d1 < 4; d1++) {
                int midR = r + dx[d1];
                int midC = c + dy[d1];

                if (!is_valid(midR, midC) || grid[midR][midC] != '#') continue;

                for (int d2 = 0; d2 < 4; d2++) {
                    int newEndR = midR + dx[d2];
                    int newEndC = midC + dy[d2];

                    if (!is_valid(newEndR, newEndC) || grid[newEndR][newEndC] != '.' || distEnd[newEndR][newEndC] == -1) continue;

                    check_cheat(r, c, midR, midC, newEndR, newEndC, time, &res);
                }
            }
        }
    }

    printf("%d\n", res);
    return 0;
}
