#include "task1.h"

bool is_in_bounds(int x, int y, int n, int m) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int get_antinodes_task_1(Point a, Point b, Point *antinodes, int n, int m) {
    int count = 0;

    int cx = a.x - (b.x - a.x);
    int cy = a.y - (b.y - a.y);

    int dx = a.x + (b.x - a.x);
    int dy = a.y + (b.y - a.y);

    if (is_in_bounds(cx, cy, n, m)) {
        antinodes[count++] = (Point){cx, cy};
    }

    if (is_in_bounds(dx, dy, n, m)) {
        antinodes[count++] = (Point){dx, dy};
    }

    return count;
}

int get_antinodes_task_2(Point a, Point b, Point *antinodes, int n, int m) {
    int count = 0;

    int delta_x = b.x - a.x;
    int delta_y = b.y - a.y;

    int i = 0;
    while (1) {
        int cx = a.x - delta_x * i;
        int cy = a.y - delta_y * i;
        if (is_in_bounds(cx, cy, n, m)) {
            antinodes[count++] = (Point){cx, cy};
        } else {
            break;
        }
        i++;
    }

    i = 0;
    while (1) {
        int dx = b.x + delta_x * i;
        int dy = b.y + delta_y * i;
        if (is_in_bounds(dx, dy, n, m)) {
            antinodes[count++] = (Point){dx, dy};
        } else {
            break;
        }
        i++;
    }

    return count;
}


bool is_point_in_list(PointList *list, Point p) {
    for (int i = 0; i < list -> size; i++) {
        if (list -> points[i].x == p.x && list -> points[i].y == p.y) {
            return true;
        }
    }

    return false;
}

void init_point_list(PointList* list) {
    list->points = (Point*)malloc(MAX_POINTS * sizeof(Point)); 
    list->size = 0;
    list->capacity = MAX_POINTS;
}

void add_unique_point(PointList* list, Point p) {
    for (int i = 0; i < list->size; i++) {
        if (list->points[i].x == p.x && list->points[i].y == p.y) { 
            return;
        }
    }
    if (list->size >= list->capacity) {
        list->capacity *= 2;  
        list->points = (Point*)realloc(list->points, list->capacity * sizeof(Point));  
    }
    list->points[list->size++] = p;  
}


void task(const char grid[MAX_ROWS][MAX_COLS], int n, int m) {
    PointList all_locs[256] = {0};
    PointList antinodes_1 = {0};
    PointList antinodes_2 = {0};

    for (int i = 0; i < 256; i++) {
        init_point_list(&all_locs[i]);
    }

    init_point_list(&antinodes_1);
    init_point_list(&antinodes_2);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            unsigned char c = grid[i][j];
            
            if (c != '.') {
                Point p = {i, j};
                add_unique_point(&all_locs[(unsigned char)c], p);     
            }
        }
    }

    for (int i = 0; i < 256; i++) {
        if (all_locs[i].size > 1) {
            PointList *locs = &all_locs[i];
            for (int j = 0; j < locs->size; j++) {
                for (int k = j + 1; k < locs->size; k++) {
                    Point a = locs->points[j];
                    Point b = locs->points[k];
                    Point generated_antinodes_1[2];
                    Point generated_antinodes_2[2];
                    int count_1 = get_antinodes_task_1(a, b, generated_antinodes_1, n, m);
                    int count_2 = get_antinodes_task_2(a, b, generated_antinodes_2, n, m);
                    for (int l = 0; l < count_1; l++) {
                        add_unique_point(&antinodes_1, generated_antinodes_1[l]);
                    }
                    for (int l = 0; l < count_2; l++) {
                        add_unique_point(&antinodes_2, generated_antinodes_2[l]);
                    }
                }
            }
        }
    }

    printf("%d\n", antinodes_1.size);
    printf("%d\n", antinodes_2.size);
}