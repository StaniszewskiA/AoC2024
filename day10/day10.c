#include "day10.h"

int n; 
int dirs[4][2] = {  
    {-1, 0}, 
    {1, 0},  
    {0, -1}, 
    {0, 1}   
};
char grid[MAX_N][MAX_N]; 
int memo[MAX_N][MAX_N];

void stack_push(Stack *stack, int x, int y) {
    stack->data[++(stack->top)] = (Position){x, y};
}

Position stack_pop(Stack *stack) {
    return stack->data[(stack->top)--];
}

bool stack_is_empty(Stack *stack) {
    return stack->top == -1;
}

bool is_in_grid(int i, int j, int n) {
    return i >= 0 && i < n && j >= 0 && j < n;
}

int score(int i, int j) {
    if (grid[i][j] != '0')
        return 0;

    int result = 0;
    Stack stack = {.top = -1};
    stack_push(&stack, i, j);

    bool visited[MAX_N][MAX_N] = {false};

    while (!stack_is_empty(&stack)) {
        Position curr = stack_pop(&stack);

        if (visited[curr.x][curr.y])
            continue;

        visited[curr.x][curr.y] = true;
        int curr_val = grid[curr.x][curr.y] - '0';

        if (curr_val == 9) {
            result++;
            continue;
        }

        for (int d = 0; d < 4; d++) {
            int nei_x = curr.x + dirs[d][0];
            int nei_y = curr.y + dirs[d][1];

            if (is_in_grid(nei_x, nei_y, n) && !visited[nei_x][nei_y]) {
                int nei_val = grid[nei_x][nei_y] - '0';
                if (nei_val == curr_val + 1) {
                    stack_push(&stack, nei_x, nei_y);
                }
            }
        }
    }

    return result;
}

int rating(int i, int j) {
    if (memo[i][j] != -1) {
        return memo[i][j];
    }

    if (grid[i][j] == '9') {
        return memo[i][j] = 1;
    }

    int result = 0;

    for (int d = 0; d < 4; d++) {
        int ni = i + dirs[d][0];
        int nj = j + dirs[d][1];
        if (is_in_grid(ni, nj, n) && (grid[ni][nj] - '0') == (grid[i][j] - '0') + 1) {
            result += rating(ni, nj);
        }
    }

    return memo[i][j] = result;
}