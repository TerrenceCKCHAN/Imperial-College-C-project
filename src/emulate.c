#include <hwloc.h>
#include "decode.h"
#include "emulate.h"

u32 fetchInstruction(MACHINE* ARM, u32 pc) {
    u32 instruction = 0;
    for(int byte = 0; byte < 4; byte++) {
        instruction += ARM->MEMORY[pc + byte] << (byte * 8);
    }
    return instruction;
}

void decodeInstruction(u32 instruction) {
    if(IS_DATAPROCESS(instruction)) {
        DATAPROCESSING_INSTR* dp = malloc(sizeof(DATAPROCESSING_INSTR));
        DecodeDataProcessing(dp, instruction);
        printDataProcessing(dp);
    } else if(IS_MULTI(instruction)) {
        MULTIPLY_INSTR* mp = malloc(sizeof(MULTIPLY_INSTR));
        DecodeMultiply(mp, instruction);
        printMultiply(mp);
    } else if(IS_SINDATATRAN(instruction)) {
        SIN_DATA_TRAN_INSTR* sdt = malloc(sizeof(SIN_DATA_TRAN_INSTR));
        DecodeSingleDataTransfer(sdt, instruction);
        printSDT(sdt);
    } else if(IS_BRANCH(instruction)) {
        BRANCH_INSTR* br = malloc(sizeof(BRANCH_INSTR));
        DecodeBranch(br, instruction);
        printBranch(br);
    } else {
        printf("Instruction not valid!");
        exit(EXIT_FAILURE);
    }
}

int main(int argc,  char **argv) {
    MACHINE* ARM = createMachine();
    u32 instruction;
    u32 PC = 0;
    loadBinaryFile(ARM, "/homes/klc116/arm11_1617_testsuite/test_cases/mul01");
    instruction = fetchInstruction(ARM,0);
    while(fetchInstruction(ARM, PC) != 0) {
        decodeInstruction(fetchInstruction(ARM,PC));
        PC += 4;
    }
/*    char hex[16];
    DATAPROCESSING_INSTR dpstruct;
    printBit(0xFu<<11);
    scanf("%s", hex);
    printf("%x\n", generateDataFromHex(hex));
    u32 instruction = generateDataFromHex(hex);
    printBit(instruction);
    printDataProcessing(DecodeDataProcessing(instruction));*/
/*

    printBit(GENERATEMASK(2,2));
    printBit(GETBITS(0xe3a01001,21,24));
    printMachineState(ARM);*/
    return EXIT_SUCCESS;
}
