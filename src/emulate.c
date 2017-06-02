#include "emulate.h"
#include "decode.h"

u32 fetchInstruction(MACHINE* ARM, u32 pc) {
    u32 instruction = 0;
    for(int byte = 0; byte < 4; byte++) {
        instruction += ARM->MEMORY[pc + byte] << (byte * 8);
    }
    return instruction;
}

INSTRUCTION* decodeInstruction(INSTRUCTION* instr, u32 instruction) {
    if (instruction == 0) {
        strcpy(instr->type, "halt");
    } else if(IS_DATAPROCESS(instruction)) {
        strcpy(instr->type, "dataprocessing");
        instr->instr.dp = malloc(sizeof(DATAPROCESSING_INSTR));
        DecodeDataProcessing(instr->instr.dp, instruction);
//        printDataProcessing(instr->instr.dp);
    } else if(IS_MULTI(instruction)) {
        strcpy(instr->type, "multiply");
        instr->instr.mp = malloc(sizeof(MULTIPLY_INSTR));
        DecodeMultiply(instr->instr.mp, instruction);
//        printMultiply(instr->instr.mp);
    } else if(IS_SINDATATRAN(instruction)) {
        strcpy(instr->type, "singledatatransfer");
        instr->instr.sdt = malloc(sizeof(SIN_DATA_TRAN_INSTR));
        DecodeSingleDataTransfer(instr->instr.sdt, instruction);
//        printSDT(instr->instr.sdt);
    } else if(IS_BRANCH(instruction)) {
        strcpy(instr->type, "branch");
        instr->instr.br = malloc(sizeof(BRANCH_INSTR));
        DecodeBranch(instr->instr.br, instruction);//
//        printBranch(instr->instr.br);
    } else {
        printf("Instruction not valid!");
        exit(EXIT_FAILURE);
    }
    return instr;
}

void executeInstruction(MACHINE* ARM, INSTRUCTION* instr) {
    if(strcmp(instr->type, "dataprocessing") == 0) {
//        parseDataprocessing(instr->instr.dp);
        dataprocessing(ARM, instr->instr.dp);
    } else if(strcmp(instr->type, "multiply") == 0) {
        //multiply(ARM, instr->instr.mp);
    } else if(strcmp(instr->type, "singledatatransfer") == 0) {
        //singledatatransfer(ARM, instr->instr.sdt);
    } else if(strcmp(instr->type, "branch") == 0) {
        //branch(ARM, instr->instr.br);
    } else if(strcmp(instr->type, "halt") == 0) {
        printf("halt function detected\n");
    }
}

int main(int argc,  char **argv) {
    MACHINE* ARM = createMachine();
    u32 fetchedInstr = 1;
    INSTRUCTION* decodedInstr = malloc(sizeof(INSTRUCTION));
    int decodedEmpty = 1, fetchedEmpty = 1, execute = 1;
    loadBinaryFile(ARM, argv[1]);
    while(execute) {
        if(decodedEmpty) {
            if(fetchedEmpty) {
                fetchedInstr = fetchInstruction(ARM, ARM->PCREG);
                fetchedEmpty = 0;
            } else {
                decodeInstruction(decodedInstr, fetchedInstr);
//                printf("Decoded ");
//                printDecodedInstruction(decodedInstr);
                fetchedInstr = fetchInstruction(ARM, ARM->PCREG);
//                printf("TRIGGERED %x\n", fetchedInstr);
                decodedEmpty = 0;
            }
        } else {
//            printf("%s\n", decodedInstr->type);
            if(strcmp(decodedInstr->type, "branch") == 0) {
                executeInstruction(ARM, decodedInstr);
                decodedEmpty = 1;
            } else {
//                printf("%s\n", decodedInstr->type);
                if(strcmp(decodedInstr->type,"halt") == 0){
                    execute = 0;
                    break;
                }
                executeInstruction(ARM, decodedInstr);
                decodeInstruction(decodedInstr, fetchedInstr);
            }
            fetchedInstr = fetchInstruction(ARM, ARM->PCREG);
        }
        ARM->PCREG += 4;
    }
    printMachineState(ARM);

/*    char hex[16];
    DATAPROCESSING_INSTR dpstruct;
    printBit(0xFu<<11);
    scanf("%s", hex);
    printf("%x\n", generateDataFromHex(hex));
    u32 instruction = generateDataFromHex(hex);
    printBit(instruction);
    printDataProcessing(DecodeDataProcessing(instruction));


    printBit(GENERATEMASK(2,2));
    printBit(GETBITS(0xe3a01001,21,24));

    printMachineState(ARM);*/

    return EXIT_SUCCESS;
}

