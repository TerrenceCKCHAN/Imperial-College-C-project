//
// Created by admin on 6/6/2017.
//

#include "assemble.h"
#include "tokenizer.h"
#include "parser.h"
#include "../emulator/instruction.h"
#include "../emulator/emulate.h"

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

u32 calculate(LINE_TOKEN* line_token, int i){
    u32 operand2=0;
    u32 val = parseExpression(line_token->operands[i]);
    u32 rotate_value = 0;
    while(val>0xff){
        if(rotate_value>0xff){
            printf("Error: can fit the number in 8 bit\n");
            break;
        }
        /*printf("Before ");
        printBit(val);*/
        val = RotateR(val,30);
        rotate_value+=1;
        /*printf("After  ");
        printBit(val);
        printf("\n");*/
        while((val&3)==0){
            val = RotateR(val,30);
            rotate_value+=1;
        }
    }
    /*while((val&3)==0){
        val = RotateR(val,30);
        rotate_value+=1;
    }*/
    operand2+=val;
    operand2+=rotate_value<<8;
    return operand2;
}


u32 shifting(LINE_TOKEN* line_token, int i){
    u32 operand2=0;
    operand2+=parseRegister(line_token->operands[i]);
    /*printf(line_token->operands[i+1]);
    printf("\n");*/
    if(line_token->numOfOperands>i+1) {
        if (strcmp(line_token->operands[i + 1], "lsl") == 0) {

        } else if (strcmp(line_token->operands[i + 1], "lsr") == 0) {
            operand2 += 1 << 5;
        } else if (strcmp(line_token->operands[i + 1], "asr") == 0) {
            operand2 += 2 << 5;
        } else if (strcmp(line_token->operands[i + 1], "ror") == 0) {
            operand2 += 3 << 5;
        } else {
            printf("Error: shift type not found\n");
        }

        if (line_token->operands[i + 2][0] == '#') {
            if (parseExpression(line_token->operands[i + 2]) > 0x1F) {
                printf("Error: shift integer too large\n");
            } else {
                operand2 += parseExpression(line_token->operands[i + 2]) << 7;
            }
        } else {
            operand2 += parseRegister(line_token->operands[i + 2]) << 8;
            operand2 += 1 << 4;
        }
    }
    return operand2;
}


//assume the operand 2 is an immediate value for now. can be ammend to support shifting
//helper method to avoid duplication
void assemble_instr_that_compute_results(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->DEST     = parseRegister(line_token->operands[0]);
    instr->instr.dp->SRC      = parseRegister(line_token->operands[1]);
    if (line_token->operands[2][0]=='#') {
        instr->instr.dp->I=1;
        instr->instr.dp->OPERAND2=calculate(line_token,2);
    }
    else{
        instr->instr.dp->I=0;
        instr->instr.dp->OPERAND2 = shifting(line_token, 2);

    }
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
        instr->instr.dp->OPERAND2=calculate(line_token,1);

    }
    else{
        instr->instr.dp->I=0;
        instr->instr.dp->OPERAND2=shifting(line_token,1);
    }
    instr->instr.dp->COND     = 0xe;
    instr->instr.dp->S        = 0;
    instr->instr.dp->OPCODEBIN = 0xd;
}
//helper method to avoid duplication
void assemble_set_flag_instructions(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->SRC      = parseRegister(line_token->operands[0]);
    if (line_token->operands[1][0]=='#') {
        instr->instr.dp->I=1;
        instr->instr.dp->OPERAND2 = calculate(line_token,1);
    }
    else{
        instr->instr.dp->I=0;
        instr->instr.dp->OPERAND2=shifting(line_token,1);
    }
    instr->instr.dp->S        = 1;
    instr->instr.dp->COND     = 0xe;
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
