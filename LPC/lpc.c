#include <stdio.h>
#include <stdlib.h>
#include "lpc.h"

int memory[MEMORY_SIZE] = {0};
int accumulator = 0;
int programCounter = 0;
int instructionReg = 0;
int opCode = 0;
int operand = 0;

#define SENTINEL -99999

void loadProgram() {
    int instruction;
    int address = 0;
    while (scanf("%d", &instruction) == 1 && instruction!= SENTINEL) {
        if (instruction < -9999 || instruction > 9999) {
            printf("Invalid instruction. Please enter a valid 4-digit word.\n");
            continue;
        }
        if (address >= MEMORY_SIZE) {
            printf("Memory overflow.\n");
            exit(1);
        }
        memory[address++] = instruction;
    }
}

void memoryDump() {
    printf("Registers: \n");
    printf("accumulator %+05d\n", accumulator);
    printf("program counter %05d\n", programCounter - 1);
    printf("op-code %05d\n", opCode);
    printf("operand %05d\n", operand);
    printf("\n      0    1    2    3    4    5    6    7    8    9 ");

    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (i % 10 == 0) {
            printf("\n%2d ", i);
        }
        int value = (memory[i] == -9999)? 0 : memory[i];
        printf("%04d ", value);
    }
    printf("\n***End LPC Execution***\n");
}
void executeProgram() {
    printf("***Start LPC Execution***\n");
    while (1) {
        if (programCounter >= MEMORY_SIZE) {  // Check for bounds
            printf("*** FATAL ERROR: Program counter out of bounds ***\n");
            memoryDump();
            exit(0);
        }

        instructionReg = memory[programCounter++];
        opCode = instructionReg / 100;
        operand = instructionReg % 100;
        if (opCode > 43) {
            printf("***FATAL ERROR: Illegal opCode***\n");
            printf("***LPC execution abnormally terminated***\n\n");
            memoryDump();
            exit(0);
        }
        if (operand >= MEMORY_SIZE) {
            printf("*** FATAL ERROR: Operand out of bounds ***\n");
            memoryDump();
            exit(0);
        }

        switch (opCode) {
            case READ:
                if (operand < MEMORY_SIZE) {
                    int value;
                    scanf("%d", &value);
                    if (value < -9999) {
                        memory[operand] = -9999;
                    } else if (value > 9999) {
                        memory[operand] = 9999;
                    } else {
                        memory[operand] = value;
                    }
                }
                break;
            case WRITE:
                if (operand < MEMORY_SIZE) {
                    printf("Contents of %02d: %d\n", operand, memory[operand]);
                }
                break;
            case LOAD:
                if (operand < MEMORY_SIZE) {
                    accumulator = memory[operand];
                }
                break;
            case STORE:
                if (operand < MEMORY_SIZE) {
                    if (accumulator < -9999) {
                        memory[operand] = -9999;
                    } else if (accumulator > 9999) {
                        memory[operand] = 9999;
                    } else {
                        memory[operand] = accumulator;
                    }
                }
                break;
            case ADD:
                if (operand < MEMORY_SIZE) {
                    if ((accumulator > 0 && memory[operand] > 9999 - accumulator) || (accumulator < 0 && memory[operand] < -9999 - accumulator)) {
                        printf("***FATAL ERROR - Accumulator Overflow***\n");
                        printf("***lpc execution abnormally terminated***\n\n");
                        memoryDump();
                        exit(0);
                    }
                    accumulator += memory[operand];
                }
                break;
            case SUBTRACT:
                if (operand < MEMORY_SIZE) {
                    if ((accumulator > 0 && memory[operand] < accumulator - 9999) || (accumulator < 0 && memory[operand] > accumulator + 9999)) {
                        printf("***FATAL ERROR - Accumulator Overflow***\n");
                        printf("***lpc execution abnormally terminated***\n\n");
                        memoryDump();
                        exit(0);
                    }
                    accumulator -= memory[operand];
                }
                break;
            case DIVIDE:
                if (operand < MEMORY_SIZE) {
                    if (memory[operand] == 0) {
                        printf("***FATAL ERROR - Attempt to divide by zero***\n");
			                printf("***lpc execution abnormally terminated***\n\n");

                        memoryDump();
                        exit(0);
                    }
                    accumulator /= memory[operand];
                }
                break;
            case MULTIPLY:
                if (operand < MEMORY_SIZE) {
                    long temp = (long)accumulator * (long)memory[operand];
                    if (temp > 9999 || temp < -9999) {
                        printf("***FATAL ERROR - Accumulator Overflow***\n");
                        printf("***lpc execution abnormally terminated***\n\n");
                        memoryDump();
                        return;
                    }
                    accumulator = (int)temp;
                }
                break;
            case JUMP:
                programCounter = operand;
                break;
            case JUMPNEG:
                if (accumulator < 0) {
                    programCounter = operand;
                }
                break;
            case JUMPZERO:
                if (accumulator == 0) {
                    programCounter = operand;
                }
                break;
            case HALT:
                printf("***End LPC Execution***\n");
                return;
            default:
                printf("***FATAL ERROR: Illegal opCode***\n");
                printf("***LPC execution abnormally terminated***\n\n");
                memoryDump();
                exit(0);
        }
    }
}
int main() {
    loadProgram();
    executeProgram();
    return 0;
}
