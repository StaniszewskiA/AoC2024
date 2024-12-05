#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "update_validator.h"

char** split(char* str, const char* delimiter, int* count) {
    char** result = malloc(MAX_PAGES * sizeof(char*));
    char* token = strtok(str, delimiter);
    *count = 0;

    while (token != NULL) {
        result[*count] = malloc(strlen(token) + 1); 
        strcpy(result[*count], token);
        (*count)++;
        token = strtok(NULL, delimiter);
    } 

    return result;
}

void process_input(
    const char* file_path,
    char rules[MAX_RULES][MAX_RULE_LEN],
    int* rule_count,
    int updates[MAX_UPDATES][MAX_PAGES],
    int* update_size,
    int* update_count
) {
    FILE* file = fopen(file_path, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    int section = 0;
    *rule_count = 0;
    *update_count = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strcmp(line, "\n") == 0) {
            section++;
            continue;
        } 

        if (section == 0) {
            strcpy(rules[(*rule_count)++], strtok(line, "\n"));
        } else if (section == 1) {
            int count;
            char** pages = split(line, ",", &count);
            for (int i = 0; i < count; i++) {
                updates[*update_count][i] = atoi(pages[i]);
            }
            update_size[(*update_count)++] = count;
            free(pages);
        }
    }

    fclose(file);
}

int is_in_valid_order(
    int* update,
    int update_size, 
    char rules[MAX_RULES][MAX_RULE_LEN], 
    int rule_count
) {
    int position[MAX_PAGES] = {0};

    for (int i = 0; i < update_size; i++) {
        position[update[i]] = i;
    }

    for (int i = 0; i < rule_count; i++) {
        int x, y;
        sscanf(rules[i], "%d|%d", &x, &y);
        if (position[x] != 0 && position[y] != 0) {
            if (position[x] > position[y]) {
                return 0;
            }
        }
    }

    return 1;
}

int get_middle_page(int* update, int update_size) {
    return update[update_size / 2];
}