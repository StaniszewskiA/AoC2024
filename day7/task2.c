#include "task2.h"

int test_combos_task_2(
    long long *nums,
    int num_count,
    long long target,
    int index,
    long long result
) {
    if (index == num_count) {
        return result == target;
    }

    if (test_combos_task_2(
        nums,
        num_count,
        target,
        index + 1,
        result + nums[index]
    )) {
        return 1;
    }

    if (test_combos_task_2(
        nums,
        num_count,
        target,
        index + 1,
        result * nums[index]
    )) {
        return 1;
    }

    char result_str[100], num_str[20];
    sprintf(result_str, "%lld", result);
    sprintf(num_str, "%lld", nums[index]);
    strcat(result_str, num_str);
    long long concat_result = atoll(result_str);

    if (test_combos_task_2(nums, num_count, target, index + 1, concat_result)) {
        return 1;
    }


    return 0;
}

void task_2(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (!file) {
        perror("Error opening file");
    }

    char line[256];
    long long result = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "n")] = '\0';

        char *token = strtok(line, " ");
        long long target = atoll(token);

        long long nums[100];
        int num_count = 0;
        while ((token = strtok(NULL, " ")) != NULL) {
            nums[num_count++] = atoll(token);
        }

        if (test_combos_task_2(nums, num_count, target, 1, nums[0])) {
            result += target;
        }
    }

    fclose(file);
    printf("%lld\n", result);
}