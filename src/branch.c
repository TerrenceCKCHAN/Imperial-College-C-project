//
// Created by admin on 30/5/2017.
//


#include "decode.h"
#include "emulate.h"

void branch(MACHINE* ARM, u32 instruction) {
    BRANCH* branchInstr = DecodeBranch(instruction);
    if(satisfyCondition(ARM, instruction)) {
        u32 offset  = GETBITS(instruction, 23, 0);
        u32 shifted = LShiftL(offset, 2);
        ARM->PCREG += shifted;
    }
}