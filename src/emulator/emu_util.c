#include "decode.h"
#include "emulate.h"

//Checking if the state of the machine satisfy the condition by checking the CPSR flags of the machine
//PRE: State of the machine, the 4 bytes instruction
//POST: Return 1 for true (satisfy condition) or return 0 for false (not satisfy condition)
int satisfyCondition(MACHINE* ARM, u32 condition) {
    int NFlag = GETBITS(ARM->REGISTER[16], 31, 31);
    int ZFlag = GETBITS(ARM->REGISTER[16], 30, 30);
    int CFlag = GETBITS(ARM->REGISTER[16], 29, 29);
    int VFlag = GETBITS(ARM->REGISTER[16], 28, 28);
    int bool;
    switch(condition) {
        case 0x0:
            bool = (ZFlag == 1) ? 1 : 0; break;
        case 0x1:
            bool = (ZFlag == 0) ? 1 : 0; break;
        case 0xa:
            bool = (NFlag == VFlag) ? 1 : 0; break;
        case 0xb:
            bool = (NFlag != VFlag) ? 1 : 0; break;
        case 0xc:
            bool = (ZFlag == 0) && (NFlag == VFlag) ? 1 : 0; break;
        case 0xd:
            bool = (ZFlag == 1) || (NFlag != VFlag) ? 1 : 0; break;
        case 0xe:
            bool = 1; break;
    }
    return bool;
}

//This is the function to print bit of a unsigned 32 bit integer
//PRE: An unsigned 32bit integer
//POST: Print the bitwise representation of the integer
void printBit(u32 x){
    int i;
    u32 mask = (u32) 1 << 31;
    for(i = 0;i < 32;++i){
        printf("%i", (x & mask) != 0);
        x<<=1;
    }
    printf("\n");
}

u32 generateDataFromHex(char hex[]){
    int length = strlen(hex);
    u32 data = 0;
    u32 shift = (length - 1) * 4;
    for(int pos = 0; pos < length; pos++) {
        u32 hexValue;
        if(hex[pos] >= '0' && hex[pos] <= '9') {
            hexValue = (hex[pos] - '0');
        } else if(hex[pos] >= 'a' && hex[pos] <= 'f') {
            hexValue = hex[pos] - 'a' + 10;
        }
        data += hexValue << shift;
        shift -= 4;
    }
    return data;
}

//Print all registers of the machine with a specific format
//PRE: State of the Machine (MACHINE pointer)
//POST: Print all the contents in the general registers including PC and CPSR register
void printRegisters(MACHINE* ARM) {
    for(int index = 0; index <= 12; index++) {
        printf("$%-3d: %10d (0x%08x)\n", index, ARM->REGISTER[index], ARM->REGISTER[index]);
    }
    printf("PC  : %10d (0x%08x)\n", ARM->REGISTER[15], ARM->REGISTER[15]);
    printf("CPSR: %10d (0x%08x)\n", ARM->REGISTER[16], ARM->REGISTER[16]);
}

//Initialize a new machine with all the registers and memory initialized as 0
MACHINE* createMachine() {
    MACHINE* ARM = malloc(sizeof(MACHINE));
    ARM->REGISTER[15] = 0;
    ARM->REGISTER[16] = 0;
    for(int index = 0; index <=NUM_OF_GENERAL_REGISTER; index++) {
        ARM->REGISTER[index] = 0;
    }
    for(int index = 0; index <MAX_MEMORY; index++) {
        ARM->MEMORY[index] = 0;
    }
    return ARM;
}

//Print the non-zero memory of the machine with a specific format
//PRE: State of the Machine (MACHINE pointer)
//POST: Print all the contents in the memory that are non-zero
void printMemory(MACHINE* ARM) {

    for(int index = 0; index < MAX_MEMORY; index+=4) {
        u32 instruction = 0;
        for(int byte = 0; byte < 4; byte++) {
            instruction += ARM->MEMORY[index + byte] << ((3 - byte) * 8);
        }
        if(instruction != 0) {
            printf("0x%08x: 0x%08x\n", index, instruction);
        }
    }
}

//Print both the registers and the non-zero memory in the machine
//PRE: State of the Machine (MACHINE pointer)
//POST: Print all the contents in the machine including non-zero memory and registers
void printMachineState(MACHINE* ARM) {
    printf("Registers:\n");
    printRegisters(ARM);
    printf("Non-zero memory:\n");
    printMemory(ARM);
}