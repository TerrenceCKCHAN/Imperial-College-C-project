//
// Created by Timothy Cheuk on 06/06/2017.
//
#include "assemble.h"
#include "tokenizer.h"
#include "parser.h"

/*INSTRUCTION* sin_data_transfer(LINE_TOKEN* token ){
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

    if (token->numOfOperands= 1) {
        if (token->*(operands+2)[0]== '='){

        }
        else if (token->*(operands+2)[0]== '['){

            }
    }

    instr->instr = *sdtr;



    return instr;

}*/

u32* assembleLdr(LINE_TOKEN* line_token, INSTRUCTION* instr){

    u32* address= NULL;

    //set opcode, destination register and also L flag
    instr->instr.sdt->OPCODE="ldr";
    instr->instr.sdt->REGD = parseRegister( line_token->operands[0] );
    instr->instr.sdt->L = 1;
    int i = 1;
    while(link_token->operands[i]!= NULL) {
        if (line_token->*(operands + 1)[0] == '='){
            if(line_token->operands[1]<=0xFF){
                line_token->opcode='mov';
                assembleMov(line_token,instr);
            }
            else{

                assembleLdr(line_token,instr);
            }
        } else if (line_token->*(operands + 1)[0] == '[') {
            if(line_token->numOfOperands=1){
                instr->instr.sdt->REGN=parseRegister(line_token->operands[i]);
            } else{

            }
        }
        i++;
    }
    return address;
}
u32* assembleStr(LINE_TOKEN* line_token, INSTRUCTION* instr){

    u32* address;

    //set opcode, destination register and also L flag
    instr->instr.sdt->OPCODE="str";
    instr->instr.sdt->REGD = parseRegister(line_token->operands[0]);
    instr->instr.sdt->L=0;



    return address;
}



/*
 * typedef struct sdt{
    u32 INSTRUCTION;
    char OPCODE[4];
    u32 COND: 4;
    u32 REGD;
    u32 REGN;
    u32 OFFSET;
    u32 I: 1;
    u32 P: 1;
    u32 U: 1;
    u32 L: 1;
}SIN_DATA_TRAN_INSTR;
 */