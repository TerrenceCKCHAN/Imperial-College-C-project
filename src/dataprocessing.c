#include "emulate.h"
#include "decode.h"




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
    if(satisfyCondition(ARM,datapro_I->INSTRUCTION)){

        char* opcode = datapro_I->OPCODE;
        u32 Rd = datapro_I->DEST;
        u32 updatedoprand2 = updatedOprand2(ARM, datapro_I);
        u32 valueofRm = NULL;

        if(datapro_I->SRC != NOT_EXIST) {
            valueofRm = ARM->REGISTER[datapro_I->SRC];
        }

        u32 result = 0;
        u32 carry = 0;
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
                break;
            case rsb:
                result = (updatedoprand2 - valueofRm);
                break;
            case add:
                result = (valueofRm + updatedoprand2);
                break;
            case tst:
                result = (valueofRm & updatedoprand2);
                break;
            case teq:
                result = (valueofRm ^ updatedoprand2);
                break;
            case cmp:
                result = (valueofRm - updatedoprand2);
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
            //seting CPSR flag
            if(result==0){
                //set zero flag
                ARM->CPSRREG = SETBIT(ARM->CPSRREG,30);
            }
            if(carry){
                ARM->CPSRREG = SETBIT(ARM->CPSRREG,29);
            }
            if(GETBITS(result,31,31)){
                ARM->CPSRREG = SETBIT(ARM->CPSRREG,31);
            }
        }

        if(strcmp(opcode,"tst")!=0 | strcmp(opcode,"teq")!=0 | strcmp(opcode,"cmp")!=0){
            if(Rd != NOT_EXIST) {
                ARM->REGISTER[Rd] = result;
            }
        }
    }
}

u32 updatedOprand2(MACHINE *ARM, DATAPROCESSING_INSTR *data) {
    if (GETBITS(data->INSTRUCTION, 25, 25)) { //if I flag = 1
        //If operand2 is a immediate value
        u32 rotatevalue = GETBITS(data->INSTRUCTION, 8, 11);
        u32 Imm = GETBITS(data->INSTRUCTION, 0, 7);
        u32 ImmAfterRotate = RotateRH(Imm, rotatevalue * 2, 8);
        return SETBITS(ImmAfterRotate, data->OPERAND2, 0, 8);

    } else { //if I flag =0

        //If operand2 is a register
        u32 shiftType = GETBITS(data->INSTRUCTION, 5, 6);
        u32 Rm = GETBITS(data->INSTRUCTION, 0, 3);
        u32 valueofRm = ARM->REGISTER[Rm];
        if (GETBITS(data->INSTRUCTION, 4, 4)) {
            //shift specified by register
            u32 Rs = GETBITS(data->INSTRUCTION, 8, 11);
            u32 shiftvalue = GETBITS(ARM->REGISTER[Rs], 0, 7); //get the bottom byte of Rs
            return shifingOperation(shiftType, valueofRm, shiftvalue);

        } else {
            //shift by constant
            u32 shiftvalue = GETBITS(data->OPERAND2, 7, 11);
            return shifingOperation(shiftType, valueofRm, shiftvalue);
        }

    }
}

u32 getcarry(u32 shifttype, u32 shiftvalue){
    if(shifttype == 0){
        return GETBITS(shiftvalue,32-shiftvalue-1,32-shiftvalue-1);
    }else{
        return GETBITS(shiftvalue,shiftvalue-1,shiftvalue-1);
    }
}





