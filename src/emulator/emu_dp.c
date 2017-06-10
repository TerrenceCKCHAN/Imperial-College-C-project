/////////////////////////////////////////////////////////////////////////////////////////
//C Group Project - First Year (2016-2017)
//File:emu_dp.c
//Group: 6
//Member: Cheung, Ka (klc116), Mang, Hao (hxm16), Cheuk, Ki (kfc216), Chan, Chun (ckc116)
/////////////////////////////////////////////////////////////////////////////////////////
#include "emulate.h"
#include "emu_decode.h"
/////////////////////////////////////////////////////////////////////////////////////////
// Helper function for shifting numbers
// Pre: the times to be shift, shift type and value to be shift
// Post: return a unsigned 32 bit interger which is shifted
/////////////////////////////////////////////////////////////////////////////////////////
u32 shifingOperation(u32 shiftType, u32 valueofRm, u32 value){
    u32 result = 0;
    switch (shiftType){
        case 0x0: //lsl
            result = LShiftL(valueofRm,value);
            break;
        case 0x1: //lst
            result = LShiftR(valueofRm,value);
            break;
        case 0x2: //asr
            result = AShiftR(valueofRm,value);
            break;
        case 0x3: //ror
            result = RotateR(valueofRm,value);
            break;
        default:
            printf("Shift type not support");
            break;
    }
    return result;
}

void dataprocessing(MACHINE* ARM, DATAPROCESSING_INSTR* datapro_I){
    if(satisfyCondition(ARM,datapro_I->COND)){

        char* opcode = datapro_I->OPCODE;
        u32 Rd = datapro_I->DEST;
        u32 carry  = 0;
        u32 updatedoprand2;
        u32 valueofRm ;

        if (datapro_I->I) { //if I flag = 1
            //If operand2 is a immediate value
            u32 rotateValue = 2*GETBITS(datapro_I->INSTRUCTION, 8, 11);
            u32 Imm = GETBITS(datapro_I->INSTRUCTION, 0, 7);
            u32 ImmAfterRotate = RotateR(Imm, rotateValue);
            carry = GETBITS(ImmAfterRotate,rotateValue-1,rotateValue-1);
            updatedoprand2 =  ImmAfterRotate;
        } else { //if I flag =0
            //If operand2 is a register
            u32 shiftType = GETBITS(datapro_I->INSTRUCTION, 5, 6);
            u32 Rm = GETBITS(datapro_I->INSTRUCTION, 0, 3);
            u32 valueInRm = ARM->REGISTER[Rm];
            if (GETBITS(datapro_I->INSTRUCTION, 4, 4)) {
                //shift specified by register
                u32 Rs = GETBITS(datapro_I->INSTRUCTION, 8, 11);
                u32 shiftvalue = GETBITS(ARM->REGISTER[Rs], 0, 7); //get the bottom byte of Rs
                if(shiftType == 0){
                    carry =  GETBITS(shiftvalue,32-shiftvalue+1,32-shiftvalue+1);
                }else{
                    carry = GETBITS(shiftvalue,shiftvalue-1,shiftvalue-1);
                }
                updatedoprand2 = shifingOperation(shiftType, valueInRm, shiftvalue);
            } else {
                //shift by constant
                u32 shiftvalue = GETBITS(datapro_I->OPERAND2, 7, 11);
                updatedoprand2 = shifingOperation(shiftType, valueInRm, shiftvalue);
                if(shiftType == 0){
                    carry =  GETBITS(shiftvalue,32-shiftvalue-1,32-shiftvalue-1);
                }else{
                    carry = GETBITS(shiftvalue,shiftvalue-1,shiftvalue-1);
                }
            }

        }

        if(datapro_I->SRC != NOT_EXIST) {
            valueofRm = ARM->REGISTER[datapro_I->SRC];
        }

        u32 result = 0;

        //OpCode operations
        switch (GETBITS(datapro_I->INSTRUCTION,21,24)){
            case and:
                result = (valueofRm & updatedoprand2);
                break;
            case eor:
                result = (valueofRm ^ updatedoprand2);
                break;
            case sub:
                result = (valueofRm - updatedoprand2);
                carry = result > valueofRm ? 0 :1 ;
                break;
            case rsb:
                result = (updatedoprand2 - valueofRm);
                carry = result > updatedoprand2 ? 1 :0;
                break;
            case add:
                result = (valueofRm + updatedoprand2);
                carry = result < valueofRm ? 1 :0;
                break;
            case tst:
                result = (valueofRm & updatedoprand2);
                break;
            case teq:
                result = (valueofRm ^ updatedoprand2);
                break;
            case cmp:
                result = (valueofRm - updatedoprand2);
                carry =  result > valueofRm ? 0 :1 ;
                break;
            case orr:
                result = (valueofRm | updatedoprand2);
                break;
            case mov:
                result = updatedoprand2;
                break;
            default:
                exit(EXIT_FAILURE);
        }

        if(datapro_I->S){
            int Nflag =GETBITS(result,31,31);
            //seting CPSR flag
            if(result==0){
                //set Z flag
                ARM->REGISTER[16] = SETBIT(ARM->REGISTER[16],30);
            }else{
                ARM->REGISTER[16] = CLEARBIT(ARM->REGISTER[16],30);
            }
            if(carry){
                //set C flag
                ARM->REGISTER[16] = SETBIT(ARM->REGISTER[16],29);
            }
            if(Nflag){
                //set N flag
                ARM->REGISTER[16] = SETBIT(ARM->REGISTER[16],31);
            }
        }

        if(strcmp(opcode,"tst")!=0 | strcmp(opcode,"teq")!=0 | strcmp(opcode,"cmp")!=0){
            if(Rd != NOT_EXIST) {
                ARM->REGISTER[Rd] = result;
            }
        }
    }
}





