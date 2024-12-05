#include <stdio.h>
#include <stdlib.h>
#include "update_validator.h"

int main() {
    const char* file_path = "input.txt";
    char rules[MAX_RULES][MAX_RULE_LEN];
    int updates[MAX_UPDATES][MAX_PAGES];
    int update_size[MAX_UPDATES];
    int rule_count, update_count;

    process_input(file_path, rules, &rule_count, updates, update_size, &update_count);

    int middle_page_sum = 0;

    for (int i = 0; i < update_count; i++) {
        if (is_in_valid_order(updates[i], update_size[i], rules, rule_count)) {
            middle_page_sum += get_middle_page(updates[i], update_size[i]);
        }
    }

    printf("%d\n", middle_page_sum);
    return 0;
}
