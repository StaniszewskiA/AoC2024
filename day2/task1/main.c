#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define REPORT_LENGTH 1001
#define MAX_LINE_LENGTH 1024

bool is_good(int levels[], int length) {
    bool inc_or_dec = true;

    for (int i = 0; i < length - 1; i++) {
        if (levels[i] > levels[i + 1]) {
            inc_or_dec = false;
            break;
        }
    }
    if (!inc_or_dec) {
        for (int i = 0; i < length - 1; i++) {
            if (levels[i] < levels[i + 1]) {
                inc_or_dec = false;
                break;
            }
        }
    }

    bool ok = true;
    for (int i = 0; i < length - 1; i++) {
        int diff = abs(levels[i] - levels[i + 1]);
        if (diff < 1 || diff > 3) {
            ok = false;
            break;
        }
    }

    return inc_or_dec && ok;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int p1 = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (line[0] == '\n') {
            continue;  // Skip empty lines
        }

        int levels[REPORT_LENGTH];
        int length = 0;

        // Tokenize the line to extract the levels
        char *token = strtok(line, " \n");
        while (token != NULL) {
            levels[length++] = atoi(token);
            token = strtok(NULL, " \n");
        }

        // Check if the sequence is good
        if (is_good(levels, length)) {
            p1++;
        }
    }

    fclose(file);

    // Output the result
    printf("Number of good reports (p1): %d\n", p1);

    return 0;
}
