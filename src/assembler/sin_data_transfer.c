//
// Created by Timothy Cheuk on 06/06/2017.
//
#include "assemble.h"
#include "tokenizer.h"
#include "parser.h"

EXP_IN_RECT* parseExpressioninrect(LINE_TOKEN* line_token){
    EXP_IN_RECT* exp_in_rect = malloc(sizeof(EXP_IN_RECT));
    int i = 1;
    int j = 0;
    int k = 0;
    while(operand[i] != NULL){
        if (*(operand+i)[0]=='[' | *(operand+i)[strlen(*(operand+i))-1]==']'){
            exp_in_rect->exp_in_rect[j] = operand[i];
            j++;
        }
        else{
            exp_in_rect->exp_in_rect[k] = operand[k];
            k++;
        }
        i++;
    }
    exp_in_rect->exp_in_rect_int=j;
    exp_in_rect->exp_not_in_rect_int=k;
    return exp_in_rect;
}

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

void assemble_Ldr(LINE_TOKEN* line_token, INSTRUCTION* instr){

    u32* address= NULL;

    //set opcode, destination register and also L flag
    strcpy(instr->instr.sdt->OPCODE,"ldr");;
    instr->instr.sdt->REGD = parseRegister(line_token->operands[0]);
    instr->instr.sdt->L = 1;

    if (line_token->operands[1][0] == '='){
        if(line_token->operands[1]<=0xFF){
            strcpy(line_token->str.opcode, "mov");
            assembleMov(line_token, instr);
        }
        else{
            instr->instr.sdt->OFFSET=calculate(line_token,1);
            instr->instr.sdt->P=1;
        }
    }
    else{
        EXP_IN_RECT *exp_in_rect = parseExpressioninrect(line_token);
        if(exp_in_rect->exp_not_in_rect_int==0 && exp_in_rect->exp_in_rect_int==1){
            instr->instr.sdt->REGN=parseRegister(line_token->operands[1]);
            instr->instr.sdt->OFFSET=0;
            instr->instr.sdt->P=1;
        }
        else if(exp_in_rect->exp_not_in_rect_int==0 && exp_in_rect->exp_in_rect_int==2){
            instr->instr.sdt->REGN=parseRegister(line_token->operands[1]);
            instr->instr.sdt->OFFSET = calculate(line_token->operands[2], 2);
            instr->instr.sdt->P=1;
        }
        else if(exp_in_rect->exp_not_in_rect_int==1 && exp_in_rect->exp_in_rect_int==1){
            instr->instr.sdt->REGN=parseRegister(line_token->operands[1]);
            instr->instr.sdt->OFFSET = calculate(line_token->operands[2], 2);
            instr->instr.sdt->P=0;
        }
    }
}

//finish the parts which is not optional
void assemble_Str(LINE_TOKEN* line_token, INSTRUCTION* instr){


    //set opcode, destination register and also L flag
    strcpy(instr->instr.sdt->OPCODE,"str");
    instr->instr.sdt->REGD = parseRegister(line_token->operands[0]);
    instr->instr.sdt->L=0;

    EXP_IN_RECT *exp_in_rect = parseExpressioninrect(line_token);
    if(exp_in_rect->exp_not_in_rect_int==0 && exp_in_rect->exp_in_rect_int==1){
        instr->instr.sdt->REGN=parseRegister(line_token->operands[1]);
        instr->instr.sdt->OFFSET=0;
        instr->instr.sdt->P=1;
    }
    else if(exp_in_rect->exp_not_in_rect_int==0 && exp_in_rect->exp_in_rect_int==2){
        instr->instr.sdt->REGN=parseRegister(line_token->operands[1]);
        instr->instr.sdt->OFFSET=calculate(line_token->operands[2], 2);
        instr->instr.sdt->P=1;
    }
    else if(exp_in_rect->exp_not_in_rect_int==1 && exp_in_rect->exp_in_rect_int==1){
        instr->instr.sdt->REGN=parseRegister(line_token->operands[1]);
        instr->instr.sdt->OFFSET=calculate(line_token->operands[2], 2);
        instr->instr.sdt->P=0;
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