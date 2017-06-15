/////////////////////////////////////////////////////////////////////////////////////////
//C Group Project - First Year (2016-2017)
//File:emu_decode.c
//Group: 6
//Member: Cheung, Ka (klc116), Mang, Hao (hxm16), Cheuk, Ki (kfc216), Chan, Chun (ckc116)
/////////////////////////////////////////////////////////////////////////////////////////
#include "emulate.h"
#include "emu_decode.h"

/////////////////////////////////////////////////////////////////////////////////////////
// Decode the dataprocessing instructions into instruction structures by extracting corresponding
// bits to the strcuture using the GETBITS function
// PRE: Data processing instuction pointer and the 32-bit instruction
// POST: Contents of the structures are assigned to their corresponding bit in the instruction
/////////////////////////////////////////////////////////////////////////////////////////
void DecodeDataProcessing(DATAPROCESSING_INSTR* instr, u32 instruction) {
    //Assigning corresponding bits to the structure
    instr->INSTRUCTION = instruction;
    instr->I = GETBITS(instruction, 25, 25);
    instr->COND = GETBITS(instruction, 28, 31);
    instr->S = GETBITS(instruction, 20, 20);
    instr->DEST = GETBITS(instruction, 12, 15);
    instr->SRC = GETBITS(instruction, 16, 19);
    instr->OPERAND2 = GETBITS(instruction, 0, 11);
    instr->OPCODEBIN = GETBITS(instruction, 21, 24);
    //Assigning the opcode string based on the binary opcodes
    switch(instr->OPCODEBIN) {
        case and:
            strcpy(instr->OPCODE,"and");
            break;
        case eor:
            strcpy(instr->OPCODE,"eor");
            break;
        case sub:
            strcpy(instr->OPCODE,"sub");
            break;
        case rsb:
            strcpy(instr->OPCODE,"rsb");
            break;
        case add:
            strcpy(instr->OPCODE,"add");
            break;
        case tst:
            strcpy(instr->OPCODE,"tst");
            instr->DEST = NOT_EXIST;
            break;
        case teq:
            strcpy(instr->OPCODE,"teq");
            instr->DEST = NOT_EXIST;
            break;
        case cmp:
            strcpy(instr->OPCODE,"cmp");
            instr->DEST = NOT_EXIST;
            break;
        case orr:
            strcpy(instr->OPCODE,"orr");
            break;
        case mov:
            strcpy(instr->OPCODE,"mov");
            instr->SRC = NOT_EXIST;
            break;
        default:
            break;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
// Decode the multiply instructions into instruction structures by extracting corresponding
// bits to the strcuture using the GETBITS function
// PRE: Multiply instuction pointer and the 32-bit instruction
// POST: Contents of the structures are assigned to their corresponding bit in the instruction
/////////////////////////////////////////////////////////////////////////////////////////
void DecodeMultiply(MULTIPLY_INSTR* instr, u32 instruction) {
    //Assigning corresponding bits to the structure
    instr->INSTRUCTION = instruction;
    instr->A = GETBITS(instruction, 21, 21);
    instr->COND = GETBITS(instruction, 28, 31);
    instr->S = GETBITS(instruction, 20, 20);
    instr->DEST = GETBITS(instruction, 16, 19);
    instr->REGM = GETBITS(instruction, 0, 3);
    instr->REGS = GETBITS(instruction, 8, 11);
    //Assigning the opcode string based on the binary opcodes
    switch(instr->A) {
        case 0:
            strcpy(instr->OPCODE,"mul");
            instr->ACC = NOT_EXIST;
            break;
        case 1:
            strcpy(instr->OPCODE,"mla");
            instr->ACC = GETBITS(instruction, 12, 15);
            break;
        default:
            break;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
// Decode the single data transfer instructions into instruction structures by extracting corresponding
// bits to the strcuture using the GETBITS function
// PRE: single data transfer instuction pointer and the 32-bit instruction
// POST: Contents of the structures are assigned to their corresponding bit in the instruction
/////////////////////////////////////////////////////////////////////////////////////////
void DecodeSingleDataTransfer(SIN_DATA_TRAN_INSTR* instr, u32 instruction) {
    //Assigning corresponding bits to the structure
    instr->INSTRUCTION = instruction;
    instr->COND = GETBITS(instruction, 28, 31);
    instr->I = GETBITS(instruction, 25, 25);
    instr->P = GETBITS(instruction, 24, 24);
    instr->U = GETBITS(instruction, 23, 23);
    instr->L = GETBITS(instruction, 20, 20);
    instr->REGN = GETBITS(instruction, 16, 19);
    instr->REGD = GETBITS(instruction, 12, 15);
    instr->OFFSET = GETBITS(instruction, 0, 11);
    //Assigning the opcode string based on the binary opcodes
    switch(instr->L) {
        case 0:
            strcpy(instr->OPCODE,"str");
            break;
        case 1:
            strcpy(instr->OPCODE,"ldr");
            break;
        default:
            break;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
// Decode the branch instructions into instruction structures by extracting corresponding
// bits to the strcuture using the GETBITS function
// PRE: branch instuction pointer and the 32-bit instruction
// POST: Contents of the structures are assigned to their corresponding bit in the instruction
/////////////////////////////////////////////////////////////////////////////////////////
void DecodeBranch(BRANCH_INSTR* instr, u32 instruction) {
    //Assigning the opcode string based on the binary opcodes
    strcpy(instr->OPCODE,"b");
    instr->INSTRUCTION = instruction;
    instr->COND = GETBITS(instruction, 28, 31);
    instr->OFFSET = GETBITS(instruction, 0, 23);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Helper fuction for printing the contents of a Dataprocessing instruction structure
// for testing purposes.
/////////////////////////////////////////////////////////////////////////////////////////
void printDataProcessing(DATAPROCESSING_INSTR* dp) {
    printf("Instruction %x\n", dp->INSTRUCTION);
    printf("Cond %x\n", dp->COND);
    printf("Opcode %s\n", dp->OPCODE);
    printf("S %d\n", dp->S);
    printf("I %d\n", dp->I);
    printf("Dest %d\n", dp->DEST);
    printf("Src %d\n", dp->SRC);
    printf("Operand2 %x\n", dp->OPERAND2);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Helper fuction for printing the contents of a Multiply instruction structure
// for testing purposes.
/////////////////////////////////////////////////////////////////////////////////////////
void printMultiply(MULTIPLY_INSTR* mp) {
    printf("Instruction %d\n",mp->INSTRUCTION);
    printf("Cond %d\n",mp->COND);
    printf("Opcode %s\n",mp->OPCODE);
    printf("S %d\n",mp->S);
    printf("A %d\n",mp->A);
    printf("Dest %d\n",mp->DEST);
    printf("RegM %d\n", mp->REGM);
    printf("RegS %d\n", mp->REGS);
    printf("Acc %d\n", mp->ACC);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Helper fuction for printing the contents of a single data transfer instruction structure
// for testing purposes.
/////////////////////////////////////////////////////////////////////////////////////////
void printSDT(SIN_DATA_TRAN_INSTR* sdt) {
    printf("Instruction %x\n",sdt->INSTRUCTION);
    printf("Cond %x\n",sdt->COND);
    printf("Opcode %s\n",sdt->OPCODE);
    printf("I %d\n",sdt->I);
    printf("L %d\n",sdt->L);
    printf("P %d\n",sdt->P);
    printf("U %d\n",sdt->U);
    printf("RegD %d\n", sdt->REGD);
    printf("RegN %d\n",sdt->REGN);
    printf("Offset %x\n",sdt->OFFSET);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Helper fuction for printing the contents of a branch instruction structure
// for testing purposes.
/////////////////////////////////////////////////////////////////////////////////////////
void printBranch(BRANCH_INSTR* br) {
    printf("Instruction %x\n",br->INSTRUCTION);
    printf("Cond %x\n",br->COND);
    printf("Opcode %s\n",br->OPCODE);
    printf("Offset %x\n",br->OFFSET);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Helper fuction for printing the contents of an instruction base on its type
/////////////////////////////////////////////////////////////////////////////////////////
void printDecodedInstruction(INSTRUCTION* instr) {
    if(strcmp(instr->type, "dataprocessing") == 0) {
        printDataProcessing(instr->instr.dp);
    } else if(strcmp(instr->type, "multiply") == 0) {
        printMultiply(instr->instr.mp);
    } else if(strcmp(instr->type, "singledatatransfer") == 0) {
        printSDT(instr->instr.sdt);
    } else if(strcmp(instr->type, "branch") == 0) {
        printBranch(instr->instr.br);
    }
}
