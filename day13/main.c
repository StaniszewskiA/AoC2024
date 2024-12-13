#include <stdio.h>
#include <stdlib.h>

#define FILEPATH "input.txt"
#define OFFSET 10000000000000LL

int is_solution_valid(
    long long int a, 
    long long int b, 
    long long int c,
    long long int d, 
    long long int e, 
    long long int f,
    long long int x, 
    long long int y
) {
    return (x >= 0 && y >= 0 && a * x + b * y == c && d * x + e * y == f);
}

int solve_equations(
    FILE* fin, 
    long long int* x, 
    long long int* y, 
    long long int* a, 
    long long int* b, 
    long long int* c, 
    long long int* d,
    long long int* e, 
    long long int* f
) {
    if (fscanf(fin, "Button A: X+%lld, Y+%lld\n", a, d) != 2) {
        return 0; 
    }
    fscanf(fin, "Button B: X+%lld, Y+%lld\n", b, e);
    fscanf(fin, "Prize: X=%lld, Y=%lld\n", c, f);

    *c += OFFSET;
    *f += OFFSET;

    long long int denominator = (*a * *e - *b * *d);
    *x = (*c * *e - *b * *f) / denominator;
    *y = (*a * *f - *c * *d) / denominator;

    return 1; 

}

void solve_task(FILE* fin) {
    long long int sum = 0; 
    long long int x, y;
    long long int a, b, c, d, e, f;

    while (solve_equations(fin, &x, &y, &a, &b, &c, &d, &e, &f)) {
        if (is_solution_valid(a, b, c, d, e, f, x, y)) {
            sum += 3 * x + y;
        }
    }

    fclose(fin);

    printf("%lld\n", sum);
}

int main() {
    FILE* fin = fopen(FILEPATH,"r");

    solve_task(fin);

    return 0;
}