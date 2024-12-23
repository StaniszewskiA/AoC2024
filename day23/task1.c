#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define ALPHABET 26
#define FILENAME "input.txt"

int adj_mat[ALPHABET * ALPHABET][ALPHABET * ALPHABET];
int t_lists[ALPHABET][ALPHABET * ALPHABET];
int t_list_len[ALPHABET] = {0};

int compute_result();
void read_input();

int main() {
    read_input();

    int result = compute_result();

    printf("%d\n", result);
    return 0;
}

int compute_result() {
    int result = 0;

    for (int i = 0; i < ALPHABET; i++) {
        for (int j = 0; j < t_list_len[i]; j++) {
            for (int k = j + 1; k < t_list_len[i]; k++) {
                int idx1 = t_lists[i][j];
                int idx2 = t_lists[i][k];

                if ((idx1 / ALPHABET == 't' - 'a' && idx1 % ALPHABET < i) || 
                    (idx2 / ALPHABET == 't' - 'a' && idx2 % ALPHABET < i)) {
                    continue;
                }

                if (adj_mat[idx1][idx2]) {
                    result++;
                }
            }
        }
    }

    return result;
}

void read_input() {
    FILE *fin = fopen(FILENAME, "r");
    while (1) {
        char label1[2];
        char label2[2];
        if (fscanf(fin, "%2c-%2c ", label1, label2) != 2) {
            break;  
        }

        int idx1 = ALPHABET * (label1[0] - 'a') + (label1[1] - 'a');
        int idx2 = ALPHABET * (label2[0] - 'a') + (label2[1] - 'a');

        adj_mat[idx1][idx2] = 1;
        adj_mat[idx2][idx1] = 1;

        if (label1[0] == 't') {
            t_lists[idx1 % ALPHABET][t_list_len[idx1 % ALPHABET]++] = idx2;
        }
        if (label2[0] == 't') {
            t_lists[idx2 % ALPHABET][t_list_len[idx2 % ALPHABET]++] = idx1;
        }
    }
}