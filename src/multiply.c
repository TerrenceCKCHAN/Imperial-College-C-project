#include "decode.h"
#include "emulate.h"

void multiply(MACHINE* ARM,u32 instruction) {
    // Decode the instruction for the multiply execution
    MULTIPLY* multiInstr = DecodeMultiply(instruction);
    if(satisfyCondition(ARM, instruction)) {
        // Get the index of the registers for ease of manipulation
        u32 rd = multiInstr->REGD;
        u32 rm = multiInstr->REGM;
        u32 rs = multiInstr->REGS;
        u32 rn = multiInstr->REGN;
        u32 res;
        // If the accumulate flag is set carry ouy multiply and accumulate. Otherwise just multiply.
        if(multiInstr->A) {
            res = ARM->REGISTER[rm] * ARM->REGISTER[rs] + ARM->REGISTER[rn];
        } else {
            res = ARM->REGISTER[rm] * ARM->REGISTER[rs];
        }
        ARM->REGISTER[rd] = res;
        // Check if S bit is set and modify the CPSR register
        if(multiInstr->S) {
            u32 n = GETBIT(res, 31, 31);
            // Setting bit 31 of the CPSR register to the N bit
            if(n) {
                ARM->CPSRREG = SETBIT(ARM->CPSRREG, 31);
            } else {
                ARM->CPSRREG = CLEARBIT(ARM->CPSRREG, 31);
            }
            // Setting the zero flag if the result is zero
            if(res == 0) {
                ARM->CPSRREG = SETBIT(ARM->CPSRREG, 30);
            }
        }
    }
}