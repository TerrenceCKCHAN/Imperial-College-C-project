#include "emulate.h";
#include "decode.h"

void singleDataTran(MACHINE* ARM, SIN_DATA_TRAN_INSTR* sin_I){
    if(satisfyCondition(ARM,sin_I->INSTRUCTION)){

        u32 offset = GETBITS(sin_I->INSTRUCTION,0,11);
        u32 carry  =0;
        u32 result;
        u32 valueofRm = NULL;
        u32 Rn = GETBITS(sin_I->INSTRUCTION,16,19);
        u32 address;
        u32 Rd = GETBITS(sin_I->INSTRUCTION,12,15);

        if (GETBITS(sin_I->INSTRUCTION, 25, 25)) { //if I flag = 1 opposite to Data Processing
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


        if (GETBITS(sin_I->INSTRUCTION,24,24)) {  //P flag
            //pre indexing
            if (GETBITS(sin_I->INSTRUCTION,23,23)) { //U flag
                address = ARM->REGISTER[Rn] + result;
            } else {
                address = ARM->REGISTER[Rn] - result;
            }
            if (GETBITS(sin_I->INSTRUCTION,20,20)) { //L flag
                if(address > 0xffff) {
                    printf("Error: Out of bounds memory access at address 0x%08x\n", address);
                } else {
                    u32 memToRegister = 0;
                    for(int byte = 0; byte < 4; byte++) {
                        memToRegister += ARM->MEMORY[address + byte] << (byte * 8);
                    }
                    ARM->REGISTER[Rd] = memToRegister;
                }
            } else {
                u32 start = 0, end = 7;
                for(int byte = 0; byte < 4; byte++) {
                    ARM->MEMORY[address + byte] = GETBITS(ARM->REGISTER[Rd], start ,end);
                    start += 8;
                    end += 8;
                }
            }

        } else {
            if (GETBITS(sin_I->INSTRUCTION,20,20)){ //L flag
                if(ARM->REGISTER[Rd] > 0xffff) {
                    printf("Error: Out of bounds memory access at address 0x%08x\n", ARM->REGISTER[Rd]);
                } else {
                    u32 memToRegister = 0;
                    for (int byte = 0; byte < 4; byte++) {
                        memToRegister += ARM->MEMORY[ARM->REGISTER[Rn] + byte] << (byte * 8);
                    }
                    ARM->REGISTER[Rd] = memToRegister;
                }
            } else {
                u32 start = 0, end = 7;
                for(int byte = 0; byte < 4; byte++) {
                    ARM->MEMORY[ARM->REGISTER[Rn] + byte] = GETBITS(ARM->REGISTER[Rd], start ,end);
                    start += 8;
                    end += 8;
                }
            }
            if (GETBITS(sin_I->INSTRUCTION,23,23)) {    //U flag
                ARM->REGISTER[Rn] = ARM->REGISTER[Rn] + result;
            } else {
                ARM->REGISTER[Rn] = ARM->REGISTER[Rn] - result;
            }
        }
    }
}
