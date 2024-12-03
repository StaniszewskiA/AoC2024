#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "mul_parser.h"

#define MAX_LENGTH 1000 

int is_mul_instruction(const char *str, int index) {
    return str[index] == 'm' && str[index + 1] == 'u' &&
           str[index + 2] == 'l' && str[index + 3] == '(';
}

int extract_number(const char *str, int *index) {
    int num = 0;
    
    while (isdigit(str[*index])) {
        num = num * 10 + (str[*index] - '0');
        (*index)++;
    }
    
    return num;
}

void skip_invalid_characters(const char *str, int *index) {
    while (str[*index] != '\0' && !isdigit(str[*index]) && str[*index] != ',' && str[*index] != ')' && str[*index] != '\n') {
        (*index)++;
    }
}

int sum_mul(const char *corrupted_memory) {
    int total_sum = 0;
    int i = 0;
    int x, y;

    while (corrupted_memory[i] != '\0') {
        if (is_mul_instruction(corrupted_memory, i)) {
            i += 4;  
            
            x = extract_number(corrupted_memory, &i);
            skip_invalid_characters(corrupted_memory, &i);
            
            if (corrupted_memory[i] == ',') {
                i++;

                y = extract_number(corrupted_memory, &i);
                skip_invalid_characters(corrupted_memory, &i);

                if (corrupted_memory[i] == ')') {
                    printf("Multiplying %d * %d\n", x, y);
                    total_sum += x * y;
                }
            }
        } else {
            i++;
        }
    }
    
    return total_sum;
}
