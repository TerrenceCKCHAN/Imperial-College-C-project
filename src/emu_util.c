#include "decode.h"
#include "emulate.h"

int satisfyCondition(MACHINE* ARM, u32 instruction) {
    int NFlag = GETBITS(ARM->CPSRREG, 31, 31);
    int ZFlag = GETBITS(ARM->CPSRREG, 30, 30);
    int CFlag = GETBITS(ARM->CPSRREG, 29, 29);
    int VFlag = GETBITS(ARM->CPSRREG, 28, 28);
    u32 cond = GETBITS(instruction, 29, 31);
    int bool;
    switch(cond) {
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

/*This is the function to print bit*/
void printBit(uint32_t x){
    int i;
    uint32_t mask = (uint32_t) 1 << 31;
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

void printRegisters(MACHINE* ARM) {
    for(int index = 0; index <= 12; index++) {
        printf("$%d\t:% 11d (0x%08x)\n", index, ARM->REGISTER[index], ARM->REGISTER[index]);
    }
    printf("PC\t:% 11d (0x%08x)\n", ARM->PCREG, ARM->PCREG);
    printf("CPSR:% 11d (0x%08x)\n", ARM->CPSRREG, ARM->CPSRREG);
}

MACHINE* createMachine() {
    MACHINE* ARM = malloc(sizeof(MACHINE));
    ARM->PCREG = 0;
    ARM->CPSRREG = 0;
    for(int index = 0; index <=NUM_OF_GENERAL_REGISTER; index++) {
        ARM->REGISTER[index] = 0;
    }
    for(int index = 0; index <MAX_MEMORY; index++) {
        ARM->MEMORY[index] = 0;
    }
    return ARM;
}


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

void printMachineState(MACHINE* ARM) {
    printRegisters(ARM);
    printf("Non-zero memory:\n");
    printMemory(ARM);
}