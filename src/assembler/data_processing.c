//
// Created by admin on 6/6/2017.
//

#include "assemble.h";
#include "tokenizer.h"

void dataProcessing(LINE_TOKEN *line_token) {
    enum TOKEN_TYPE type = line_token->type;
    char label           = line_token->label;
    char opcode          = line_token->opcode;
    char *operands       = line_token->operands;
    int  numOfOperands   = line_token->numOfOperands;

    // This is the case for Instructions that do not compute results
    if (operands[0] == NULL) {

    }
    // This is the case for Single operand assignment:mov
    else if (operands[1] == NULL) {

    }
    // This is the case for instructions that compute results
    else {
        switch (opcode) {
            
        }



    }


}