//
// Created by Timothy Cheuk on 06/06/2017.
//
#include "assemble.h"
#include "tokenizer.h"
#include "parser.h"


u32* assembleLdr(LINE_TOKEN* line_token, INSTRUCTION* instr){

    u32* address= NULL;

    //set opcode, destination register and also L flag
    strcopy(instr->instr.sdt->OPCODE,"ldr");;
    instr->instr.sdt->REGD = parseRegister( line_token->operands[0] );
    instr->instr.sdt->L = 1;
    if (line_token->*(operands + 1)[0] == '='){
        if(line_token->operands[1]<=0xFF){
            line_token->opcode='mov';
            assembleMov(line_token,instr);
        }
        else{
            /*some code here to store the numbers in four byte in memory*/
            line_token->operands[2] = ( PC );
            line_token->operands[3] = (difference_between_current_location_and_address);
            assembleLdr(line_token,instr);
        }
    }
    return address;
}

//finish the parts which is not optional
u32* assembleStr(LINE_TOKEN* line_token, INSTRUCTION* instr){

    u32* address;

    //set opcode, destination register and also L flag
    strcopy(instr->instr.sdt->OPCODE,"str");
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