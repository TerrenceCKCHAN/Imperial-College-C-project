#include "decode.h"
#include "emulate.h"

//Execution of the branch instruction
//PRE: Pointer to the machine and the structure of the branch instruction
//POST: Modified the contents of the machine through the pointer
void branch(MACHINE* ARM, BRANCH_INSTR* br) {
    if(satisfyCondition(ARM, br->COND)) {
        u32 offset  = br->OFFSET;
        //Left shifting the offset by two bits
        offset = LShiftL(offset,2);
        if(offset & ( 1 << 23 )){
            //offset is negative
            //changing the two's complement integer to an unisgned integer
            offset = (~offset)+1;
            ARM->REGISTER[15] -= GETBITS(offset, 0, 23);
        }else{
            //offset is positive
            ARM->REGISTER[15] += GETBITS(offset, 0, 23);
        }

    }
}