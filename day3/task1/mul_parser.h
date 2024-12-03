#ifndef MUL_PARSER_H
#define MUL_PRASER_H

int is_mul_instruction(const char *str, int index);
int extract_number(const char *str, int *idx);
void skip_invalid_chars(const char *str, int *idx);
int sum_mul(const char *corrupted_mem);

#endif