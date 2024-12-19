#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_STRING_LENGTH 1000
#define MAX_PATTERN_LENGTH 1000
#define MAX_PATTERNS 1000
#define MAX_STRINGS 2000
#define FILENAME "input.txt"

typedef struct {
    char *patterns[MAX_PATTERNS];
    int count;
} PatternDict;

typedef struct {
    char *string;
    int match_count;
} SeenEntry;

SeenEntry seen_map[MAX_STRINGS];
int seen_map_size = 0;

void memoize_match(const char *string, int match_count);

void read_file(
    const char *filename, 
    PatternDict *pattern_dict,
    char strings[MAX_STRINGS][MAX_STRING_LENGTH],
    int *string_count    
) {
    FILE *fin = fopen(filename, "r");
    assert(fin != NULL && "File cannot be opened");

    char line[MAX_STRING_LENGTH];

    while (fgets(line, sizeof(line), fin)) {
        if (strcmp(line, "\n") == 0) {
            break;
        }

        char *pattern = strtok(line, ", ");
        while (pattern != NULL) {
            pattern_dict->patterns[pattern_dict->count++] = strdup(pattern);  
            pattern = strtok(NULL, ", ");
        }
    }

    while (fgets(line, sizeof(line), fin)) {
        line[strcspn(line, "\n")] = 0; 
        strcpy(strings[*string_count], line);
        (*string_count)++;
    }

    fclose(fin);
}

int compare_patterns(const void *a, const void *b) {
    return strlen(*(char **)a) - strlen(*(char **)b);
}

int get_seen_match_count(const char *string) {
    for (int i = 0; i < seen_map_size; i++) {
        if (strcmp(seen_map[i].string, string) == 0) {
            return seen_map[i].match_count;
        }
    }

    return -1;
}

int match(const char *string, PatternDict *pattern_dict) {
    int seen_count = get_seen_match_count(string);
    if (seen_count != -1) {
        return seen_count;
    }

    if (string[0] == '\0') {
        memoize_match(string, 0);
        return 0;
    }

    int total_matches = 0;
    char first_char = string[0];

    for (int i = 0; i < pattern_dict->count; i++) {
        char *pattern = pattern_dict->patterns[i];
        if (pattern[0] == first_char) {
            int pattern_len = strlen(pattern);
            if (pattern_len == 1 || strncmp(string, pattern, pattern_len) == 0) {
                if (strlen(string) == pattern_len) {
                    total_matches++;
                    break;
                }
                total_matches += match(string + pattern_len, pattern_dict);
            }
        }
    }

    memoize_match(string, total_matches);
    return total_matches;
}

void memoize_match(const char *string, int match_count) {
    if (seen_map_size >= MAX_STRINGS) {
        fprintf(stderr, "Error: Seen map size exceeded the maximum limit (%d).\n", MAX_STRINGS);
        exit(1);  
    }

    seen_map[seen_map_size].string = strdup(string);
    seen_map[seen_map_size].match_count = match_count;
    seen_map_size++;
}

void free_seen_map() {
    for (int i = 0; i < seen_map_size; i++) {
        free(seen_map[i].string);
    }
}

int main() {
    PatternDict pattern_dict = { .count = 0 };
    char strings[MAX_STRINGS][MAX_STRING_LENGTH];
    int string_count = 0;

    read_file(FILENAME, &pattern_dict, strings, &string_count);
    printf("File read! %d strings found.\n", string_count);

    qsort(pattern_dict.patterns, pattern_dict.count, sizeof(char *), compare_patterns);
    printf("Patterns sorted!\n");

    int result = 0;
    for (int i = 0; i < string_count; i++) {
        printf("Processing string %d of %d\n", i + 1, string_count);
        if (match(strings[i], &pattern_dict) > 0) {
            result++;
        }
    }

    printf("Total strings with matches: %d\n", result);
    for (int i = 0; i < pattern_dict.count; i++) {
        free(pattern_dict.patterns[i]);
    }
    free_seen_map();

    return 0;
}