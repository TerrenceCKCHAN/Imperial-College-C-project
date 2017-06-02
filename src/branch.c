//
// Created by admin on 30/5/2017.
//

#include "decode.h"
#include "emulate.h"

void branch(MACHINE* ARM, BRANCH_INSTR* br) {
    if(satisfyCondition(ARM, br->INSTRUCTION)) {
        u32 offset  = GETBITS(br->INSTRUCTION, 23, 0);
        u32 shifted = LShiftL(offset, 2);
        ARM->PCREG += shifted;
    }
}