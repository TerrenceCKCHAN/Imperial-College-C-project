/////////////////////////////////////////////////////////////////////////////////////////
//C Group Project - First Year (2016-2017)
//File:emu_decode.c
//Group: 6
//Member: Cheung, Ka (klc116), Mang, Hao (hxm16), Cheuk, Ki (kfc216), Chan, Chun (ckc116)
/////////////////////////////////////////////////////////////////////////////////////////
#include "emulate.h"
#include "emu_decode.h"


void DecodeDataProcessing(DATAPROCESSING_INSTR* instr, u32 instruction) {
    instr->I            = GETBITS(instruction, 25, 25);
    instr->COND         = GETBITS(instruction, 28, 31);
    instr->S            = GETBITS(instruction, 20, 20);
    instr->INSTRUCTION  = instruction;
    instr->DEST         = GETBITS(instruction, 12, 15);
    instr->SRC          = GETBITS(instruction, 16, 19);
    instr->OPERAND2     = GETBITS(instruction, 0, 11);
    u32 opcode          = GETBITS(instruction, 21, 24);
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
    instr->A            = GETBITS(instruction, 21, 21);
    instr->INSTRUCTION  = instruction;
    instr->COND         = GETBITS(instruction, 28, 31);
    instr->S            = GETBITS(instruction, 20, 20);
    instr->DEST         = GETBITS(instruction, 16, 19);
    instr->REGM         = GETBITS(instruction, 0, 3);
    instr->REGS         = GETBITS(instruction, 8, 11);
    switch(instr->A) {
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
    instr->COND      = GETBITS(instruction, 28, 31);
    instr->I         = GETBITS(instruction, 25, 25);
    instr->P         = GETBITS(instruction, 24, 24);
    instr->U         = GETBITS(instruction, 23, 23);
    instr->L         = GETBITS(instruction, 20, 20);
    instr->REGN      = GETBITS(instruction, 16, 19);
    instr->REGD      = GETBITS(instruction, 12, 15);
    instr->OFFSET    = GETBITS(instruction, 0, 11);
    instr->INSTRUCTION = instruction;
    switch(instr->L) {
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
    printf("%d ", sdt->REGD);
    printf("%d\n", sdt->OFFSET);
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

void parseDataprocessing(DATAPROCESSING_INSTR* dp) {
    printf("instruction %x\n", dp->INSTRUCTION);
    printf("cond %x\n", dp->COND);
    printf("s %x\n", dp->S);
    printf("opcode %s\n", dp->OPCODE);
    printf("dest %x\n", dp->DEST);
    printf("src %x\n", dp->SRC);
    printf("operand2 %x\n", dp->OPERAND2);
}
