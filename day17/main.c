#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 1000
#define MAX_LINE_LENGTH 256
#define REG_PREFIX_LEN 11
#define PROG_PREFIX_LEN 8
#define FILEPATH "input.txt"

// Instruction to opcode
enum {
    ADV = 0,
    BXL,
    BST,
    JNZ,
    BXC,
    OUT,
    BDV,
    CDV
};

typedef struct {
    int reg_a;
    int reg_b;
    int reg_c;
} Registers;

void read_input_file(const char *filename, Registers *registers, int *instruction_stack, int *instruction_size);
void execute_instruction(const int *instruction_stack, Registers *registers, int *instruction_pointer);
long parse_combo(int combo, const Registers *registers);
long adv(long reg_a, long operand);
long bxl(long reg_b, long operand);
long bst(long operand);
long jnz(long reg_a, long operand);
long bxc(long reg_b, long reg_c);
long out(long operand);
long bdv(long reg_a, long operand);
long cdv(long reg_a, long operand);
long get_reg_a_value(int *instruction_stack, int position, Registers *registers);

int main() {
    Registers registers = {0};
    int instruction_stack[MAX_STACK_SIZE] = {0};  
    int instruction_size = 0;

    read_input_file(FILEPATH, &registers, instruction_stack, &instruction_size);

    printf("Register A: %d\n", registers.reg_a);
    printf("Register B: %d\n", registers.reg_b);
    printf("Register C: %d\n", registers.reg_c);
    printf("Instruction stack: ");
    for (int i = 0; i < instruction_size; i++) {
        printf("%d ", instruction_stack[i]);
    }
    printf("\n");

    int instruction_pointer = 0;

    while (instruction_pointer < instruction_size && instruction_stack[instruction_pointer] != -1) {
        execute_instruction(instruction_stack, &registers, &instruction_pointer);
    }

    return 0;
}

void read_input_file(const char *filename, Registers *registers, int *instruction_stack, int *instruction_size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    int parsing_program = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Register A:", REG_PREFIX_LEN) == 0) {
            registers->reg_a = atoi(line + REG_PREFIX_LEN);
        } else if (strncmp(line, "Register B:", REG_PREFIX_LEN) == 0) {
            registers->reg_b = atoi(line + REG_PREFIX_LEN);
        } else if (strncmp(line, "Register C:", REG_PREFIX_LEN) == 0) {
            registers->reg_c = atoi(line + REG_PREFIX_LEN);
        } else if (strncmp(line, "Program:", PROG_PREFIX_LEN) == 0) {
            parsing_program = 1;
            char *token = strtok(line + PROG_PREFIX_LEN, ",");
            while (token) {
                instruction_stack[(*instruction_size)++] = atoi(token);
                token = strtok(NULL, ",");
            }
            instruction_stack[*instruction_size] -= 1;
        }
    }

    fclose(file);
}

void execute_instruction(const int *instruction_stack, Registers *registers, int *instruction_pointer) {
    int opcode = instruction_stack[*instruction_pointer + 1];

    switch (instruction_stack[*instruction_pointer]) {
        case ADV:
            registers->reg_a = adv(registers->reg_a, parse_combo(opcode, registers));
            break;
        case BXL:
            registers->reg_b = bxl(registers->reg_b, opcode);
            break;
        case BST:
            registers->reg_b = bst(parse_combo(opcode, registers));
            break;
        case JNZ:
            if (registers->reg_a != 0) {
                *instruction_pointer = jnz(registers->reg_a, opcode) - 2;
            }
            break;
        case BXC:
            registers->reg_b = bxc(registers->reg_b, registers->reg_c);
            break;
        case OUT:
            printf("%ld\n", out(parse_combo(opcode, registers)));
            break;
        case BDV:
            registers->reg_b = bdv(registers->reg_a, parse_combo(opcode, registers));
            break;
        case CDV:
            registers->reg_c = cdv(registers->reg_a, parse_combo(opcode, registers));
            break;
        default:
            fprintf(stderr, "Unknown instruction: %d\n", instruction_stack[*instruction_pointer]);
            exit(EXIT_FAILURE);
    }

    *instruction_pointer += 2;
}

long parse_combo(int combo, const Registers *registers) {
    switch (combo) {
        case 0: return 0;
        case 1: return 1;
        case 2: return 2;
        case 3: return 3;
        case 4: return registers->reg_a;
        case 5: return registers->reg_b;
        case 6: return registers->reg_c;
        default:
            fprintf(stderr, "Invalid combo operand: %d\n", combo);
            exit(EXIT_FAILURE);
    }
}

long adv(long reg_a, long operand) { return reg_a >> operand; }
long bxl(long reg_b, long operand) { return reg_b ^ operand; }
long bst(long operand) { return operand % 8; }
long jnz(long reg_a, long operand) { return operand; }
long bxc(long reg_b, long reg_c) { return reg_b ^ reg_c; }
long out(long operand) { return operand % 8; }
long bdv(long reg_a, long operand) { return reg_a >> operand; }
long cdv(long reg_a, long operand) { return reg_a >> operand; }

long get_reg_a_value(int *instruction_stack, int position, Registers *registers) {
    if (position < 0) {
        registers->reg_a >>= 3;
        return registers->reg_a;
    }

    char output_buffer[MAX_STACK_SIZE];

    for (int i = 0; i < 8; ++i) {
        execute_instruction(instruction_stack, registers, output_buffer);

        if ((output_buffer[0] - '0') == instruction_stack[position]) {
            registers->reg_a <<= 3;

            long temp_a = get_reg_a_value(instruction_stack, position - 1, registers);
            if (temp_a != -1) {
                return temp_a;
            } else {
                registers->reg_a >>= 3;
            }
        }

        if (i == 7) {
            return -1;
        }

        registers->reg_a += 1;
    }

    return -1;
}
