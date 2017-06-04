#include "decode.h"
#include "emulate.h"

void branch(MACHINE* ARM, BRANCH_INSTR* br) {
    if(satisfyCondition(ARM, br->INSTRUCTION)) {
        u32 offset  = br->OFFSET;
        offset = LShiftL(offset,2);
        if(offset & ( 1 << 23 )){
            //offset is negative
            offset = (~offset)+1;
            ARM->REGISTER[15] -= GETBITS(offset, 0, 23);
        }else{
            ARM->REGISTER[15] += GETBITS(offset, 0, 23);
        }

    }
}