#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define FILENAME "input.txt"
#define NUM_INPUTS 90
#define MAX_OUTPUT_WIRES 50
#define MAX_WIRES 300
#define WIRE_LOOKUP_SIZE 36

typedef struct {
    int inputA;
    int inputB;
    int operation;
    int state;
    int classification;
} Wire;

enum {
    AND,
    OR,
    XOR,
    NONE
};

enum {
    XOR1,
    XOR2,
    XOR3,
    AND1,
    AND2,
    AND3,
    OR1,
    INPUT1
};

void processInput(FILE* fin);
void processWires(FILE* fin, int* outputWires, int* numOutputs);
void identifyProblems(int numOutputs);
void printProblems();
int getWireValue(Wire w);
int labelToIdx(char label[3]);
void printLabel(int index);
void idxToLabel(int idx, char label[4]);
int containsLabel(char list[8][4], int size, char label[4]);
void addProblem(int idx);
int max(int a, int b);
int compare(const void *a, const void *b);

Wire wireLookup[WIRE_LOOKUP_SIZE * 
    WIRE_LOOKUP_SIZE * 
    WIRE_LOOKUP_SIZE
] = {0};

char problemLabels[8][4] = {0};
int numProblems = 0;
int outputWires[MAX_OUTPUT_WIRES];
int numOutputs = 0;
int wireList[MAX_WIRES];
int numWires = 0;

int main() {
    FILE* fin = fopen(FILENAME, "r");

    processInput(fin);
    processWires(fin, outputWires, &numOutputs);
    identifyProblems(numOutputs);
    printProblems();

    fclose(fin);
    return 0;           
}

void processInput(FILE* fin) {
    for (int i = 0; i < NUM_INPUTS; i++) {
        char label[3];
        int state = 0;
        fscanf(fin, "%3c: %d ", label, &state);
        int idx = labelToIdx(label);
        wireLookup[idx] = (Wire){-1, -1, NONE, state, INPUT1};
    }
}

void processWires(FILE* fin, int* outputWires, int* numOutputs) {
    char wireList[MAX_WIRES];
    int numWires = 0;

    while (!feof(fin)) {
        Wire w;
        char label[4], inLabelA[3], inLabelB[3], operationLabel[4];
        fscanf(fin, "%s %s %3c -> %3c ", inLabelA, operationLabel, inLabelB, label);

        if (operationLabel[0] == 'A') w.operation = AND;
        else if (operationLabel[0] == 'O') w.operation = OR;
        else if (operationLabel[0] == 'X') w.operation = XOR;
        else assert(0);

        int index = labelToIdx(label);
        w.inputA = labelToIdx(inLabelA);
        w.inputB = labelToIdx(inLabelB);
        w.state = -1;

        if (w.inputA == labelToIdx("x00") || w.inputB == labelToIdx("x00")) {
            w.classification = (w.operation == XOR) ? XOR1 : AND1;
        } else if (wireLookup[w.inputA].classification == INPUT1) {
            w.classification = (w.operation == XOR) ? XOR2 : AND2;
        } else {
            w.classification = (w.operation == XOR) ? XOR3 :
                               (w.operation == AND) ? AND3 : OR1;
        }

        wireLookup[index] = w;
        wireList[numWires++] = index;

        if (label[0] == 'z') {
            int zIndex = atoi(&label[1]);
            *numOutputs = (*numOutputs > zIndex) ? *numOutputs : zIndex + 1;
            outputWires[zIndex] = index;
        }
    }
}

void identifyProblems(int numOutputs) {
    for (int i = 0; i < numOutputs; i++) {
        Wire w = wireLookup[outputWires[i]];
        if ((i == 0 && w.classification == XOR1) || 
            (i == numOutputs - 1 && w.classification == OR1) ||
            w.classification == XOR3) {
            continue;
        }
        addProblem(outputWires[i]);
    }

    for (int i = 0; i < numWires; i++) {
        Wire w = wireLookup[wireList[i]];
        Wire a = wireLookup[w.inputA];
        Wire b = wireLookup[w.inputB];

        if (w.classification == XOR3 || w.classification == AND3) {
            if (a.classification != XOR2 && a.classification != OR1 && a.classification != AND1)
                addProblem(w.inputA);
            if (b.classification != XOR2 && b.classification != OR1 && b.classification != AND1)
                addProblem(w.inputB);
        }

        if (w.classification == OR1) {
            if (a.classification != AND2 && a.classification != AND3)
                addProblem(w.inputA);
            if (b.classification != AND2 && b.classification != AND3)
                addProblem(w.inputB);
        }
    }
}

void printProblems() {
    qsort(problemLabels, numProblems, sizeof(problemLabels[0]), compare);
    for (int i = 0; i < numProblems; i++) {
        printf("%s", problemLabels[i]);
        if (i != numProblems - 1) {
            printf(",");
        }
    }
    printf("\n");
}

int labelToIdx(char* label) {
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

void printWire(int index) {
    Wire w = wireLookup[index];
    printLabel(w.inputA);
    if (w.operation == OR) {
        printf(" OR ");
    }
    if (w.operation == AND) {
        printf(" AND ");
    }
    if (w.operation == XOR) {
        printf(" XOR ");
    }
    printLabel(w.inputB);
    printf(" -> ");
    printLabel(index);
    printf("\n");
}

void idxToLabel(int idx, char label[4]) {
    label[0] = idx / 1296;
    label[1] = (idx / 36) % 36;
    label[2] = idx % 36;

    for (int i = 0; i < 3; i++) {
        if (label[i] < 26) {
            label[i] += 'a';
        }
        else if (label[i] >= 26) {
            label[i] -= 26;
            label[i] += '0';
        }
    }
    label[3] = '\0';
}

void addProblem(int idx) {
    char label[4];
    idxToLabel(idx, label);
    if (!containsLabel(problemLabels, numProblems, label)) {
        printWire(idx);
        strcpy(problemLabels[numProblems++], label);
    }
}

int containsLabel(char list[8][4], int size, char label[4]) {
    for (int i = 0; i < size; i++) {
        if (strncmp(label, list[i], 3) == 0) {
            return 1;
        }
    }

    return 0;
}

void printLabel(int idx) {
    char label[4];
    idxToLabel(idx, label);
    printf("%s", label);
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int compare(const void *a, const void *b) {
    return strcmp((char*)a, (char*)b);
}