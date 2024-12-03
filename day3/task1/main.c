#include <stdio.h>
#include <stdlib.h>
#include "mul_parser.h"

#define MAX_LENGTH 100000

int main() {
    FILE *file;
    char corrupted_mem[MAX_LENGTH];

    file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Unable to open file");
        return 1;
    }

    fgets(corrupted_mem, MAX_LENGTH, file);
    fclose(file);

    int result = sum_mul(corrupted_mem);
    printf("The total sum is: %d\n", result);
    
    return 0;
}