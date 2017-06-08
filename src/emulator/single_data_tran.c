#include "emulate.h";
#include "decode.h"

void singleDataTran(MACHINE* ARM, SIN_DATA_TRAN_INSTR* sin_I){
    if(satisfyCondition(ARM,sin_I->COND)){

        u32 offset = sin_I->OFFSET;
        u32 carry  = 0;
        u32 result;
        u32 valueofRm = NULL;
        u32 Rn = sin_I->REGN;
        u32 address;
        u32 Rd = sin_I->REGD;

        if (sin_I->I) { //if I flag = 1 opposite to Data Processing
            //offset is a shift reg
            u32 shiftType = GETBITS(sin_I->INSTRUCTION, 5, 6);
            u32 Rm = GETBITS(sin_I->INSTRUCTION, 0, 3);
            u32 valueInRm = ARM->REGISTER[Rm];
            if (GETBITS(sin_I->INSTRUCTION, 4, 4)) {
                //shift specified by register
                u32 Rs = GETBITS(sin_I->INSTRUCTION, 8, 11);
                u32 shiftvalue = GETBITS(ARM->REGISTER[Rs], 0, 7); //get the bottom byte of Rs
                result = shifingOperation(shiftType, valueInRm, shiftvalue);
            } else {
                //shift by constant
                u32 shiftvalue = GETBITS(sin_I->INSTRUCTION, 7, 11);
                result = shifingOperation(shiftType, valueInRm, shiftvalue);
            }
        } else { //if I flag =0
            //If offset is a immediate value
            u32 rotateValue = 2*GETBITS(sin_I->INSTRUCTION, 8, 11);
            u32 Imm = GETBITS(sin_I->INSTRUCTION, 0, 7);
            u32 ImmAfterRotate = RotateR(Imm, rotateValue);
            carry = GETBITS(ImmAfterRotate,rotateValue-1,rotateValue-1);
            result =  ImmAfterRotate;
        }


        if (sin_I->P) {  //P flag
            //pre indexing
            if (sin_I->U) { //U flag
                address = ARM->REGISTER[Rn] + result;
            } else {
                address = ARM->REGISTER[Rn] - result;
            }
            if (sin_I->L) { //L flag
                u32 content;
                content = readMemory(ARM, address);
                if (content != 0) {
                    ARM->REGISTER[Rd] = content;
                }
            } else {
                writeMemory(ARM, address, ARM->REGISTER[Rd]);
            }
        } else {
            if (sin_I->L){ //L flag
                u32 content;
                content = readMemory(ARM, ARM->REGISTER[Rn]);
                if (content != 0) {
                    ARM->REGISTER[Rd] = content;
                }
            } else {
                writeMemory(ARM, ARM->REGISTER[Rn], ARM->REGISTER[Rd]);
            }
            if (sin_I->U) {    //U flag
                ARM->REGISTER[Rn] = ARM->REGISTER[Rn] + result;
            } else {
                ARM->REGISTER[Rn] = ARM->REGISTER[Rn] - result;
            }
        }
    }
}
