#ifndef SAFETY_CHECKER_H
#define SAFETY_CHECKER_H

#include <stdbool.h>

bool is_safe(int levels[], int length);
bool is_good_with_one_removed(int levels[], int length);

#endif