//
// Created by admin on 6/6/2017.
//

#include "parser.h";
#include "assemble.h";
#include "tokenizer.h";



void assembleMul(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.mp->DEST = parseRegister(line_token->operands[0]);
    instr->instr.mp->REGM = parseRegister(line_token->operands[1]);
    instr->instr.mp->REGS = parseRegister(line_token->operands[2]);
    instr->instr.mp->A    = 0;
    instr->instr.mp->S    = 0;
    instr->instr.mp->COND = 1110;
}

void assembleMla(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.mp->DEST = parseRegister(line_token->operands[0]);
    instr->instr.mp->REGM = parseRegister(line_token->operands[1]);
    instr->instr.mp->REGS = parseRegister(line_token->operands[2]);
    instr->instr.mp->ACC  = parseRegister(line_token->operands[3]);
    instr->instr.mp->S    = 0;
    instr->instr.mp->COND = 1110;
}
