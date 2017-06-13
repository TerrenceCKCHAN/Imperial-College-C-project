/////////////////////////////////////////////////////////////////////////////////////////
//C Group Project - First Year (2016-2017)
//File:emulate.c
//Group: 6
//Member: Cheung, Ka (klc116), Mang, Hao (hxm16), Cheuk, Ki (kfc216), Chan, Chun (ckc116)
/////////////////////////////////////////////////////////////////////////////////////////
#include "emulate.h"
#include "emu_decode.h"
/////////////////////////////////////////////////////////////////////////////////////////
// Fetch 4 bytes starting from the program counter(PC)
// and assemble the instruction for decoding
// Pre: State of the machine, program counter
// Post: the instruction in 32bits
/////////////////////////////////////////////////////////////////////////////////////////
u32 fetchInstruction(MACHINE* ARM, u32 pc) {
    // Initialize instruction
    u32 instruction = 0;
    // Add the bytes to the instruction after shifting to the correct bit
    for(int byte = 0; byte < 4; byte++) {
        instruction += ARM->MEMORY[pc + byte] << (byte * 8);
    }
    return instruction;
}
/////////////////////////////////////////////////////////////////////////////////////////
// Decode the instruction into structures for executing
// Pre: Instruction pointer and the 32bits instruction
// Post: The union of the instructions, showing the type and respective
// instruction structures
/////////////////////////////////////////////////////////////////////////////////////////
void decodeInstruction(INSTRUCTION* instr, u32 instruction) {
    //printf("%x %d\n", instruction, IS_BRANCH(instruction));
    if (instruction == 0) {  // Represent the all-zero halt instruction
        strcpy(instr->type, "halt");
    } else if(IS_DATAPROCESS(instruction)) { //Represent the dataprocessing instruction
        strcpy(instr->type, "dataprocessing");
        instr->instr.dp = malloc(sizeof(DATAPROCESSING_INSTR));
        DecodeDataProcessing(instr->instr.dp, instruction);
//        printDataProcessing(instr->instr.dp);
    } else if(IS_MULTI(instruction)) { //Represent the multiply instruction
        strcpy(instr->type, "multiply");
        instr->instr.mp = malloc(sizeof(MULTIPLY_INSTR));
        DecodeMultiply(instr->instr.mp, instruction);
        //printMultiply(instr->instr.mp);
    } else if(IS_SINDATATRAN(instruction)) { //Represent the single data transfer instruction
        strcpy(instr->type, "singledatatransfer");
        instr->instr.sdt = malloc(sizeof(SIN_DATA_TRAN_INSTR));
        DecodeSingleDataTransfer(instr->instr.sdt, instruction);
        //printSDT(instr->instr.sdt);
    } else if(IS_BRANCH(instruction)) { //Represent the branch instruction
        strcpy(instr->type, "branch");
        instr->instr.br = malloc(sizeof(BRANCH_INSTR));
        DecodeBranch(instr->instr.br, instruction);//
//        printBranch(instr->instr.br);
    } else {
        printf("Instruction not valid!");
        exit(EXIT_FAILURE);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////
// Execute the decoded function and change the state of the ARM machine
// Pre: State of the current machine, instruction structure
// Post: The modified state of the machine after each execution function
/////////////////////////////////////////////////////////////////////////////////////////
void executeInstruction(MACHINE* ARM, INSTRUCTION* instr) {

    if(strcmp(instr->type, "dataprocessing") == 0) {
//        parseDataprocessing(instr->instr.dp);
        dataprocessing(ARM, instr->instr.dp);
    } else if(strcmp(instr->type, "multiply") == 0) {
        multiply(ARM, instr->instr.mp);
    } else if(strcmp(instr->type, "singledatatransfer") == 0) {
        singleDataTran(ARM, instr->instr.sdt);
    } else if(strcmp(instr->type, "branch") == 0) {
        branch(ARM, instr->instr.br);
    } else if(strcmp(instr->type, "halt") == 0) {
        printf("halt function detected\n");
    }
}

int main(int argc,  char **argv) {
    //Creating the ARM machine with 0s in registers and memory
    MACHINE* ARM = createMachine();
    //Simulating the pipeline: fetchedInstr represents the Fetched state while
    //DecodedInstr represens the Decoded state for execution
    u32 fetchedInstr = 1;
    INSTRUCTION* decodedInstr = malloc(sizeof(INSTRUCTION));
    int decodedEmpty = 1, fetchedEmpty = 1, execute = 1;
//    loadBinaryFile(ARM, "/homes/klc116/CLionProjects/arm11_06/programs/kernel.img");
    loadBinaryFile(ARM, argv[1]);
    while(execute) {
        if(decodedEmpty) {
            if(fetchedEmpty) {
                fetchedInstr = fetchInstruction(ARM, ARM->REGISTER[15]);
                fetchedEmpty = 0;
            } else {
                decodeInstruction(decodedInstr, fetchedInstr);
                fetchedInstr = fetchInstruction(ARM, ARM->REGISTER[15]);
                decodedEmpty = 0;
            }
        } else {
            if(strcmp(decodedInstr->type, "branch") == 0 && satisfyCondition(ARM, decodedInstr->instr.br->COND)) {
                executeInstruction(ARM, decodedInstr);
                decodedEmpty = 1;
            } else {
                if(strcmp(decodedInstr->type,"halt") == 0){
                    execute = 0;
                    break;
                }
                executeInstruction(ARM, decodedInstr);
                decodeInstruction(decodedInstr, fetchedInstr);;
            }
            fetchedInstr = fetchInstruction(ARM, ARM->REGISTER[15]);
        }
        ARM->REGISTER[15] += 4;
//        printMachineState(ARM);
    }
    printMachineState(ARM);
    return EXIT_SUCCESS;
}


