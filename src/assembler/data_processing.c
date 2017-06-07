//
// Created by admin on 6/6/2017.
//

#include "assemble.h"
#include "tokenizer.h"
#include "parser.h"
#include "../emulator/instruction.h"

/*typedef struct {
    u32 INSTRUCTION;
    char OPCODE[4];
    u32 COND: 4;
    u32 S:1;
    u32 I:1;
    u32 DEST;
    u32 SRC;
    u32 OPERAND2;
}DATAPROCESSING_INSTR;*/





//assume the operand 2 is an immediate value for now. can be ammend to support shifting
//helper method to avoid duplication
void assemble_instr_that_compute_results(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->DEST     = parseRegister(line_token->operands[0]);
    instr->instr.dp->SRC      = parseRegister(line_token->operands[1]);
    instr->instr.dp->OPERAND2 = parseExpression(line_token->operands[2]);
    instr->instr.dp->I        = 1;
    instr->instr.dp->S        = 0;
    instr->instr.dp->COND     = 0xe;

}

void assembleAdd(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    strcpy(instr->instr.dp->OPCODE, "add");
    instr->instr.dp->OPCODEBIN = 0x4;
    assemble_instr_that_compute_results(line_token, instr);


}

void assembleSub(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    strcpy(instr->instr.dp->OPCODE, "sub");
    instr->instr.dp->OPCODEBIN = 0x2;
    assemble_instr_that_compute_results(line_token, instr);
}

void assembleRsb(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    strcpy(instr->instr.dp->OPCODE, "rsb");
    instr->instr.dp->OPCODEBIN = 0x3;
    assemble_instr_that_compute_results(line_token, instr);
}

void assembleAnd(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    strcpy(instr->instr.dp->OPCODE, "and");
    instr->instr.dp->OPCODEBIN = 0x0;
    assemble_instr_that_compute_results(line_token, instr);
}

void assembleEor(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    strcpy(instr->instr.dp->OPCODE, "eor");
    instr->instr.dp->OPCODEBIN = 0x1;
    assemble_instr_that_compute_results(line_token, instr);
}

void assembleOrr(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    strcpy(instr->instr.dp->OPCODE, "orr");
    instr->instr.dp->OPCODEBIN = 0xc;
    assemble_instr_that_compute_results(line_token, instr);
}

void assembleMov(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->DEST     = parseRegister(line_token->operands[0]);
    if (line_token->operands[1][0]=='#') {
        instr->instr.dp->I=1;
        instr->instr.dp->OPERAND2 = parseExpression(line_token->operands[1]);
    }
    instr->instr.dp->COND     = 0xe;
    instr->instr.dp->S        = 0;
    instr->instr.dp->OPCODEBIN = 0xd;
}
//helper method to avoid duplication
void assemble_set_flag_instructions(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->SRC      = parseRegister(line_token->operands[1]);
    instr->instr.dp->OPERAND2 = parseExpression(line_token->operands[2]);
    instr->instr.dp->S        = 1;
}

void assembleTst(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    strcpy(instr->instr.dp->OPCODE, "tst");
    instr->instr.dp->OPCODEBIN = 0x8;
    assemble_set_flag_instructions(line_token, instr);
}

void assembleTeq(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    strcpy(instr->instr.dp->OPCODE, "teq");
    instr->instr.dp->OPCODEBIN = 0x9;
    assemble_set_flag_instructions(line_token, instr);
}

void assembleCmp(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    strcpy(instr->instr.dp->OPCODE, "cmp");
    instr->instr.dp->OPCODEBIN = 0xa;
    assemble_set_flag_instructions(line_token, instr);
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
