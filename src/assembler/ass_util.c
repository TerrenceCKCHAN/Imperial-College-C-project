/////////////////////////////////////////////////////////////////////////////////////////
//C Group Project - First Year (2016-2017)
//File: ass_util.c
//Group: 6
//Member: Cheung, Ka (klc116), Mang, Hao (hxm16), Cheuk, Ki (kfc216), Chan, Chun (ckc116)
/////////////////////////////////////////////////////////////////////////////////////////
#include "assemble.h"

/////////////////////////////////////////////////////////////////////////////////////////
//Return a 32bit instruction after getting the instruction structure pointer
/////////////////////////////////////////////////////////////////////////////////////////

u32 assembleInstructions(INSTRUCTION* instr) {
    u32 instruction = 0;
    if(strcmp(instr->type, "dataprocessing") == 0) {
        instruction |= instr->instr.dp->OPERAND2;
        instruction |= instr->instr.dp->DEST << 12;
        instruction |= instr->instr.dp->SRC << 16;
        instruction |= instr->instr.dp->S << 20;
        instruction |= instr->instr.dp->OPCODEBIN << 21;
        instruction |= instr->instr.dp->I << 25;
        instruction |= instr->instr.dp->COND << 28;
    } else if(strcmp(instr->type, "multiply") == 0) {
        instruction |= instr->instr.mp->REGM;
        instruction |= 9 << 4;
        instruction |= instr->instr.mp->REGS << 8;
        instruction |= instr->instr.mp->ACC << 12;
        instruction |= instr->instr.mp->DEST << 16;
        instruction |= instr->instr.mp->S << 20;
        instruction |= instr->instr.mp->A << 21;
        instruction |= instr->instr.mp->COND << 28;
    } else if(strcmp(instr->type, "singledatatransfer") == 0) {
        instruction |= instr->instr.sdt->OFFSET;
        instruction |= instr->instr.sdt->REGD << 12;
        instruction |= instr->instr.sdt->REGN << 16;
        instruction |= instr->instr.sdt->L << 20;
        instruction |= instr->instr.sdt->U << 23;
        instruction |= instr->instr.sdt->P << 24;
        instruction |= instr->instr.sdt->I << 25;
        instruction |= 1 << 26;
        instruction |= instr->instr.sdt->COND << 28;
    } else if(strcmp(instr->type, "branch") == 0) {
        instruction |= instr->instr.br->OFFSET;
        instruction |= 0xa << 24;
        instruction |= instr->instr.br->COND << 28;
    } else if(strcmp(instr->type, "halt") == 0) {
        instruction = 0;
    }
    return instruction;
}