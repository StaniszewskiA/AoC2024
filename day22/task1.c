#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRETS_AMOUNT 2000
#define FILENAME "input.txt"

int main() {
    FILE* fin = fopen(FILENAME, "r");

    long long secret;
    long long tmp;
    long long res = 0;

    while(fscanf(fin, "%lld", &secret) == 1) {
        for (int i = 0; i < SECRETS_AMOUNT; i++) {
            tmp = ((secret << 6) ^ secret) % 16777216;
            tmp = ((tmp >> 5) ^ tmp) % 16777216;
            tmp = ((tmp << 11) ^ tmp) % 16777216;

            secret = tmp;
        }
        res += secret;
    }

    fclose(fin);
    printf("%lld\n", res);

    return 0;
}
