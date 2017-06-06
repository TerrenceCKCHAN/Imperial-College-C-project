//
// Created by Timothy Cheuk on 06/06/2017.
//
#include "assemble.h"

INSTRUCTION* sin_data_transfer(LINE_TOKEN* token ){
    INSTRUCTION* instr = malloc(sizeof(INSTRUCTION));
    SIN_DATA_TRAN_INSTR* sdtr = malloc (sizeof(SIN_DATA_TRAN_INSTR));
    sdtr->OPCODE = token->operands[0];
    sdtr->REGD = token->operands[1];

    //if it is a load command
    if (token->operands[0] == "ldr") {
        //set L flag
        sdtr->L = 1;
    }

    //if it is a store command
    else if( token->operands[0] == "str" ){

        //clear L flag
        sdtr->L = 1;

    }

    int isinrect = 0;
    for (int i = 2; i < token->numOfOperands + 1; i++) {
        isinexp = 0;
        isinrect = 0;
        if (token->*(operands + i)[0] == '=') {
            isinexp = 1;
        } else if (token->*(operands + i)[0] == '[') {
            isinrect = 1;
        }

        if (isinexp) {

            //numeric expression is for ldr only
            if (token->operands[0] == "ldr") {

            } else {
                printf("Error: str with an numeric expression");
            }
        } else if (isinrect) {

        }
    }

    instr->instr = *sdtr;



    return instr;

}
