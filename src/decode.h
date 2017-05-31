#ifndef ARM11_06_DECODE_H
#define ARM11_06_DECODE_H

#include "emulate.h"
void DecodeDataProcessing(DATAPROCESSING*, u32);
void DecodeMultiply(MULTIPLY*, u32);
void DecodeSingleDataTransfer(SIN_DATA_TRAN*, u32);
void DecodeBranch(BRANCH*, u32);
void printDataProcessing(DATAPROCESSING*);
void printMultiply(MULTIPLY*);
void printSDT(SIN_DATA_TRAN*);
void printBranch(BRANCH*);

#endif //ARM11_06_DECODE_H
