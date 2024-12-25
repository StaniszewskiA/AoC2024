#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define PATTERNS 1000
#define PATTERN_WIDTH 5
#define FILENAME "input.txt"

void parse(
    char pattern[][PATTERN_WIDTH + 2],
    int rows,
    int *array,
    int *count
);
int readFile(
    const char* filename,
    int *locks,
    int *keys,
    int *lockCount,
    int *keyCount
);
unsigned int count_fits(
    int *locks, 
    int *keys, 
    int lockCount, 
    int keyCount
);

int main() {

    int locks[PATTERNS * PATTERN_WIDTH] = {0};
    int keys[PATTERNS * PATTERN_WIDTH] = {0};
    int lockCount = 0;
    int keyCount = 0;
    
    readFile(FILENAME, locks, keys, &lockCount, &keyCount);
    unsigned int res = count_fits(locks, keys, lockCount, keyCount);

    printf("%d\n", res);
    return 0;
}

void parse(
    char pattern[][PATTERN_WIDTH + 2],
    int rows,
    int *array,
    int *count
) {
    for (int col = 0; col < PATTERN_WIDTH; col++) {
        unsigned int sum = 0;

        for (int row = 0; row < rows; row++) {
            if (pattern[row][col] == '#') {
                sum++;
            }
        }

        array[(*count) * PATTERN_WIDTH + col] = sum - 1;
    }
    (*count)++;
}

int readFile(
    const char* filename,
    int *locks,
    int *keys,
    int *lockCount,
    int *keyCount
) {
    FILE *fin = fopen(FILENAME, "r");
    char pattern[10][PATTERN_WIDTH + 2] = {0};
    int patternRow = 0;
    char line[PATTERN_WIDTH + 2];

    while (fgets(line, sizeof(line), fin)) {
        if (line[0] == '\n' || line[0] == '\r' || line[0] == '\0') {
            if (patternRow > 0) {
                if (pattern[0][0] == '#') {
                    parse(pattern, patternRow, locks, lockCount);
                } else {
                    parse(pattern, patternRow, keys, keyCount);
                }
            }
            patternRow = 0;
            memset(pattern, 0, sizeof(pattern));
            continue;
        }
        strncpy(pattern[patternRow], line, PATTERN_WIDTH + 1);
        patternRow++;
    }

    if (patternRow > 0) {
        if (pattern[0][0] == '#') {
            parse(pattern, patternRow, locks, lockCount);
        } else {
            parse(pattern, patternRow, keys, keyCount);
        }
    }

    fclose(fin);
}

unsigned int count_fits(
    int *locks, 
    int *keys, 
    int lockCount, int keyCount
) {
    unsigned int res = 0;

    for (int i = 0; i < lockCount; i++) {
        for (int j = 0; j < keyCount; j++) {
            bool fits = true;
            for (int k = 0; k < PATTERN_WIDTH; k++) {
                if (locks[i * PATTERN_WIDTH + k] + keys[j * PATTERN_WIDTH + k] > 5) {
                    fits = false;
                    break;
                }
            }
            if (fits) {
                res++;
            }
        }
    }

    return res;
}