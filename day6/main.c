#include "task1.h"
#include "task2.h"

int main() {
    char input_data[MAX_ROWS][MAX_ROWS];
    int rows = 0, cols = 0;

    FILE *file = fopen("input.txt", "r");
    if (!file) {
        perror("Unable to open the file");
        return EXIT_FAILURE;
    }

    while (fgets(input_data[rows], MAX_COLS, file)) {
        char *newline = strchr(input_data[rows], '\n');
        if (newline) *newline = '\0';
        
        rows++;
    }
    fclose(file);

    cols = strlen(input_data[0]);

    task1(input_data, rows, cols);
    task2(input_data, rows, cols);

    return EXIT_SUCCESS;
}