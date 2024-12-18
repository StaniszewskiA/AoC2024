#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define KILOBYTE 1024
#define MAX_Q_SIZE 10000
#define FILENAME "input.txt"

typedef struct {
    int32_t x;
    int32_t y;
} Position;

typedef struct {
    Position position;
} Byte;

typedef enum {
    HEALTHY = 0,
    CORRUPTED,
    FLOODED,
    VISITED,
} State;

typedef struct {
    State state;
    int32_t score;
} Register;

typedef struct {
    Register* registers;
    int32_t count;
    int32_t size_x;
    int32_t size_y;
} Memory;

static int8_t is_position_equal(Position* p1, Position* p2) {
    return (p1->x == p2->x && p1->y == p2->y);
}

static int8_t mem_in_map(Memory* memory, Position* position) 
{
    return (position->x >= 0 && position->x < memory->size_x &&
            position->y >= 0 && position->y < memory->size_y);
}

static Register* mem_get_reg(Memory* memory, Position* position)
{
    int32_t index = position->y * memory->size_x + position->x;
    return &memory->registers[index];
}

static int32_t get_bytes(char* file_name, Byte* bytes, int32_t bytes_size) {
    FILE* fin = fopen(file_name, "r");

    int32_t bytes_count = 0;
    while (fscanf(fin, "%d,%d\n", &bytes[bytes_count].position.x, &bytes[bytes_count].position.y) == 2) {
        bytes_count++;
        if (bytes_count == bytes_size) {
            printf("Bytes array size reached!\n");
            fclose(fin);
            return -1;
        }
    }

    return bytes_count;
}

static Memory get_map(char* file_name)
{
    Memory memory;
    memory.size_x = 70 + 1;
    memory.size_y = 70 + 1;

    memory.count = memory.size_x * memory.size_y;
    memory.registers = (Register*)malloc(sizeof(Register) * memory.count);

    for (int32_t i = 0; i < memory.count; i++) {
        Register* reg = &memory.registers[i];
        reg->state = HEALTHY;
        reg->score = 0;
    }

    return memory;
}

static void mem_fall_bytes(Memory* memory, Byte* bytes, int32_t bytes_count)
{
    for (int32_t i = 0; i < bytes_count; i++) {
        Register* reg = mem_get_reg(memory, &bytes[i].position);
        reg->state = CORRUPTED;
    }
}

static int32_t dfs_flood(Memory* memory, int8_t task_num) 
{
    const int8_t x_dir[4] = {0, 1, 0, -1};
    const int8_t y_dir[4] = {1, 0, -1, 0};

    Position start = (Position){0, 0};
    Position finish = (Position){memory->size_x - 1, memory->size_y - 1};

    Position queue[MAX_Q_SIZE];
    int32_t queue_size = sizeof(queue) / sizeof(Position);
    int32_t write_ptr = 0;
    int32_t read_ptr = 0;

    queue[write_ptr] = start;
    write_ptr = (write_ptr + 1) % queue_size;

    while (write_ptr != read_ptr) {
        Position* position = &queue[read_ptr];
        read_ptr = (read_ptr + 1) % queue_size;
        Register* reg = mem_get_reg(memory, position);
        reg->state = FLOODED;

        for (int8_t i=0; i<4; i++) {
            Position next_position;
            next_position.x = position->x + x_dir[i];
            next_position.y = position->y + y_dir[i];   
            Register* next_reg = mem_get_reg(memory, &next_position);

            if (next_reg->state != HEALTHY)
                continue;

            if (mem_in_map(memory, &next_position) == 0)
                continue;

            next_reg->state = FLOODED;
            next_reg->score = reg->score + 1;
            queue[write_ptr] = next_position;
            write_ptr = (write_ptr + 1) % queue_size;
            if (write_ptr == read_ptr) {
                return 0;
            }
        }
    }

    if (task_num == 2)
    {
        return mem_get_reg(memory, &finish)->state == FLOODED;
    }

    int32_t step_count = 0;
    Position crawler = finish;
    while (is_position_equal(&crawler, &start) == 0) {
        Register* reg = mem_get_reg(memory, &crawler);
        reg->state = VISITED;
        for (int8_t i=0; i<4; i++) {
            Position next_position;
            next_position.x = crawler.x + x_dir[i];
            next_position.y = crawler.y + y_dir[i];
            Register* next_reg = mem_get_reg(memory, &next_position);

            if (next_reg->state != FLOODED)
                continue;

            if (mem_in_map(memory, &next_position) == 0)
                continue;
            
            if (next_reg->score < reg->score) {
                next_reg->state = VISITED;
                crawler = next_position;
                step_count++;
                break;
            }
        }
    }

    return step_count;
}

static Position get_blocking_byte(Memory* memory, Byte* bytes, int32_t bytes_count)
{
    Memory mem_copy;
    memcpy(&mem_copy, memory, sizeof(Memory));
    mem_copy.registers = (Register*)malloc(sizeof(Register) * mem_copy.count);

    Byte* blocking_byte;
    for (int32_t i = 0; i < bytes_count; i++) {
        blocking_byte = &bytes[i];
        Register* reg = mem_get_reg(memory, &blocking_byte->position);
        reg->state = CORRUPTED;
        memcpy(mem_copy.registers, memory->registers, sizeof(Register) * mem_copy.count);
        int8_t can_reach = dfs_flood(&mem_copy, 2);
        if (can_reach == 0) 
            break;
    }

    free(mem_copy.registers);
    return blocking_byte->position;
}

int solve_task_1(char* file_name)
{
    Byte bytes[4 * KILOBYTE];
    int32_t bytes_size = sizeof(bytes) / sizeof(Byte);
    int32_t bytes_count = get_bytes(file_name, bytes, bytes_size);
    Memory memory = get_map(file_name);

    int32_t corrupted_bytes = KILOBYTE;
    mem_fall_bytes(&memory, bytes, corrupted_bytes);
    int32_t answer = dfs_flood(&memory, 1);

    printf("Answer: %d\n", answer);

    free(memory.registers);
}

int solve_task_2(char* file_name)
{
    Byte bytes[4096];
    int32_t bytes_size = sizeof(bytes) / sizeof(Byte);
    int32_t bytes_count = get_bytes(file_name, bytes, bytes_size);

    Memory memory = get_map(file_name);

    Position answer = get_blocking_byte(&memory, bytes, bytes_count);
    printf("Answer: %d,%d\n", answer.x, answer.y);
    free(memory.registers);
}

int main()
{
    // solve_task_1(FILENAME);
    solve_task_2(FILENAME);
    
    return 0;
}