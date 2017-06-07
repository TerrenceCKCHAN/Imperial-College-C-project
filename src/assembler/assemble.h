#ifndef ARM11_06_ASSEMBLE_H
#define ARM11_06_ASSEMBLE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <string.h>
#include "tokenizer.h"
#include "../emulator/instruction.h"

typedef uint32_t u32;



struct Linkedlist{
    struct Linkedlist *next;
    void* value;
    char *key;
}*head;

typedef struct table{
    char* opcode;
    void (*func)(LINE_TOKEN*, INSTRUCTION*);
};

typedef struct branchelem{
    char* opcode;
    void (*br)(LINE_TOKEN*, INSTRUCTION*, struct Linkedlist*, u32 currAddress);
};



void assembleAdd(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleSub(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleRsb(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleAnd(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleEor(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleOrr(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleMov(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleTst(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleTeq(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleCmp(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleMul(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleMla(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleLdr(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleStr(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleBeq(LINE_TOKEN* line_token, INSTRUCTION* instr, struct Linkedlist *symboltable, u32 currAddress);
void assembleBne(LINE_TOKEN* line_token, INSTRUCTION* instr, struct Linkedlist *symboltable, u32 currAddress);
void assembleBge(LINE_TOKEN* line_token, INSTRUCTION* instr, struct Linkedlist *symboltable, u32 currAddress);
void assembleBlt(LINE_TOKEN* line_token, INSTRUCTION* instr, struct Linkedlist *symboltable, u32 currAddress);
void assembleBgt(LINE_TOKEN* line_token, INSTRUCTION* instr, struct Linkedlist *symboltable, u32 currAddress);
void assembleBle(LINE_TOKEN* line_token, INSTRUCTION* instr, struct Linkedlist *symboltable, u32 currAddress);
void assembleB(LINE_TOKEN* line_token, INSTRUCTION* instr, struct Linkedlist *symboltable, u32 currAddress);
void assembleLsl(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleAndeq(LINE_TOKEN* line_token, INSTRUCTION* instr);


struct Linkedlist* getNewlist(void);
void* lookUpValue(struct Linkedlist *list, char *key);
char* lookUpkey(struct Linkedlist *list, void* value);
void printLinkedList(struct Linkedlist* linkedlist);
void insertElement(struct Linkedlist** list, char *key, void* value);
typedef void(*assemblefunction)(LINE_TOKEN*, INSTRUCTION*);
typedef void(*assembleBranch)(LINE_TOKEN*, INSTRUCTION*, struct Linkedlist* symbolTable, u32 currentAddress);
assemblefunction lookUpfunction(char* instr);
assembleBranch lookUpBranch(char* instr);
u32 assembleInstructions(INSTRUCTION* instr);
void printBit1(uint32_t x);
u32 secondpass(LINE_TOKEN* line_tokens[], u32* Memory,struct Linkedlist **symbolTable, int numOfLines);


typedef struct{
    int expinrect;
    int expnotinrect;
    char *expinrect[2];
    char *expnotinrect[1];
}EXP_IN_RECT;

#endif //ARM11_06_ASSEMBLE_H
