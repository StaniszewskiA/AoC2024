#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRETS_AMOUNT 2000
#define FILENAME "input.txt"
#define OFFSET 9
#define RANGE 19

int find_max_sum(int sums[RANGE][RANGE][RANGE][RANGE]) {
    int max_sum = 0;

    for (int a1 = -OFFSET; a1 <= OFFSET; a1++) {
        for (int a2 = -OFFSET; a2 <= OFFSET; a2++) {
            for (int a3 = -OFFSET; a3 <= OFFSET; a3++) {
                for (int a4 = -OFFSET; a4 <= OFFSET; a4++) {
                    int index1 = a1 + OFFSET, index2 = a2 + OFFSET;
                    int index3 = a3 + OFFSET, index4 = a4 + OFFSET;

                    if (sums[index1][index2][index3][index4] > max_sum) {
                        max_sum = sums[index1][index2][index3][index4];
                    }
                }
            }
        }
    }

    return max_sum;
}

int main() {
    FILE* fin = fopen(FILENAME, "r");

    long long secret, tmp, last_digit;
    int sums[RANGE][RANGE][RANGE][RANGE] = {0};

    while(fscanf(fin,"%lld",&secret) == 1) {
        last_digit = secret % 10;
        int a1 = -1, a2 = -1, a3 = -1, a4 = -1;
        char visited[RANGE][RANGE][RANGE][RANGE] = {0};

        for (int i = 0; i < SECRETS_AMOUNT; i++) {
            tmp = ((secret << 6) ^ secret) % 16777216;
            tmp = ((tmp >> 5) ^ tmp) % 16777216;
            tmp = ((tmp << 11) ^ tmp) % 16777216;

            a1 = a2;
            a2 = a3;
            a3 = a4;
            a4 = (tmp % 10) - last_digit;

            if (a1 != -1) {
                int index1 = a1 + OFFSET, index2 = a2 + OFFSET;
                int index3 = a3 + OFFSET, index4 = a4 + OFFSET;

                if (!visited[index1][index2][index3][index4]) {
                    visited[index1][index2][index3][index4] = 1;
                    sums[index1][index2][index3][index4] += (tmp % 10);
                }
            }

            last_digit = tmp % 10;
            secret = tmp;
        }
    }

    fclose(fin);

    int res = find_max_sum(sums);

    printf("%d\n", res);
    return 0;
}