#ifndef ARM11_06_DECODE_H
#define ARM11_06_DECODE_H

#include "emulate.h"
DATAPROCESSING* DecodeDataProcessing(u32 instructions);
MULTIPLY* DecodeMultiply(u32);
SIN_DATA_TRAN* DecodeSingleDataTransfer(u32);
BRANCH* DecodeBranch(u32);
void printDataProcessing(DATAPROCESSING*);
void printMultiply(MULTIPLY*);
void printSDT(SIN_DATA_TRAN*);
void printBranch(BRANCH*);


#endif //ARM11_06_DECODE_H
