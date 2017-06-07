#ifndef ARM11_06_EMULATE_H
#define ARM11_06_EMULATE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <string.h>
#include "instruction.h"

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

#define NUM_OF_GENERAL_REGISTER 17
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

/*This is use to extract bit 26 and 27 in the instruction set*/
#define BIT2627_MASK             (u32)   0x3u << 26
#define FIND_BIT2627(x)          (u32)   (BIT2627_MASK & x) >> 26
#define FIND_BIT25(x)            (u32)   (0x1u<<25 & x)>>25

/*To determine which state the instruction set are*/
#define IS_MULTI(x)              (u32)   (~FIND_BIT25(x)&((0x90u & x) == 0x90) & (FIND_BIT2627(x) == 0))
#define IS_DATAPROCESS(x)        (u32)   (FIND_BIT2627(x) == 0) & ~(IS_MULTI(x))
#define IS_SINDATATRAN(x)        (u32)   FIND_BIT2627(x) == 0x1u
#define IS_BRANCH(x)             (u32)   FIND_BIT2627(x) == 0x2u

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

typedef struct{
    u32 REGISTER[NUM_OF_GENERAL_REGISTER];
    u32 MEMORY[MAX_MEMORY];
}MACHINE;

int satisfyCondition(MACHINE* ARM, u32 condition);
void dataprocessing(MACHINE* ARM, DATAPROCESSING_INSTR* instruction);
void printBit(uint32_t x);
u32 generateDataFromHex(char hex[]);
void printRegisters(MACHINE* ARM);
MACHINE* createMachine();
void printMemory(MACHINE* ARM);
void printMachineState(MACHINE* ARM);
void loadBinaryFile(MACHINE* ARM, char *address);
u32 updatedOprand2(MACHINE *ARM, DATAPROCESSING_INSTR *data);
void branch(MACHINE* ARM, BRANCH_INSTR* br);
void singleDataTran(MACHINE* ARM, SIN_DATA_TRAN_INSTR* sin_I);
u32 shifingOperation(u32 shiftType, u32 valueofRm, u32 value);
void multiply(MACHINE* ARM,MULTIPLY_INSTR* multiInstr);
void singleDataTran(MACHINE* ARM, SIN_DATA_TRAN_INSTR* sin_I);


#endif //ARM11_06_EMULATE_H
