//
// Created by Timothy Cheuk on 06/06/2017.
//
#include "assemble.h"
#include "../emulator/instruction.h"

u32 transformnum(int num){
    u32 val = 0;
    u32 MASK = 1 << 25 - 1;
    if (num > 0){
        val = (u32) (num >> 2);
    } else if(num < 0) {
        val = (u32) 1 << 24 + (~(num >> 2) & MASK);
    }
    return val;
}

//as by the time i finish this part we still not able to get current address, create this helper so we can amend easier
void generalbr(LINE_TOKEN* line_token, INSTRUCTION* instr,struct Linkedlist *symboltable,u32 curA){
    int i = (int) lookUpValue(symboltable, line_token->operands[0]);
    i -= curA + 8;
    printf("OFFSET = %d\n", i);
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
    instr->instr.br->COND = 0xA;
    generalbr(line_token, instr,symboltable,curA);
}
void assembleBlt(LINE_TOKEN* line_token, INSTRUCTION* instr,struct Linkedlist *symboltable,u32 curA){
    instr->instr.br = malloc(sizeof(BRANCH_INSTR));
    strcpy(instr->instr.br->OPCODE,"blt");
    instr->instr.br->COND = 0xB;
    generalbr(line_token, instr,symboltable,curA);
}
void assembleBgt(LINE_TOKEN* line_token, INSTRUCTION* instr,struct Linkedlist *symboltable,u32 curA){
    instr->instr.br = malloc(sizeof(BRANCH_INSTR));
    strcpy(instr->instr.br->OPCODE,"bgt");
    instr->instr.br->COND = 0xC;
    generalbr(line_token, instr,symboltable,curA);
}
void assembleBle(LINE_TOKEN* line_token, INSTRUCTION* instr,struct Linkedlist *symboltable,u32 curA){
    instr->instr.br = malloc(sizeof(BRANCH_INSTR));
    strcpy(instr->instr.br->OPCODE,"ble");
    instr->instr.br->COND = 0xD;
    generalbr(line_token, instr,symboltable,curA);
}

void assembleB(LINE_TOKEN* line_token, INSTRUCTION* instr,struct Linkedlist *symboltable,u32 curA){
    instr->instr.br = malloc(sizeof(BRANCH_INSTR));
    strcpy(instr->instr.br->OPCODE,"b");
    instr->instr.br->COND = 0xE;
    generalbr(line_token, instr,symboltable,curA);
}



/*typedef struct br{
u32 INSTRUCTION;
char OPCODE[4];
u32 COND: 4;
u32 OFFSET;
}BRANCH_INSTR;


 typedef struct{
    enum TOKEN_TYPE type;
    char label[512];
    char opcode[4];
    char *operands[10];
    int numOfOperands;
}LINE_TOKEN;

 */
