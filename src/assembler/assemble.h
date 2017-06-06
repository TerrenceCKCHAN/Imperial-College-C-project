#ifndef ARM11_06_ASSEMBLE_H
#define ARM11_06_ASSEMBLE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <string.h>

typedef uint32_t u32;



struct Linkedlist{
    struct Linkedlist *next;
    void* value;
    char *key;
};


typedef struct dp{
    u32 INSTRUCTION;
    char OPCODE[4];
    u32 COND: 4;
    u32 S:1;
    u32 I:1;
    u32 DEST;
    u32 SRC;
    u32 OPERAND2;
}DATAPROCESSING_INSTR;

typedef struct mp{
    u32 INSTRUCTION;
    char OPCODE[4];
    u32 COND: 4;
    u32 S:1;
    u32 A:1;
    u32 DEST;
    u32 REGM;
    u32 REGS;
    u32 ACC;
}MULTIPLY_INSTR;

typedef struct sdt{
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

typedef struct br{
    u32 INSTRUCTION;
    char OPCODE[4];
    u32 COND: 4;
    u32 OFFSET;
}BRANCH_INSTR;

typedef struct {
    char type[20];
    union {
        DATAPROCESSING_INSTR* dp;
        MULTIPLY_INSTR* mp;
        SIN_DATA_TRAN_INSTR* sdt;
        BRANCH_INSTR* br;
    }instr;
}INSTRUCTION;

struct Linkedlist* getNewlist(void);
struct Linkedlist* insertElementInNode(struct Linkedlist* list,char *key, void* value);
void* lookUpValue(struct Linkedlist *list, char *key);
char* lookUpkey(struct Linkedlist *list, void* value);

#endif //ARM11_06_ASSEMBLE_H
