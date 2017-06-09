/////////////////////////////////////////////////////////////////////////////////////////
//C Group Project - First Year (2016-2017)
//File:instruction.h
//Group: 6
//Member: Cheung, Ka (klc116), Mang, Hao (hxm16), Cheuk, Ki (kfc216), Chan, Chun (ckc116)
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef ARM11_06_INSTRUCION_H
#define ARM11_06_INSTRUCION_H
#include <stdint.h>
typedef uint32_t u32;

typedef struct dp{
    u32 INSTRUCTION;
    char OPCODE[4];
    u32 COND: 4;
    u32 OPCODEBIN: 4;
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

#endif //ARM11_06_INSTRUCION_H
