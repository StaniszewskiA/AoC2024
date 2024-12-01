#include <stdio.h>
#include "reconcile.h"

int calculate_sim_score(int left_list[], int right_list[], int size) {
    int sim_score = 0;

    for (int i = 0; i < size; i++) {
        int count = 0;

        for (int j = 0; j < size; j++) {
            if (left_list[i] == right_list[j]) {
                count++;
            }
        }

        sim_score += left_list[i] * count;
    }

    return sim_score;

    return sim_score;
}