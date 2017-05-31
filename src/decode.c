#include "emulate.h"
#include "decode.h"

void DecodeDataProcessing(DATAPROCESSING* instr, u32 instruction) {
    instr->COND     = GETBITS(instruction, 28, 31);
    instr->I        = GETBITS(instruction, 25, 25);
    instr->OPCODE   = GETBITS(instruction, 21, 24);
    instr->S        = GETBITS(instruction, 20, 20);
    instr->REGN     = GETBITS(instruction, 16, 19);
    instr->REGD     = GETBITS(instruction, 12, 15);
    instr->OPRAND2  = GETBITS(instruction, 0, 11);
}

void DecodeMultiply(MULTIPLY* instr, u32 instruction) {
    instr->COND     = GETBITS(instruction, 28, 31);
    instr->A        = GETBITS(instruction, 21, 21);
    instr->S        = GETBITS(instruction, 20, 20);
    instr->REGD     = GETBITS(instruction, 16, 19);
    instr->REGN     = GETBITS(instruction, 12, 15);
    instr->REGS     = GETBITS(instruction, 8, 11);
    instr->REGM     = GETBITS(instruction, 0, 3);
}

void DecodeSingleDataTransfer(SIN_DATA_TRAN* instr, u32 instruction) {
    instr->COND      = GETBITS(instruction, 28, 31);
    instr->I         = GETBITS(instruction, 25, 25);
    instr->P         = GETBITS(instruction, 24, 24);
    instr->U         = GETBITS(instruction, 23, 23);
    instr->L         = GETBITS(instruction, 20, 20);
    instr->REGN      = GETBITS(instruction, 16, 19);
    instr->REGD      = GETBITS(instruction, 12, 15);
    instr->OFFSET    = GETBITS(instruction, 0, 11);
}

void DecodeBranch(BRANCH* instr, u32 instruction) {
    instr->COND      = GETBITS(instruction, 28, 31);
    instr->OFFSET    = GETBITS(instruction, 0, 23);
}

void printDataProcessing(DATAPROCESSING* dp) {
    printf("COND %x\n",dp->COND);
    printf("I %x\n",dp->I);
    printf("OPCODE %x\n",dp->OPCODE);
    printf("S %x\n",dp->S);
    printf("REGN %x\n",dp->REGN);
    printf("REGD %x\n",dp->REGD);
    printf("OPRAND2 %x\n",dp->OPRAND2);
}

void printMultiply(MULTIPLY* mp) {
    printf("COND %x\n",mp->COND);
    printf("A %x\n",mp->A);
    printf("S %x\n",mp->S);
    printf("REGD %x\n",mp->REGD);
    printf("REGN %x\n",mp->REGN);
    printf("REGS %x\n",mp->REGS);
    printf("REGM %x\n",mp->REGM);
}

void printSDT(SIN_DATA_TRAN* sdt) {
    printf("COND %x\n",sdt->COND);
    printf("I %x\n",sdt->I);
    printf("P %x\n",sdt->P);
    printf("U %x\n",sdt->U);
    printf("L %x\n",sdt->L);
    printf("REGN %x\n",sdt->REGN);
    printf("REGD %x\n",sdt->REGD);
    printf("OFFSET %x\n",sdt->OFFSET);
}

void printBranch(BRANCH* br) {
    printf("COND %x\n",br->COND);
    printf("OFFSET %x\n",br->OFFSET);
}

