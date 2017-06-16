/////////////////////////////////////////////////////////////////////////////////////////
//C Group Project - First Year (2016-2017)
//File:emulate.h
//Group: 6
//Member: Cheung, Ka (klc116), Mang, Hao (hxm16), Cheuk, Ki (kfc216), Chan, Chun (ckc116)
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef ARM11_06_EMULATE_H
#define ARM11_06_EMULATE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <string.h>
#include "instruction.h"

#define NUM_OF_GENERAL_REGISTER 17
#define MAX_MEMORY  65536
/////////////////////////////////////////////////////////////////////////////////////////
// Macro definition that help to extract and set bits in u32 binary code
/////////////////////////////////////////////////////////////////////////////////////////
#define SETBIT(input, pos)          (u32) (input | 1 << pos)
//Change bit at position pos to 0
#define CLEARBIT(input, pos)        (u32) (input & (~(1 << pos)))

/////////////////////////////////////////////////////////////////////////////////////////
// Macro definition that help to determine the ARM instruction set from its binary code
/////////////////////////////////////////////////////////////////////////////////////////
//This is use to extract bit 26 and 27 in the instruction set
#define BIT2627_MASK             (u32)   (0x3u << 26)
#define FIND_BIT2627(x)          (u32)   ((BIT2627_MASK & x) >> 26)
#define FIND_BIT25(x)            (u32)   ((0x1u<<25 & x) >> 25)

//To determine which state the instruction set are
#define IS_MULTI(x)              (u32)   (~FIND_BIT25(x) & ((0x90u & x) == 0x90) & (FIND_BIT2627(x) == 0))
#define IS_DATAPROCESS(x)        (u32)   ((FIND_BIT2627(x) == 0) & ~(IS_MULTI(x)))
#define IS_SINDATATRAN(x)        (u32)   (FIND_BIT2627(x) == 0x1u)
#define IS_BRANCH(x)             (u32)   (FIND_BIT2627(x) == 0x2u)

/////////////////////////////////////////////////////////////////////////////////////////
// Macro definition that doing shift operation
/////////////////////////////////////////////////////////////////////////////////////////
/*define shifting operations*/
#define MSB(x)           ((1 << 31 & x) >> 31)
#define MSBH(x,v)        ((MSB(x) ? (MSB(x) << v) - (1 << (32 - v)) : 0))
#define LShiftL(x,n)     ((x) << (n))
#define LShiftR(x,n)     ((x) >> (n))
#define AShiftR(x,n)     (MSBH(x,n) | LShiftR(x, n))
#define RotateR(x,n)     (((x) >> (n)) | LShiftL(x, 32 - n))


/////////////////////////////////////////////////////////////////////////////////////////
// Macro definition that help to identify the code and suffix
/////////////////////////////////////////////////////////////////////////////////////////
#define NOT_EXIST 0xffffffffu

#define and 0x0
#define eor 0x1
#define sub 0x2
#define rsb 0x3
#define add 0x4
#define tst 0x8
#define teq 0x9
#define cmp 0xa
#define orr 0xc
#define mov 0xd

#define eq 0x0
#define ne 0x1
#define ge 0xa
#define lt 0xb
#define gt 0xc
#define le 0xd
#define al 0xe

/////////////////////////////////////////////////////////////////////////////////////////
// Structure of a ARM machine with register and memory
/////////////////////////////////////////////////////////////////////////////////////////
typedef struct{
    u32 REGISTER[NUM_OF_GENERAL_REGISTER];
    u32 MEMORY[MAX_MEMORY];
}MACHINE;


/////////////////////////////////////////////////////////////////////////////////////////
// Function declaration (Utility functions in emu_util.c)
/////////////////////////////////////////////////////////////////////////////////////////
u32 GENERATEMASKHELPER(int pos);
u32 GENERATEMASK(int start, int end);
u32 GETBITS(u32 input, int start, int end);
int satisfyCondition(MACHINE* ARM, u32 condition);
void printBit(uint32_t x);
void printRegisters(MACHINE* ARM);
MACHINE* createMachine();
void printMemory(MACHINE* ARM);
void printMachineState(MACHINE* ARM);
u32 readMemory(MACHINE* ARM, u32 address);
void writeMemory(MACHINE* ARM, u32 address, u32 content);

/////////////////////////////////////////////////////////////////////////////////////////
// Function declaration (Input/Output functions in emu_io.c)
/////////////////////////////////////////////////////////////////////////////////////////
void loadBinaryFile(MACHINE* ARM, char *address);

/////////////////////////////////////////////////////////////////////////////////////////
// Function declaration (emulating instructions in emu_branch.c, emu_dp.c, emu_multiply.c, emu_sdt.c)
/////////////////////////////////////////////////////////////////////////////////////////
void dataprocessing(MACHINE* ARM, DATAPROCESSING_INSTR* instruction);
u32 shifingOperation(u32 shiftType, u32 valueofRm, u32 value);
void branch(MACHINE* ARM, BRANCH_INSTR* br);
void singleDataTran(MACHINE* ARM, SIN_DATA_TRAN_INSTR* sin_I);
void multiply(MACHINE* ARM,MULTIPLY_INSTR* multiInstr);
void Indexing(MACHINE *ARM, const SIN_DATA_TRAN_INSTR *sin_I, u32 result, u32 Rn, u32 address, u32 Rd);

#endif //ARM11_06_EMULATE_H
