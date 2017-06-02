#ifndef ARM11_06_EMULATE_H
#define ARM11_06_EMULATE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <string.h>

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

#define NUM_OF_GENERAL_REGISTER 13
#define MAX_MEMORY  65536

//Generate a mask to extract the bits of position start to position end
#define GENERATEMASK(start,end) (u32) ((1 << (end+1)) -1) - ((1<<start)-1)
//Change the bits from position start to position end
#define GETBITS(input, start, end)   (u32) (GENERATEMASK(start, end) & input)>>start
//Change bit at position pos to 1
#define SETBIT(input, pos)          (u32) (input | 1 << pos)
//Change bit at position pos to 0
#define CLEARBIT(input, pos)        (u32) (input & (~(1 << pos)))
//Change bits in target from position start to position end to input
#define SETBITS(input, target, start, length)  (u32) (GENERATEMASK(start, start + length - 1) | target) & (((GENERATEMASK(length, 31) | input) << start) | GENERATEMASK(0, start - 1))

/*This is use to set and get the flag of the CPSR register*/
#define NFLAG_MASK (u32) 1 << 31
#define ZFLAG_MASK (u32) 1 << 30
#define CFLAG_MASK (u32) 1 << 29
#define VFLAG_MASK (u32) 1 << 28

#define SET_NFLAG(x) (u32) (x  & NFLAG_MASK)
#define SET_ZFLAG(x) (u32) (x  & ZFLAG_MASK)
#define SET_CFLAG(x) (u32) (x  & CFLAG_MASK)
#define SET_VFLAG(x) (u32) (x  & VFLAG_MASK)

#define GET_NFLAG(x) (u32) (SET_NFLAG(x)>>31)
#define GET_ZFLAG(x) (u32) (SET_ZFLAG(x)>>30)
#define GET_CFLAG(x) (u32) (SET_CFLAG(X)>>29)
#define GET_VFLAG(x) (u32) (SET_VFLAG(x)>>28)

/*This is use to extract bit 26 and 27 in the instruction set*/
#define BIT2627_MASK             (u32)   0x3u << 26
#define FIND_BIT2627(x)          (u32)   (BIT2627_MASK & x) >> 26
#define FIND_BIT25(x)            (u32)   (0x1u<<25 & x)>>25

/*To determine which state the instruction set are*/
#define IS_MULTI(x)              (u32)   (~FIND_BIT25(x)&((0x90u & x) == 0x90) & (FIND_BIT2627(x) == 0))
#define IS_DATAPROCESS(x)        (u32)   (FIND_BIT2627(x) == 0) & ~(IS_MULTI(x))
#define IS_SINDATATRAN(x)        (u32)   FIND_BIT2627(x) == 0x1u
#define IS_BRANCH(x)             (u32)   FIND_BIT2627(x) == 0x2u

/*This is the masks, setter and getter for data processing instruction (for testing purpose) */

#define COND_MASK            (u32)         0xFu << 28
#define IMMED_OP_MASK        (u32)         0x1u << 25
#define OP_CODE_MASK         (u32)         0xFu << 21
#define S_MASK               (u32)         0x1u << 20
#define FIRST_OP_REG_MASK    (u32)         0xFu << 16
#define DIS_REG_MASK         (u32)         0xFu << 12

#define SET_COND(x)              (u32)          (x & COND_MASK)
#define SET_IMMED_OP(x)          (u32)          (x & IMMED_OP_MASK)
#define SET_OP_CODE(x)           (u32)          (x & OP_CODE_MASK)
#define SET_S(x)                 (u32)          (x & S_MASK)
#define SET_FIRST_OP_REG(x)      (u32)          (x & FIRST_OP_REG_MASK)
#define SET_DIS_REG(x)           (u32)          (x & DIS_REG_MASK)
#define SET_OPRAND2(x)           (u32)          (x)

#define GET_COND(x)              (u32)          SET_COND(x) >> 28
#define GET_IMMED_OP(x)          (u32)          SET_IMMED_OP(x) >> 25
#define GET_OP_CODE(x)           (u32)          SET_OP_CODE(x) >> 21
#define GET_S(x)                 (u32)          SET_S(x) >> 20
#define GET_FIRST_OP_REG(x)      (u32)          SET_FIRST_OP_REG(x) >> 16
#define GET_DIS_REG(x)           (u32)          SET_DIS_REG(x) >> 12
#define GET_OPRAND2(x)           (u32)          SET_OPRAND2(x)

/*define shifting operations*/
#define MSB(x)           (1 << 31 & x) >> 31
#define MSBH(x,v)        (MSB(x) ? (MSB(x)<<v )-1<<(32-v) : 0)
#define LShiftL(x,n)     x << n
#define LShiftR(x,n)     x >> n
#define AShiftR(x,n)     (MSBH(x,n) | LShiftR(x, n))
#define RotateR(x,n)     (x>>n)|LShiftL(x, 32-n)
#define RotateRH(x,n,length)    (RotateR(x,n) | (RotateR(x,n)>>(32-length))) & GENERATEMASK(0,length-1)

#define NOT_EXIST 0xffffffffu

#define and 0x00
#define eor 0x01
#define sub 0x02
#define rsb 0x03
#define add 0x04
#define tst 0x08
#define teq 0x09
#define cmp 0x0a
#define orr 0x0c
#define mov 0x0d



#define eq 0x0
#define ne 0x1
#define ge 0xa
#define lt 0xb
#define gt 0xc
#define le 0xd
#define al 0xe

/*
typedef struct{
    u32 COND:4;
    u32 I:1;
    u32 OPCODE:4;
    u32 S:1;
    u32 REGN:4;
    u32 REGD:4;
    u32 OPRAND2:12;
}DATAPROCESSING;

typedef struct{
    u32 COND:4;
    u32 A:1;
    u32 S:4;
    u32 REGD:4;
    u32 REGN:4;
    u32 REGS:4;
    u32 REGM:4;
}MULTIPLY;

typedef struct{
    u32 COND:4;
    u32 I:1;
    u32 P:1;
    u32 U:1;
    u32 L:1;
    u32 REGN:4;
    u32 REGD:4;
    u32 OFFSET:1;
}SIN_DATA_TRAN;

typedef struct{
    u32 COND:4;
    u32 OFFSET:24;
}BRANCH;
*/
typedef struct dp{
    u32 INSTRUCTION;
    u32 COND: 4;
    u32 S:1;
    char OPCODE[4];
    u32 DEST;
    u32 SRC;
    u32 OPERAND2;
}DATAPROCESSING_INSTR;

typedef struct mp{
    u32 INSTRUCTION;
    u32 COND: 4;
    u32 S:1;
    char OPCODE[4];
    u32 DEST;
    u32 REGM;
    u32 REGS;
    u32 ACC;
}MULTIPLY_INSTR;

typedef struct sdt{
    u32 INSTRUCTION;
    u32 COND: 4;
    char OPCODE[4];
    u32 REG;
    u32 ADDRESS;
}SIN_DATA_TRAN_INSTR;

typedef struct br{
    u32 INSTRUCTION;
    u32 COND: 4;
    char OPCODE[4];
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

typedef struct{
    u32 CPSRREG;
    u32 PCREG;
    u32 REGISTER[NUM_OF_GENERAL_REGISTER];
    u32 MEMORY[MAX_MEMORY];
}MACHINE;

int satisfyCondition(MACHINE* ARM, u32 instruction);
void dataprocessing(MACHINE* ARM, DATAPROCESSING_INSTR* instruction);
void printBit(uint32_t x);
u32 generateDataFromHex(char hex[]);
void printRegisters(MACHINE* ARM);
MACHINE* createMachine();
void printMemory(MACHINE* ARM);
void printMachineState(MACHINE* ARM);
void loadBinaryFile(MACHINE* ARM, char *address);
u32 updatedOprand2(MACHINE *ARM, DATAPROCESSING_INSTR *data);

#endif //ARM11_06_EMULATE_H
