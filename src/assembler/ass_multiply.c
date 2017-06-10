/////////////////////////////////////////////////////////////////////////////////////////
//C Group Project - First Year (2016-2017)
//File: ass_multiply.c
//Group: 6
//Member: Cheung, Ka (klc116), Mang, Hao (hxm16), Cheuk, Ki (kfc216), Chan, Chun (ckc116)
/////////////////////////////////////////////////////////////////////////////////////////
#include "parser.h"


void assembleMul(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    printf("Multiplying\n");
    strcpy(instr->type, "multiply");
    instr->instr.mp = malloc(sizeof(MULTIPLY_INSTR));
    instr->instr.mp->DEST = parseRegister(line_token->operands[0]);
    instr->instr.mp->REGM = parseRegister(line_token->operands[1]);
    instr->instr.mp->REGS = parseRegister(line_token->operands[2]);
    instr->instr.mp->A    = 0;
    instr->instr.mp->S    = 0;
    instr->instr.mp->COND = 0xe;
}

void assembleMla(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    printf("Multiplying\n");
    strcpy(instr->type, "multiply");
    instr->instr.mp = malloc(sizeof(MULTIPLY_INSTR));
    instr->instr.mp->DEST = parseRegister(line_token->operands[0]);
    instr->instr.mp->REGM = parseRegister(line_token->operands[1]);
    instr->instr.mp->REGS = parseRegister(line_token->operands[2]);
    instr->instr.mp->ACC  = parseRegister(line_token->operands[3]);
    instr->instr.mp->A    = 1;
    instr->instr.mp->S    = 0;
    instr->instr.mp->COND = 0xe;
}
