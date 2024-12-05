#ifndef UPDATE_VALIDATOR_H
#define UPDATE_VALIDATOR_H

#define MAX_RULES 1200
#define MAX_RULE_LEN 10 
#define MAX_UPDATES 300
#define MAX_PAGES 200

char** split(char* str, const char* delimiter, int* count);

void process_input(
    const char* file_path,
    char rules[MAX_RULES][MAX_RULE_LEN],
    int* rule_count,
    int updates[MAX_UPDATES][MAX_PAGES],
    int* update_size,
    int* update_count
);

int is_in_valid_order(
    int* update,
    int update_size, 
    char rules[MAX_RULES][MAX_RULE_LEN], 
    int rule_count
);

int get_middle_page(int* update, int update_size);

#endif
