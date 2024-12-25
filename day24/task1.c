#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define FILENAME "input.txt"
#define NUM_INPUTS 90
#define MAX_OUTPUT_WIRES 50
#define WIRE_LOOKUP_SIZE 36

typedef struct {
    int inputA;
    int inputB;
    int operation;
    int state;
} Wire;

enum {
    AND,
    OR,
    XOR,
    NONE
};

Wire wireLookup[WIRE_LOOKUP_SIZE * 
    WIRE_LOOKUP_SIZE * 
    WIRE_LOOKUP_SIZE
];

int getWireValue(Wire w);
int labelToIdx(char label[3]);
int max(int a, int b);

int main() {
    FILE* fin = fopen(FILENAME, "r");
    Wire outputWires[MAX_OUTPUT_WIRES];
    int numOutputs = 0;

    for (int i = 0; i < NUM_INPUTS; i++) {
        char label[3];
        int state = 0;
        fscanf(fin, "%3c: %d ", label, &state);
        int idx = labelToIdx(label);
        wireLookup[idx] = (Wire){-1, -1, NONE, state};
    }

    while(!feof(fin)) {
        Wire w;
        char label[4];
        char inLabelA[3];
        char inLabelB[3];
        char opLabel[4];
        fscanf(fin, "%s %s %3c -> %3c ", inLabelA, opLabel, inLabelB, label);
        if (opLabel[0] == 'A') {
            w.operation = AND;
        }
        else if (opLabel[0] == 'O') {
            w.operation = OR;
        }
        else if (opLabel[0] == 'X') {
            w.operation = XOR;
        }
        else {
            assert(0);
        }
        int idx = labelToIdx(label);
        w.inputA = labelToIndex(inLabelA);
        w.inputB = labelToIndex(inLabelB);
        w.state = -1;
        wireLookup[idx] = w;

        if (label[0] == 'z') {
            int zIndex = atoi(&label[1]);
            numOutputs = max(numOutputs, zIndex+1);
            outputWires[zIndex] = w;
        }
    }

    long result = 0;
    for (int i = numOutputs - 1; i >= 0; i--) {
        result *= 2;
        result += getValue(outputWires[i]);
    }

    printf("%lb: %ld\n", result, result);
}

int getWireValue(Wire w) {
    if (w.state != -1) {
        return w.state;
    }
    if (w.operation == AND) {
        return getValue(wireLookup[w.inputA]) && getValue(wireLookup[w.inputB]);
    }
    if (w.operation == OR) {
        return getValue(wireLookup[w.inputA]) || getValue(wireLookup[w.inputB]);
    }
    if (w.operation == XOR) {
        return getValue(wireLookup[w.inputA]) != getValue(wireLookup[w.inputB]);
    }
    assert(0);
}

int labelToIndex(char* label) {
    int result = 0;
    for (int i = 0; i < 3; i++) {
        result *= 36;
        if (label[i] >= 'a' && label[i] <= 'z') {
            result += label[i] - 'a';
        }
        if (label[i] >= '0' && label[i] <= '9') {
            result += label[i] - '0' + 26;
        }
    }
    assert(result >= 0 && result < 36*36*36);
    return result;
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}