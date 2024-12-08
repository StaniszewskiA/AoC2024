#include "task1.h"

int main() {
    char input_data[MAX_ROWS][MAX_COLS];
    int rows = 0, cols = 0;

    FILE *file = fopen("input.txt", "r");
    if (!file) {
        perror("Unable to open the file");
        return EXIT_FAILURE;
    }

    while (rows < MAX_ROWS - 1 && fgets(input_data[rows], MAX_COLS, file)) {
        char *newline = strchr(input_data[rows], '\n');
        if (newline) *newline = '\0';
        input_data[rows][MAX_COLS - 1] = '\0'; 
        rows++;
    }
    fclose(file);

    cols = strlen(input_data[0]);

    task(input_data, rows, cols);

    return 0;
}
