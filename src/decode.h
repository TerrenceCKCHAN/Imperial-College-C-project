#ifndef ARM11_06_DECODE_H
#define ARM11_06_DECODE_H

#include "emulate.h"
void DecodeDataProcessing(DATAPROCESSING_INSTR*, u32);
void DecodeMultiply(MULTIPLY_INSTR*, u32);
void DecodeSingleDataTransfer(SIN_DATA_TRAN_INSTR*, u32);
void DecodeBranch(BRANCH_INSTR*, u32);
void printDataProcessing(DATAPROCESSING_INSTR*);
void printMultiply(MULTIPLY_INSTR*);
void printSDT(SIN_DATA_TRAN_INSTR*);
void printBranch(BRANCH_INSTR*);


#endif //ARM11_06_DECODE_H
