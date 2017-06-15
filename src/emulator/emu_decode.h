/////////////////////////////////////////////////////////////////////////////////////////
//C Group Project - First Year (2016-2017)
//File.decode.h
//Group: 6
//Member: Cheung, Ka (klc116), Mang, Hao (hxm16), Cheuk, Ki (kfc216), Chan, Chun (ckc116)
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef ARM11_06_DECODE_H
#define ARM11_06_DECODE_H

#include "instruction.h"
void DecodeDataProcessing(DATAPROCESSING_INSTR*, u32);
void DecodeMultiply(MULTIPLY_INSTR*, u32);
void DecodeSingleDataTransfer(SIN_DATA_TRAN_INSTR*, u32);
void DecodeBranch(BRANCH_INSTR*, u32);
void printDataProcessing(DATAPROCESSING_INSTR*);
void printMultiply(MULTIPLY_INSTR*);
void printSDT(SIN_DATA_TRAN_INSTR*);
void printBranch(BRANCH_INSTR*);
void printDecodedInstruction(INSTRUCTION* instr);

#endif //ARM11_06_DECODE_H
