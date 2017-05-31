#include <hwloc.h>
#include "decode.h"
#include "emulate.h"

u32 fetchInstruction(MACHINE* ARM, u32 pc) {
    u32 instruction = 0;
    for(int byte = 0; byte < 4; byte++) {
        instruction += ARM->MEMORY[pc + byte] << ((3 - byte) * 8);
    }
    return instruction;
}

void decodeInstruction(u32 instruction) {
    if(IS_DATAPROCESS(instruction)) {
        DATAPROCESSING* dp = malloc(sizeof(DATAPROCESSING));
        DecodeDataProcessing(dp, instruction);
    } else if(IS_MULTI(instruction)) {
        MULTIPLY* mp = malloc(sizeof(MULTIPLY));
        DecodeMultiply(mp, instruction);
    } else if(IS_SINDATATRAN(instruction)) {
        SIN_DATA_TRAN* sdt = malloc(sizeof(SIN_DATA_TRAN));
        DecodeSingleDataTransfer(sdt, instruction);
    } else if(IS_BRANCH(instruction)) {
        BRANCH* br = malloc(sizeof(BRANCH));
        DecodeBranch(br, instruction);
    } else {
        printf("Instruction not valid!");
        exit(EXIT_FAILURE);
    }
}

int main(int argc,  char **argv) {
    MACHINE* ARM = createMachine();
    loadBinaryFile(ARM, "/homes/klc116/arm11_1617_testsuite/test_cases/add01");
/*    char hex[16];
    DATAPROCESSING dpstruct;
    printBit(0xFu<<11);
    scanf("%s", hex);
    printf("%x\n", generateDataFromHex(hex));
    u32 instruction = generateDataFromHex(hex);
    printBit(instruction);
    printDataProcessing(DecodeDataProcessing(instruction));


    printBit(GENERATEMASK(2,2));
    printBit(GETBITS(0xe3a01001,21,24));*/
    printMachineState(ARM);
    return EXIT_SUCCESS;
}


