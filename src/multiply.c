#include "decode.h"
#include "emulate.h"

void multiply(MACHINE* ARM,MULTIPLY_INSTR* multiInstr) {
    if(satisfyCondition(ARM, multiInstr->INSTRUCTION)) {
        // Get the index of the registers for ease of manipulation
        u32 rd = multiInstr->DEST;
        u32 rm = multiInstr->REGM;
        u32 rs = multiInstr->REGS;
        u32 rn = multiInstr->ACC;
        u32 res;
        // If the accumulate flag is set carry ouy multiply and accumulate. Otherwise just multiply.
        if(rn != NOT_EXIST) {
            res = ARM->REGISTER[rm] * ARM->REGISTER[rs] + ARM->REGISTER[rn];
        } else {
            res = ARM->REGISTER[rm] * ARM->REGISTER[rs];
        }
        ARM->REGISTER[rd] = res;
        // Check if S bit is set and modify the CPSR register
        if(multiInstr->S) {
            u32 n = GETBITS(res, 31, 31);
            // Setting bit 31 of the CPSR register to the N bit
            if(n) {
                ARM->REGISTER[16] = SETBIT(ARM->REGISTER[16], 31);
            } else {
                ARM->REGISTER[16] = CLEARBIT(ARM->REGISTER[16], 31);
            }
            // Setting the zero flag if the result is zero
            if(res == 0) {
                ARM->REGISTER[16] = SETBIT(ARM->REGISTER[16], 30);
            }
        }
    }
}