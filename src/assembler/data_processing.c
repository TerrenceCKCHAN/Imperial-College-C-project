//
// Created by admin on 6/6/2017.
//

#include "assemble.h";
#include "tokenizer.h"


void assembleAdd(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->OPCODE   = "add";
    instr->instr.dp->DEST     = parseRegister(line_token->operands[0]);
    instr->instr.dp->SRC      = parseRegister(line_token->operands[1]);
    instr->instr.dp->OPERAND2 = parseExpression(line_token->operands[2]);
    instr->instr.dp->COND     = 1110 << 28;
}
void assembleSub(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->OPCODE   = "sub";
    instr->instr.dp->DEST     = parseRegister(line_token->operands[0]);
    instr->instr.dp->SRC      = parseRegister(line_token->operands[1]);
    instr->instr.dp->OPERAND2 = parseExpression(line_token->operands[2]);
    instr->instr.dp->COND     = 1110 << 28;
}
void assembleRsb(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->OPCODE   = "rsb";
    instr->instr.dp->DEST     = parseRegister(line_token->operands[0]);
    instr->instr.dp->SRC      = parseRegister(line_token->operands[1]);
    instr->instr.dp->OPERAND2 = parseExpression(line_token->operands[2]);
    instr->instr.dp->COND     = 1110 << 28;
}
void assembleAnd(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->OPCODE   = "and";
    instr->instr.dp->DEST     = parseRegister(line_token->operands[0]);
    instr->instr.dp->SRC      = parseRegister(line_token->operands[1]);
    instr->instr.dp->OPERAND2 = parseExpression(line_token->operands[2]);
    instr->instr.dp->COND     = 1110 << 28;
}
void assembleEor(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->OPCODE   = "eor";
    instr->instr.dp->DEST     = parseRegister(line_token->operands[0]);
    instr->instr.dp->SRC      = parseRegister(line_token->operands[1]);
    instr->instr.dp->OPERAND2 = parseExpression(line_token->operands[2]);
    instr->instr.dp->COND     = 1110 << 28;
}
void assembleOrr(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->OPCODE   = "orr";
    instr->instr.dp->DEST     = parseRegister(line_token->operands[0]);
    instr->instr.dp->SRC      = parseRegister(line_token->operands[1]);
    instr->instr.dp->OPERAND2 = parseExpression(line_token->operands[2]);
    instr->instr.dp->COND     = 1110 << 28;
}
void assembleMov(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->DEST     = parseRegister(line_token->operands[0]);
    instr->instr.dp->OPERAND2 = parseExpression(line_token->operands[2]);
    instr->instr.dp->COND     = 1110 << 28;
}

void assembleTst(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->OPCODE   ="tst";
    instr->instr.dp->SRC      = parseRegister(line_token->operands[1]);
    instr->instr.dp->OPERAND2 = parseExpression(line_token->operands[2]);
}
void assembleTeq(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->OPCODE   ="teq";
    instr->instr.dp->SRC      = parseRegister(line_token->operands[1]);
    instr->instr.dp->OPERAND2 = parseExpression(line_token->operands[2]);
}
void assembleCmp(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->OPCODE   ="cmp";
    instr->instr.dp->SRC      = parseRegister(line_token->operands[1]);
    instr->instr.dp->OPERAND2 = parseExpression(line_token->operands[2]);
}

//This is the implementation for one single dataProcessing function that cover all the cases.
/*
INSTRUCTION *dataProcessing(LINE_TOKEN *line_token) {
    INSTRUCTION *instr = malloc(sizeof(INSTRUCTION));


        // This is the case for Instructions that do not compute results
    if (line_token->opcode == "tst" | "teq" | "cmp") {
        instr->instr.dp->SRC      = line_token->operands[1];
        instr->instr.dp->OPERAND2 = line_token->operands[2];
    }
        // This is the case for Single operand assignment:mov
    else if (line_token->opcode == "mov") {
        instr->instr.dp->DEST     = line_token->operands[0];
        instr->instr.dp->OPERAND2 = line_token->operands[2];
        instr->instr.dp->COND     = 1110 << 28;

    }
        // This is the case for instructions that compute results
    else {
        instr->instr.dp->OPCODE   = line_token->opcode;
        instr->instr.dp->DEST     = line_token->operands[0];
        instr->instr.dp->SRC      = line_token->operands[1];
        instr->instr.dp->OPERAND2 = line_token->operands[2];
        instr->instr.dp->COND     = 1110 << 28;
    }

    return instr;
}*/
