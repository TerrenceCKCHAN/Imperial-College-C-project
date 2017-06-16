/////////////////////////////////////////////////////////////////////////////////////////
//C Group Project - First Year (2016-2017)
//File: ass_branch.c
//Group: 6
//Member: Cheung, Ka (klc116), Mang, Hao (hxm16), Cheuk, Ki (kfc216), Chan, Chun (ckc116)
/////////////////////////////////////////////////////////////////////////////////////////
#include "assemble.h"

/////////////////////////////////////////////////////////////////////////////////////////
// Helper function to transform an int to a u32 in twos complement
/////////////////////////////////////////////////////////////////////////////////////////
u32 transformnum(int num){
    u32 val;
    u32 valMASK = (1 << 24) - 1;
    if(num<0){
        int tmp = -num;
        val = (u32) ~(tmp-1);
    }else{
        val = (u32) num;
    }
    val >>= 2;
    return val & valMASK;
}
/////////////////////////////////////////////////////////////////////////////////////////
// Helper function to avoid duplication
/////////////////////////////////////////////////////////////////////////////////////////
void generalbr(LINE_TOKEN* line_token, INSTRUCTION* instr,struct Linkedlist *symboltable,u32 curA){
    int i = (int) lookUpValue(symboltable, line_token->operands[0]);
    i -= curA + 8;
    instr->instr.br->OFFSET = transformnum(i);
    strcpy(instr->type, "branch");
}

void assembleBeq(LINE_TOKEN* line_token, INSTRUCTION* instr,struct Linkedlist *symboltable,u32 curA){
    instr->instr.br = malloc(sizeof(BRANCH_INSTR));
    strcpy(instr->instr.br->OPCODE,"beq");
    instr->instr.br->COND = 0x0;
    generalbr(line_token, instr,symboltable,curA);
}
void assembleBne(LINE_TOKEN* line_token, INSTRUCTION* instr,struct Linkedlist *symboltable,u32 curA){
    instr->instr.br = malloc(sizeof(BRANCH_INSTR));
    strcpy(instr->instr.br->OPCODE,"bne");
    instr->instr.br->COND = 0x1;
    generalbr(line_token, instr,symboltable,curA);
}
void assembleBge(LINE_TOKEN* line_token, INSTRUCTION* instr,struct Linkedlist *symboltable,u32 curA) {
    instr->instr.br = malloc(sizeof(BRANCH_INSTR));
    strcpy(instr->instr.br->OPCODE,"bge");
    instr->instr.br->COND = 0xa;
    generalbr(line_token, instr,symboltable,curA);
}
void assembleBlt(LINE_TOKEN* line_token, INSTRUCTION* instr,struct Linkedlist *symboltable,u32 curA){
    instr->instr.br = malloc(sizeof(BRANCH_INSTR));
    strcpy(instr->instr.br->OPCODE,"blt");
    instr->instr.br->COND = 0xb;
    generalbr(line_token, instr,symboltable,curA);
}
void assembleBgt(LINE_TOKEN* line_token, INSTRUCTION* instr,struct Linkedlist *symboltable,u32 curA){
    instr->instr.br = malloc(sizeof(BRANCH_INSTR));
    strcpy(instr->instr.br->OPCODE,"bgt");
    instr->instr.br->COND = 0xc;
    generalbr(line_token, instr,symboltable,curA);
}
void assembleBle(LINE_TOKEN* line_token, INSTRUCTION* instr,struct Linkedlist *symboltable,u32 curA){
    instr->instr.br = malloc(sizeof(BRANCH_INSTR));
    strcpy(instr->instr.br->OPCODE,"ble");
    instr->instr.br->COND = 0xd;
    generalbr(line_token, instr,symboltable,curA);
}

void assembleB(LINE_TOKEN* line_token, INSTRUCTION* instr,struct Linkedlist *symboltable,u32 curA){
    instr->instr.br = malloc(sizeof(BRANCH_INSTR));
    strcpy(instr->instr.br->OPCODE,"b");
    instr->instr.br->COND = 0xe;
    generalbr(line_token, instr,symboltable,curA);
}
