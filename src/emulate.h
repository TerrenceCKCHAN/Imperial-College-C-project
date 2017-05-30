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

#define NUM_OF_GENERAL_REGISTER 12
#define MAX_MEMORY  65536

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

/*To determine which state the instruction set are*/
#define IS_MULTI(x)              (u32)   ((0x90u & x) == 0x90) & (FIND_BIT2627(x) == 0)
#define IS_DATAPROCESS(x)        (u32)   ((FIND_BIT2627(x) == 0) & !IS_MULTI(x)
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
#define MSBH(x)          (MSB(x)<<v )-1<<(32-v)
#define LShiftL(x,n)     x << n
#define LShiftR(x,n)     x >> n
#define AShiftR(x,n)     LShiftR(x, n)|(x & MSB)
#define RotateR(x,n)     (x>>n)|LShiftL(x, 32-n)

#define GENERATEMASK(start,end) (u32) ((1<<(end+1)) -1) - ((1<<start)-1)
#define GETBIT(x, start, end)   (u32) (GENERATEMASK(start, end) & x)>>start

typedef struct a{
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

typedef struct{
    u32 CPSRREG;
    u32 PCREG;
    u32 REGISTER[NUM_OF_GENERAL_REGISTER];
    u32 MEMORY[MAX_MEMORY];
}MACHINE;

#endif //ARM11_06_EMULATE_H
