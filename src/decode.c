#include "emulate.h"
#include "decode.h"


void DecodeDataProcessing(DATAPROCESSING_INSTR* instr, u32 instruction) {
    u32 i               = GETBITS(instruction, 25, 25);
    u32 opcode          = GETBITS(instruction, 21, 24);
    instr->COND         = GETBITS(instruction, 28, 31);
    instr->S            = GETBITS(instruction, 20, 20);
    instr->INSTRUCTION  = instruction;
    instr->DEST         = GETBITS(instruction, 12, 15);
    instr->SRC          = GETBITS(instruction, 16, 19);
    instr->OPERAND2     = GETBITS(instruction, 0, 11);
    switch(opcode) {
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
    }
}

void DecodeMultiply(MULTIPLY_INSTR* instr, u32 instruction) {
    u32 a               = GETBITS(instruction, 21, 21);
    instr->INSTRUCTION  = instruction;
    instr->COND         = GETBITS(instruction, 28, 31);
    instr->S            = GETBITS(instruction, 20, 20);
    instr->DEST         = GETBITS(instruction, 16, 19);
    instr->REGM         = GETBITS(instruction, 0, 3);
    instr->REGS         = GETBITS(instruction, 8, 11);
    switch(a) {
        case 0:
            strcpy(instr->OPCODE,"mul");
            instr->ACC = NOT_EXIST;
            break;
        case 1:
            strcpy(instr->OPCODE,"mla");
            instr->ACC = GETBITS(instruction, 12, 15);
            break;
    }
}

void DecodeSingleDataTransfer(SIN_DATA_TRAN_INSTR* instr, u32 instruction) {
    u32 cond      = GETBITS(instruction, 28, 31);
    u32 i         = GETBITS(instruction, 25, 25);
    u32 p         = GETBITS(instruction, 24, 24);
    u32 u         = GETBITS(instruction, 23, 23);
    u32 l         = GETBITS(instruction, 20, 20);
    u32 regn      = GETBITS(instruction, 16, 19);
    u32 regd      = GETBITS(instruction, 12, 15);
    u32 offset    = GETBITS(instruction, 0, 11);
    instr->INSTRUCTION = instruction;
    instr->COND = cond;
    instr->REG = regd;
    instr->ADDRESS = offset;
    switch(l) {
        case 0:
            strcpy(instr->OPCODE,"str");
            break;
        case 1:
            strcpy(instr->OPCODE,"ldr");
            break;
    }
}

void DecodeBranch(BRANCH_INSTR* instr, u32 instruction) {
    strcpy(instr->OPCODE,"b");
    instr->INSTRUCTION = instruction;
    instr->COND      = GETBITS(instruction, 28, 31);
    instr->OFFSET    = GETBITS(instruction, 0, 23);
}

void printDataProcessing(DATAPROCESSING_INSTR* dp) {
    printf("%s ",dp->OPCODE);
    if(dp->DEST != NOT_EXIST) {
        printf("r%d,",dp->DEST);
    }
    if(dp->SRC != NOT_EXIST) {
        printf("r%d,",dp->SRC);
    }
    printf("#%x\n",dp->OPERAND2);
}

void printMultiply(MULTIPLY_INSTR* mp) {
    printf("%s ",mp->OPCODE);
    printf("%d ",mp->DEST);
    printf("%d ",mp->REGM);
    if(mp->ACC != NOT_EXIST) {
        printf("%d %d\n", mp->REGS, mp->ACC);
    } else {
        printf("%d\n",mp->REGS);
    }
}

void printSDT(SIN_DATA_TRAN_INSTR* sdt) {
    printf("%s ",sdt->OPCODE);
    printf("%d ", sdt->REG);
    printf("%d\n", sdt->ADDRESS);
}

void printBranch(BRANCH_INSTR* br) {
    printf("%s",br->OPCODE);
    switch(br->COND) {
        case eq:
            printf("eq");
            break;
        case ne:
            printf("ne");
            break;
        case ge:
            printf("ge");
            break;
        case lt:
            printf("lt");
            break;
        case gt:
            printf("gt");
            break;
        case le:
            printf("le");
            break;
        case al:
            break;
    }
    printf(" %x\n",br->OFFSET);
}

