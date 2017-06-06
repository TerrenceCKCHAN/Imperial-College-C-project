//
// Created by admin on 6/6/2017.
//

#include "assemble.h";
#include "tokenizer.h"

void dataProcessing(LINE_TOKEN *line_token) {
    INSTRUCTION *instr = malloc(sizeof(INSTRUCTION));


    // This is the case for Instructions that do not compute results
    if (line_token->operands[0] == NULL) {
        instr->instr.dp->SRC      = line_token->operands[1];
        instr->instr.dp->OPERAND2 = line_token->operands[2];

    }
        // This is the case for Single operand assignment:mov
    else if (line_token->operands[1] == NULL) {

        instr->instr.dp->DEST     = line_token->operands[0];
        instr->instr.dp->OPERAND2 = line_token->operands[2]
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


}