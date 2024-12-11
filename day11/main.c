#include <stdio.h>
#include <stdlib.h>
#include "solver.h"

#define FILEPATH "input.txt"
#define ITERS_ONE 25
#define ITERS_TWO 75

int main() {
    int size;
    int* stones = parse_input(FILEPATH, &size);

    int result = solve(stones, size, ITERS_ONE);
    printf("%d\n", result);

    free(stones);
    return 0;
}
