#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_LEN 20000
#define BLOCK_CAPACITY 50

int* prepare_filesystem(const char* input, int* size) {
    int* blocks = NULL;
    int blocks_size = 0;
    int blocks_capacity = BLOCK_CAPACITY;
    int is_file = 1;
    int id = 0;

    blocks = (int*)malloc(blocks_capacity * sizeof(int));
    if (!blocks) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    for (size_t i = 0; input[i] != '\0'; ++i) {
        int count = input[i] - '0';

        while (blocks_size + count > blocks_capacity) {
            blocks_capacity *= 2;
            blocks = (int*)realloc(blocks, blocks_capacity * sizeof(int));
            if (!blocks) {
                fprintf(stderr, "Memory allocation failed.\n");
                exit(1);
            }
        }

        if (is_file) {
            for (int j = 0; j < count; ++j) {
                blocks[blocks_size++] = id;
            }
            ++id;
            is_file = 0;
        } else {
            for (int j = 0; j < count; ++j) {
                blocks[blocks_size++] = -1;
            }
            is_file = 1;
        }
    }

    *size = blocks_size;
    return blocks;
}

void compress(int* filesystem, int size) {
    int i = 0;
    while (filesystem[i] != -1) {
        ++i;
    }

    int j = size - 1;
    while (filesystem[j] == -1) {
        --j;
    }

    while (j > i) {
        filesystem[i] = filesystem[j];
        filesystem[j] = -1;

        while (j > 0 && filesystem[j] == -1) {
            --j;
        }
        while (i < size && filesystem[i] != -1) {
            ++i;
        }
    }
}

long long get_checksum(const int* filesystem, int size) {
    long long checksum = 0;

    for (int i = 0; i < size; i++) {
        if (filesystem[i] != -1) {
            checksum += i * filesystem[i];
        }
    }

    return checksum;
}

int main() {
    FILE* file = fopen("input.txt", "r");
    if (!file) {
        fprintf(stderr, "Failed to open input file.\n");
        return 1;
    }

    char input_data[INPUT_LEN];
    if (!fgets(input_data, sizeof(input_data), file)) {
        fprintf(stderr, "Failed to read input file.\n");
        fclose(file);
        return 1;
    }
    fclose(file);

    int filesystem_size;
    int* filesystem = prepare_filesystem(input_data, &filesystem_size);

    compress(filesystem, filesystem_size);
    printf("%lld\n", get_checksum(filesystem, filesystem_size));

    free(filesystem);
    return 0;
}