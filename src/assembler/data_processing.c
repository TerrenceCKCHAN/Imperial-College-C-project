//
// Created by admin on 6/6/2017.
//

#include "assemble.h";
#include "tokenizer.h"

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


//assume there is a field OPCODEBIN in struct DATAPROCESSING
void setOpCodeBin (INSTRUCTION* instr) {
    switch (instr->instr.dp->OPCODE) {
        case "and" :
            instr->instr.dp->OPCODEBIN = 0000;
        case "eor" :
            instr->instr.dp->OPCODEBIN = 0001;
        case "sub" :
            instr->instr.dp->OPCODEBIN = 0010;
        case "rsb" :
            instr->instr.dp->OPCODEBIN = 0011;
        case "add" :
            instr->instr.dp->OPCODEBIN = 0100;
        case "orr" :
            instr->instr.dp->OPCODEBIN = 1100;
        case "mov" :
            instr->instr.dp->OPCODEBIN = 1101;
        case "tst" :
            instr->instr.dp->OPCODEBIN = 1000;
        case "teq" :
            instr->instr.dp->OPCODEBIN = 1001;
        case "cmp" :
            instr->instr.dp->OPCODEBIN = 1010;
    }
}

//assume the operand 2 is an immediate value for now. can be ammend to support shifting
//helper method to avoid duplication
void assemble_instr_that_compute_results(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->DEST     = parseRegister(line_token->operands[0]);
    instr->instr.dp->SRC      = parseRegister(line_token->operands[1]);
    instr->instr.dp->OPERAND2 = parseExpression(line_token->operands[2]);
    instr->instr.dp->I        = 1;
    instr->instr.dp->S        = 0;
    instr->instr.dp->COND     = 1110;
    //instr->instr.dp->OPCODE must be set before using setOpCodeBin
    setOpCodeBin (instr);

}

void assembleAdd(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->OPCODE   = "add";
    assemble_instr_that_compute_results(line_token, instr);
}

void assembleSub(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->OPCODE   = "sub";
    assemble_instr_that_compute_results(line_token, instr);
}

void assembleRsb(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->OPCODE   = "rsb";
    assemble_instr_that_compute_results(line_token, instr);
}

void assembleAnd(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->OPCODE   = "and";
    assemble_instr_that_compute_results(line_token, instr);
}

void assembleEor(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->OPCODE   = "eor";
    assemble_instr_that_compute_results(line_token, instr);
}

void assembleOrr(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->OPCODE   = "orr";
    assemble_instr_that_compute_results(line_token, instr);
}

void assembleMov(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->DEST     = parseRegister(line_token->operands[0]);
    instr->instr.dp->OPERAND2 = parseExpression(line_token->operands[2]);
    instr->instr.dp->COND     = 1110;
    instr->instr.dp->S        = 0;
    setOpCodeBin (instr);
}
//helper method to avoid duplication
void assemble_set_flag_instructions(LINE_TOKEN* line_token, INTSRUCTION* instr) {
    instr->instr.dp->SRC      = parseRegister(line_token->operands[1]);
    instr->instr.dp->OPERAND2 = parseExpression(line_token->operands[2]);
    instr->instr.dp->S        = 1;
    setOpCodeBin (instr);
}

void assembleTst(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->OPCODE   ="tst";
    assemble_set_flag_instructions(line_token, instr);
}

void assembleTeq(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->OPCODE   ="teq";
    assemble_set_flag_instructions(line_token, instr);
}

void assembleCmp(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->OPCODE   ="cmp";
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