#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define INPUT

#ifdef INPUT
#define FILENAME "input.txt"
#define SIZE 141
#endif

// Directions
enum {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

typedef struct {
    int row, col, direction, score;
} Move;

typedef struct {
    Move* data;
    int size, capacity;
} MinHeap;

void parseInput(FILE* fin, char map[SIZE][SIZE], int* s_row, int* s_col);
MinHeap* createHeap(int capacity);
void heapPush(MinHeap* heap, Move move);
Move heapPop(MinHeap* heap);
int isHeapEmpty(MinHeap* heap);
int mod(int a, int b);
int isValid(int row, int col);
int dijkstra(char map[SIZE][SIZE], int s_row, int s_col);
void backtrack_shortest_paths(
    char map[SIZE][SIZE], 
    int visited[SIZE][SIZE], 
    int start[2], 
    int end[2], 
    int rows, 
    int cols
);

char map[SIZE][SIZE];
int minDist[SIZE][SIZE][4];
int prev[SIZE][SIZE][4];

int main() {
    FILE* fin = fopen(FILENAME, "r");
    printf("File opened! \n");

    char map[SIZE][SIZE];
    int s_row, s_col;

    parseInput(fin, map, &s_row, &s_col);
    printf("Input parsed! \n");

    fclose(fin);

    int score = dijkstra(map, s_row, s_col);
    printf("%d\n", score);
    
    return EXIT_SUCCESS;
}

int dijkstra(char map[SIZE][SIZE], int s_row, int s_col) {
    int minDist[SIZE][SIZE][4];
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            for (int dir = 0; dir < 4; dir++) {
                minDist[row][col][dir] = INT_MAX;
                prev[row][col][dir] = -1;
            }
        }
    }

    MinHeap* heap = createHeap(SIZE * SIZE * 4);
    heapPush(heap, (Move){s_row, s_col, EAST, 0});

    int score = -1;

    while (!isHeapEmpty(heap)) {
        Move bestMove = heapPop(heap);
        int r = bestMove.row, c = bestMove.col, direction = bestMove.direction, currentScore = bestMove.score;
        if (map[r][c] == 'E') {
            score = currentScore;
            break;
        }

        if (map[r][c] == '#' || currentScore >= minDist[r][c][direction]) {
            continue;
        }

        minDist[r][c][direction] = currentScore;
        prev[r][c][direction] = bestMove.direction;

        heapPush(heap, (Move){r, c, mod(direction + 1, 4), currentScore + 1000});
        heapPush(heap, (Move){r, c, mod(direction - 1, 4), currentScore + 1000});

        if (direction == NORTH && isValid(r - 1, c)) {
            heapPush(heap, (Move){r - 1, c, direction, currentScore + 1});
        } else if (direction == EAST && isValid(r, c + 1)) {
            heapPush(heap, (Move){r, c + 1, direction, currentScore + 1});
        } else if (direction == SOUTH && isValid(r + 1, c)) {
            heapPush(heap, (Move){r + 1, c, direction, currentScore + 1});
        } else if (direction == WEST && isValid(r, c - 1)) {
            heapPush(heap, (Move){r, c - 1, direction, currentScore + 1});
        }
    }

    free(heap->data);
    free(heap);

    return score;
}

void parseInput(FILE* fin, char map[SIZE][SIZE], int* s_row, int* s_col) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            fscanf(fin, "%c ", &map[row][col]);
            if (map[row][col] == 'S') {
                *s_row = row;
                *s_col = col;
            }
        }
    }
}

MinHeap* createHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (Move*)malloc(sizeof(Move) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void heapPush(MinHeap* heap, Move move) {
    if (heap->size >= heap->capacity) return;

    heap->data[heap->size++] = move;
    int i = heap->size - 1;

    while (i > 0 && heap->data[i].score < heap->data[(i - 1) / 2].score) {
        Move temp = heap->data[i];
        heap->data[i] = heap->data[(i - 1) / 2];
        heap->data[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

Move heapPop(MinHeap* heap) {
    if (heap->size == 0) return (Move){-1, -1, -1, -1};

    Move root = heap->data[0];
    heap->data[0] = heap->data[--heap->size];

    int i = 0;
    while (1) {
        int smallest = i;
        int left = 2 * i + 1, right = 2 * i + 2;

        if (left < heap->size && heap->data[left].score < heap->data[smallest].score) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right].score < heap->data[smallest].score) {
            smallest = right;
        }
        if (smallest == i) break;

        Move temp = heap->data[i];
        heap->data[i] = heap->data[smallest];
        heap->data[smallest] = temp;

        i = smallest;
    }

    return root;
}

int isHeapEmpty(MinHeap* heap) {
    return heap->size == 0;
}

int mod(int a, int b) {
    int result = a % b;
    if (result < 0) result += b;
    return result;
}


int isValid(int row, int col) {
    return row >= 0 && row < SIZE && col >= 0 && col < SIZE;
}