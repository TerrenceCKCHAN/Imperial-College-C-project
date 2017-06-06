//
// Created by admin on 6/6/2017.
//

#include "assemble.h";
#include "tokenizer.h"

void dataProcessing(LINE_TOKEN *line_token) {
    INSTRUCTION *instr = malloc(sizeof(INSTRUCTION));

    u32 Cond;
    u32 I;
    char OpCode;
    u32 S;
    u32 Rn;
    u32 Rd;
    u32 Operand2;

    // This is the case for Instructions that do not compute results
    if (operands[0] == NULL) {

    }
    // This is the case for Single operand assignment:mov
    else if (operands[1] == NULL) {

    }
    // This is the case for instructions that compute results
    else {
        instr->instr.dp->OPCODE == line_token->opcode;
    }

}