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
    printBit(GETBITS(0xe3a01001,21,24));
    DATAPROCESSING* dp = DecodeDataProcessing(0);
    dp->OPRAND2 =0x136;
    printf("Oprand2\n");
    printBit(dp->OPRAND2);
    printf("IMM:\n");
    printBit(GETBITS(dp->OPRAND2,0,7));//thing to rotate
    printf("After rotate for 2\n");
    u32 roate = GETBITS(dp->OPRAND2,8,11);
    printBit(RotateR(GETBITS(dp->OPRAND2, 0, 7),roate*2));
    u32 result = SETBITS(RotateR(GETBITS(dp->OPRAND2, 0, 7),roate*2),dp->OPRAND2,0,8);
    printBit(result);
    printBit(RotateR(0xef,2));
    printDataProcessing(dp);*/
    u32 Oprand2 =0x18d;

    u32 rotate = GETBITS(Oprand2, 8, 11);
    u32 Imm = GETBITS(Oprand2,0,7);
    u32 ImmAfterRotate = RotateRH(Imm,rotate*2,8);
    //printBit(SETBITS(ImmAfterRotate,Oprand2,0,8));
    u32 shiftType = GETBITS(Oprand2,5,6);
    u32 Rm = GETBITS(Oprand2,0,3);
    u32 value = GETBITS(Oprand2,7,11);
    printBit(Oprand2);
    printBit(LShiftL(Rm ,value));
    printBit(SETBITS(LShiftL(Rm,value),Oprand2,0,4));


    dataprocessing(ARM,0xe3a01001);
    dataprocessing(ARM,0xe1a01081);
    printMachineState(ARM);




    return EXIT_SUCCESS;
}


