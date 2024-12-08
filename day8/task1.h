#ifndef TASK_1
#define TASK_1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ROWS 51
#define MAX_COLS 51
#define MAX_POINTS 2601

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point* points;  
    int size;       
    int capacity;   
} PointList;

bool is_in_bounds(int x, int y, int n, int m);
int get_antinodes_task_1(Point a, Point b, Point *antinodes, int n, int m);
int get_antinodes_task_2(Point a, Point b, Point *antinodes, int n, int m);
bool is_point_in_list(PointList *list, Point p);
void init_point_list(PointList* list);
void add_unique_point(PointList *list, Point p);
void task(const char grid[MAX_ROWS][MAX_COLS], int n, int m);

#endif