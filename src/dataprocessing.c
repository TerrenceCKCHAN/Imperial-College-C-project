#include "emulate.h"
#include "decode.h"




u32 shifingOperation(DATAPROCESSING_INSTR *datapro_I, u32 shiftType, u32 valueofRm, u32 value, u32 oprand2){
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
    }
    return result;
}





void dataprocessing(MACHINE* ARM, DATAPROCESSING_INSTR* datapro_I){
//    printf("%x\n", datapro_I->INSTRUCTION);
//    printf("\n");
//    printf("%x\n", satisfyCondition(ARM,datapro_I->INSTRUCTION));
//    parseDataprocessing(datapro_I);
    if(satisfyCondition(ARM,datapro_I->INSTRUCTION)){

        char* opcode = datapro_I->OPCODE;
        u32 COND = datapro_I->COND;
        u32 S = datapro_I->S;
        u32 Rd = datapro_I->DEST;
        u32 Rn = datapro_I->SRC;
        u32 oprand2 = datapro_I->OPERAND2;
        u32 ARM_Rn;
        u32 I = GETBITS(datapro_I->INSTRUCTION,25,25);

        if(Rn != NOT_EXIST) {
            ARM_Rn = ARM->REGISTER[Rn];
        }
        u32 result=0;
        u32 carry =0;
        //OpCode operations
        switch (GETBITS(datapro_I->INSTRUCTION,21,24)){
            case and:
                result = (ARM_Rn & oprand2);
                break;
            case eor:
                result = (ARM_Rn ^ oprand2);
                break;
            case sub:
                result = (ARM_Rn - oprand2);
                break;
            case rsb:
                result = (oprand2 - ARM_Rn);
                break;
            case add:
                result = (ARM_Rn + oprand2);
                break;
            case tst:
                result = (ARM_Rn & oprand2);
                break;
            case teq:
                result = (ARM_Rn ^ oprand2);
                break;
            case cmp:
                result = (ARM_Rn - oprand2);
                break;
            case orr:
                result = (ARM_Rn | oprand2);
                break;
            case mov:
                result = oprand2;
                break;
            default:
                exit(EXIT_FAILURE);
        }

        if(strcmp(opcode,"tst")!=0 | strcmp(opcode,"teq")!=0 | strcmp(opcode,"cmp")!=0){
            ARM->REGISTER[Rd] = result;
        }



        if(I){
            //If operand2 is a immediate value
            u32 rotatevalue = GETBITS(oprand2, 8, 11);
            u32 Imm = GETBITS(oprand2,0,7);
            u32 ImmAfterRotate = RotateRH(Imm,rotatevalue*2,8);
            datapro_I->OPERAND2 = SETBITS(ImmAfterRotate,oprand2,0,8);

        }else{
            //If operand2 is a register
            u32 shiftType = GETBITS(oprand2,5,6);
            u32 Rm = GETBITS(oprand2,0,3);
            u32 valueofRm = ARM->REGISTER[Rm];
            u32 RmAfterRotate;
            if(GETBITS(datapro_I->INSTRUCTION,4,4)){
                //shift specified by register
                u32 Rs = GETBITS(datapro_I->INSTRUCTION,8,11);
                u32 shiftvalue = GETBITS(ARM->REGISTER[Rs],0,7); //get the bottom byte of Rs
                if(shiftType == 0x0){
                    carry = GETBITS(shiftvalue,32-shiftvalue-1,32-shiftvalue-1);
                }else{
                    carry = GETBITS(shiftvalue,shiftvalue-1,shiftvalue-1);
                }
                result = shifingOperation(datapro_I, shiftType, valueofRm, shiftvalue, oprand2);

            } else{
                //shift by constant
                u32 shiftvalue = GETBITS(oprand2,7,11);
                if(shiftType == 0x0){
                    carry = GETBITS(shiftvalue,32-shiftvalue-1,32-shiftvalue-1);
                }else{
                    carry = GETBITS(shiftvalue,shiftvalue-1,shiftvalue-1);
                }
                result = shifingOperation(datapro_I, shiftType, valueofRm, shiftvalue, oprand2);
            }

        }
//        printf("Hi\n");

        if(S){
            //seting CPSR flag
            if(result==0){
                //set zero flag
                ARM->CPSRREG = SETBIT(ARM->CPSRREG,30);
            }
            if(carry==1){
                ARM->CPSRREG = SETBIT(ARM->CPSRREG,29);
            }
            if(GETBITS(result,31,31)){
                ARM->CPSRREG = SETBIT(ARM->CPSRREG,31);
            }


        }
//        printMachineState(ARM);
    }
}





