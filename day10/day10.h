#ifndef GRID_RATING_H
#define GRID_RATING_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_N 50
#define STACK_SIZE 10000

typedef struct {
    int x, y;
} Position;

typedef struct {
    Position data[STACK_SIZE];
    int top;
} Stack;

extern int n;
extern int dirs[4][2];
extern char grid[MAX_N][MAX_N];
extern int memo[MAX_N][MAX_N];

void stack_push(Stack *stack, int x, int y);
Position stack_pop(Stack *stack);
bool stack_is_empty(Stack *stack);

bool is_in_grid(int i, int j, int n);

int score(int i, int j);
int rating(int i, int j);

#endif 
