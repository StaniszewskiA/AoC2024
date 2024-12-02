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

bool is_good_with_one_removed(int levels[], int length) {
    for (int i = 0; i < length; i++) {
        int new_levels[length - 1];
        int new_length = 0;
        
        for (int j = 0; j < length; j++) {
            if (j != i) {
                new_levels[new_length++] = levels[j];
            }
        }
        
        if (is_good(new_levels, new_length)) {
            return true;
        }
    }
    return false;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int p1 = 0, p2 = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (line[0] == '\n') {
            continue; 
        }

        int levels[REPORT_LENGTH];
        int length = 0;

        char *token = strtok(line, " \n");
        while (token != NULL) {
            levels[length++] = atoi(token);
            token = strtok(NULL, " \n");
        }

        if (is_good(levels, length)) {
            p1++;
        }

        if (is_good_with_one_removed(levels, length)) {
            p2++;
        }
    }

    fclose(file);

    printf("Number of good reports (p1): %d\n", p1);
    printf("Number of reports with one element removed that are good (p2): %d\n", p2);

    return 0;
}
