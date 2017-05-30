#include "decode.h"
#include "emulate.h"

void multiply(MACHINE* ARM,u32 instruction) {
    MULTIPLY* multiInstr = DecodeMultiply(instruction);
    if(satisfyCondition(ARM, instruction)) {
        u32 rd = multiInstr->REGD;
        u32 rm = multiInstr->REGM;
        u32 rs = multiInstr->REGS;
        u32 rn = multiInstr->REGN;
        u32 res;
        if(multiInstr->A) {
            res = ARM->REGISTER[rm] * ARM->REGISTER[rs] + ARM->REGISTER[rn];
        } else {
            res = ARM->REGISTER[rm] * ARM->REGISTER[rs];
        }
        ARM->REGISTER[rd] = res;
        if(multiInstr->S) {
            u32 n = GETBIT(res, 31, 31);
            if(n) {
                ARM->CPSRREG = SETBIT(ARM->CPSRREG, 31);
            } else {
                ARM->CPSRREG = CLEARBIT(ARM->CPSRREG, 31);
            }
            if(res == 0) {
                ARM->CPSRREG = SETBIT(ARM->CPSRREG, 30);
            }
        }
    }
}