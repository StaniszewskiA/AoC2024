#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_LEN 20000
#define BLOCKS_CAPACITY 50

int* loc;
int* size;

int* prepare_filesystem(const char* filesystem, int* size, int* num_ids) {
    int length = strlen(filesystem);
    loc = (int*)calloc(length, sizeof(int));
    size = (int*)calloc(length, sizeof(int));
    if (!loc || !size) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    int* blocks = NULL;
    int blocks_capacity = BLOCKS_CAPACITY;
    int blocks_count = 0;

    blocks = (int*)malloc(blocks_capacity * sizeof(int));
    if (!blocks) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    int is_file = 1;
    int id = 0;
    for (size_t i = 0; filesystem[i] != '\0'; ++i) {
        int x = filesystem[i] - '0';

        while (blocks_count + x > blocks_capacity) {
            blocks_capacity *= 2;
            blocks = (int*)realloc(blocks, blocks_capacity * sizeof(int));
            if (!blocks) {
                fprintf(stderr, "Memory allocation failed.\n");
                exit(1);
            }
        }

        if (is_file) {
            loc[id] = blocks_count;
            size[id] = x;for (int j = 0; j < x; ++j) {
                blocks[blocks_count++] = id;
            }
            ++id;
            is_file = 0;
        } else {
            for (int j = 0; j < x; ++j) {
                blocks[blocks_count++] = -1; 
            }
            is_file = 1;
        }
    }

    *size = blocks_count;
    *num_ids = id;
    return blocks;
}

void compress(int* filesystem, int filesystem_size, int num_ids) {
    for (int to_move = num_ids - 1; to_move >= 0; --to_move) {
        // Validate `to_move` index
        if (to_move < 0 || to_move >= num_ids) {
            fprintf(stderr, "Invalid file ID: %d\n", to_move);
            exit(EXIT_FAILURE);
        }

        int free_space = 0;
        int first_free = 0;

        while (first_free < loc[to_move] && free_space < size[to_move]) {
            first_free += free_space; 
            free_space = 0;

            while (first_free < filesystem_size && filesystem[first_free] != -1) {
                ++first_free;
            }

            while (first_free + free_space < filesystem_size && 
                   filesystem[first_free + free_space] == -1) {
                ++free_space;
            }

            if (free_space == 0 && first_free < loc[to_move]) {
                ++first_free;
            }
        }

        if (first_free >= loc[to_move]) {
            continue;
        }

        for (int idx = 0; idx < size[to_move]; ++idx) {
            int src_idx = loc[to_move] + idx;
            int dest_idx = first_free + idx;

            if (src_idx >= filesystem_size || dest_idx >= filesystem_size) {
                fprintf(stderr, "Out-of-bounds access detected: src_idx=%d, dest_idx=%d\n", src_idx, dest_idx);
                exit(EXIT_FAILURE);
            }

            filesystem[dest_idx] = to_move;  
            filesystem[src_idx] = -1;    
        }

        loc[to_move] = first_free;
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

    int blocks_size;
    int num_ids;
    int* filesystem = prepare_filesystem(input_data, &blocks_size, &num_ids);

    compress(filesystem, blocks_size, num_ids);
    printf("%lld\n", get_checksum(filesystem, blocks_size));

    free(filesystem);
    printf("DONE");
    return 0;
}