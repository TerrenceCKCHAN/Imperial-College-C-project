//
// Created by Timothy Cheuk on 06/06/2017.
//
#include "assemble.h"
#include "tokenizer.h"
#include "parser.h"
#include "../emulator/instruction.h"

//void parseExpressioninrect(EXP_IN_RECT* exp_in_rect, LINE_TOKEN* line_token){
//    int i = 1;
//    int expinrect = 0;
//    int expnotinrect = 0;
//    while(line_token->operands[i] != NULL){
//        if (line_token->operands[i][0]=='[' ){
//            line_token->operands[i] ++;
//            exp_in_rect->exp_in_rect[expinrect] = line_token->operands[i];
//            expinrect++;
//        }else if(line_token->operands[i][strlen(line_token->operands[i])-1]==']'){
//            exp_in_rect->exp_in_rect[expinrect] = line_token->operands[i];
//            expinrect++;
//        }
//        else {
//            exp_in_rect->exp_in_rect[expnotinrect] = line_token->operands[expnotinrect];
//            expnotinrect++;
//        }
//        i++;
//    }
//    exp_in_rect->exp_in_rect_int=expinrect;
//    exp_in_rect->exp_not_in_rect_int=expnotinrect;
//}

void parseExpressioninrect(EXP_IN_RECT* exp_in_rect, LINE_TOKEN* line_token){
    int i = 1;
    int expinrect = 0;
    int expnotinrect = 0;
    int inrect=1;
    while(line_token->operands[i] != NULL){
        if (line_token->operands[i][0]=='[' && line_token->operands[i][strlen(line_token->operands[i])-1]==']'){
            inrect=0;
            line_token->operands[i] ++;
            exp_in_rect->exp_in_rect[expinrect] = line_token->operands[i];
            expinrect++;
        } else if (line_token->operands[i][0]=='[' ){
            inrect=1;
            line_token->operands[i] ++;
            exp_in_rect->exp_in_rect[expinrect] = line_token->operands[i];
            expinrect++;
        } else if(line_token->operands[i][strlen(line_token->operands[i])-1]==']'){
            inrect=0;
            exp_in_rect->exp_in_rect[expinrect] = line_token->operands[i];
            expinrect++;
        }
        else if(inrect){
            exp_in_rect->exp_in_rect[expinrect] = line_token->operands[i];
            expinrect++;
        }
        else {
            exp_in_rect->exp_in_rect[expnotinrect] = line_token->operands[expnotinrect];
            expnotinrect++;
        }
        i++;
    }
    exp_in_rect->exp_in_rect_int=expinrect;
    exp_in_rect->exp_not_in_rect_int=expnotinrect;
}
u32 shifting1(LINE_TOKEN* line_token, int i){
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

void calculate2(LINE_TOKEN *line_token, int i, INSTRUCTION *instr) {

    if(line_token->operands[i][0] == '+' | line_token->operands[i][0] == '-'){
        if(line_token->operands[i][0] == '+'){
            instr->instr.sdt->U=1;
        }
        else{
            instr->instr.sdt->U=0;
        }
        line_token->operands[i]++;
        instr->instr.sdt->OFFSET=shifting1(line_token,i);
    }
    else{
        instr->instr.sdt->U=1;
        instr->instr.sdt->OFFSET=shifting1(line_token,i);
    }
}

void calculate1(LINE_TOKEN *line_token, int i, INSTRUCTION *instr, u32 address, u32 numofinstr) {
    u32 operand2=0;
    u32 val;
    if(line_token -> operands[i][1] == '-'){
        line_token->operands[i]++;
        val = parseExpression(line_token->operands[i]);
        instr->instr.sdt->U = 0;
    }
    else {
        val = parseExpression(line_token->operands[i]);
        instr->instr.sdt->U = 1;
    }
    u32 rotate_value = 0;
    while(val>0xff){
        if(rotate_value>0xff){
            instr->instr.sdt->REGN=15;
            Memory[memoryPos] = parseExpression(line_token->operands[i]);
            val = (numofinstr+memoryPos)*4 - address - 8;
            memoryPos++;
            rotate_value = 0;
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
    instr->instr.sdt->OFFSET=operand2;
}

void assembleLdr(LINE_TOKEN *line_token, INSTRUCTION *instr, u32 address, u32 numOfInstructions) {

    //allocate memory for instr->instr.sdt
    strcpy(instr->type,"singledatatransfer");
    instr->instr.sdt = malloc(sizeof(SIN_DATA_TRAN_INSTR));

    //set opcode, destination register and also L flag
    strcpy(instr->instr.sdt->OPCODE,"ldr");
    instr->instr.sdt->COND = 0xe;
    instr->instr.sdt->REGD = parseRegister(line_token->operands[0]);
    instr->instr.sdt->L = 1;

    if (line_token->operands[1][0] == '='){

        if(parseExpression(line_token->operands[1])<=0xFF){
            line_token->operands[1][0] = '#';
            strcpy(line_token->str.opcode, "mov");
            assembleMov(line_token, instr);
        }
        else{
            calculate1(line_token, 1, instr, address, numOfInstructions);
            instr->instr.sdt->P=1;
        }
    }
    else{
        EXP_IN_RECT *exp_in_rect = malloc(sizeof(EXP_IN_RECT));
        parseExpressioninrect(exp_in_rect, line_token);
        instr->instr.sdt->REGN   = parseRegister(line_token->operands[1]);
        if(exp_in_rect->exp_not_in_rect_int == 0 && exp_in_rect->exp_in_rect_int == 1){
            instr->instr.sdt->REGN   = parseRegister(exp_in_rect->exp_in_rect[0]);
            printf(exp_in_rect->exp_in_rect[0]);
            instr->instr.sdt->OFFSET = 0;
            instr->instr.sdt->P      = 1;
        } else if(exp_in_rect->exp_not_in_rect_int == 0 && exp_in_rect->exp_in_rect_int == 2){
            if(line_token->operands[2][0]=='#') {
                printf("hi");
                instr->instr.sdt->I=0;
                calculate1(line_token, 2, instr, address, numOfInstructions);
            }
            else{
                instr->instr.sdt->I=1;
                calculate2(line_token, 2, instr);
            }
            instr->instr.sdt->P      = 1;
        } else if(exp_in_rect->exp_not_in_rect_int == 1 && exp_in_rect->exp_in_rect_int == 1){
            instr->instr.sdt->REGN=parseRegister(line_token->operands[1]);
            if(line_token->operands[2][0]=='#') {
                instr->instr.sdt->I=0;
                calculate1(line_token, 2, instr, address, numOfInstructions);
            }
            else{
                instr->instr.sdt->I=1;
                calculate2(line_token, 2,instr);
            }
            instr->instr.sdt->P      = 0;
        }
    }
}

//finish the parts which is not optional
void assembleStr(LINE_TOKEN *line_token, INSTRUCTION *instr, u32 address, u32 numOfInstructions) {
    strcpy(instr->type,"singledatatransfer");
    //allocate memory for instr->instr.sdt
    instr->instr.sdt = malloc(sizeof(SIN_DATA_TRAN_INSTR));

    //set opcode, destination register and also L flag
    instr->instr.sdt->COND = 0xe;
    strcpy(instr->instr.sdt->OPCODE,"str");
    instr->instr.sdt->REGD = parseRegister(line_token->operands[0]);
    instr->instr.sdt->L=0;
    instr->instr.sdt->U = 1;
    EXP_IN_RECT *exp_in_rect = malloc(sizeof(EXP_IN_RECT));
    parseExpressioninrect(exp_in_rect, line_token);
    if(exp_in_rect->exp_not_in_rect_int==0 && exp_in_rect->exp_in_rect_int==1){
        instr->instr.sdt->I = 1;
        instr->instr.sdt->REGN=parseRegister(line_token->operands[1]);
        instr->instr.sdt->OFFSET=0;
        instr->instr.sdt->P=1;
    }
    else if(exp_in_rect->exp_not_in_rect_int==0 && exp_in_rect->exp_in_rect_int==2){
        instr->instr.sdt->I = 1;
        instr->instr.sdt->REGN=parseRegister(line_token->operands[1]);
        if(line_token->operands[2][0]=='#') {
            instr->instr.sdt->I=0;
            calculate1(line_token, 2, instr, address, numOfInstructions);
        }
        else{
            instr->instr.sdt->I=1;
            calculate2(line_token, 2, instr);
        }
        instr->instr.sdt->P=1;
    }
    else if(exp_in_rect->exp_not_in_rect_int == 1 && exp_in_rect->exp_in_rect_int == 1){
        instr->instr.sdt->REGN=parseRegister(line_token->operands[1]);
        if(line_token->operands[2][0]=='#') {
            instr->instr.sdt->I=0;
            calculate1(line_token, 2, instr, address, numOfInstructions);
        }
        else{
            instr->instr.sdt->I=1;
            calculate2(line_token, 2, instr);
        }
        instr->instr.sdt->P      = 0;
    }

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