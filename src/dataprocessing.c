#include "emulate.h"
#include "decode.h"


void dataprocessing(MACHINE* ARM, u32 instruction){
    DATAPROCESSING* datapro = DecodeDataProcessing(instruction);
    if(satisfyCondition(ARM,instruction)){

        u32 I = datapro->I;
        u32 OpCode = datapro->OPCODE;
        u32 S   = datapro->S;
        u32 Rn = datapro->REGN;
        u32 Rd = datapro->REGD;
        u32 Oprand2 = datapro->OPRAND2;
        u32 ARM_Rn = ARM->REGISTER[Rn];
        u32 result=0;

        //OpCode operations
        switch (OpCode){
            case and:
                result = (ARM_Rn & Oprand2);
                break;
            case eor:
                result = (ARM_Rn ^ Oprand2);
                break;
            case sub:
                result = (ARM_Rn - Oprand2);
                break;
            case rsb:
                result = (Oprand2 - ARM_Rn);
                break;
            case add:
                result = (ARM_Rn + Oprand2);
                break;
            case tst:
                result = (ARM_Rn & Oprand2);
                break;
            case teq:
                result = (ARM_Rn ^ Oprand2);
                break;
            case cmp:
                result = (ARM_Rn - Oprand2);
                break;
            case orr:
                result = (ARM_Rn | Oprand2);
                break;
            case mov:
                result = Oprand2;
                break;
            default:
                exit(EXIT_FAILURE);
        }

        if(OpCode != tst | OpCode != teq | OpCode != cmp){
            ARM->REGISTER[Rd] = result;
        }


        if(datapro->S){
            //TODO: CPSR REG
        }

        if(I){
            //If operand2 is a immediate value
            u32 rotate = GETBITS(Oprand2, 8, 11);
            u32 Imm = GETBITS(Oprand2,0,7);
            u32 ImmAfterRotate = RotateRH(Imm,rotate*2,8);
            datapro->OPRAND2 = SETBITS(ImmAfterRotate,Oprand2,0,8);

        }else{
            //If operand2 is a register
            u32 shiftType = GETBITS(Oprand2,5,6);
            u32 Rm = GETBITS(Oprand2,0,3);
            u32 value = GETBITS(Oprand2,7,11);
            u32 RmAfterRotate;
            if(GETBITS(datapro->OPRAND2,4,4)){
                //shift specified by register


            } else{
                //shift by constant
                switch (shiftType){
                    case lsl:
                        datapro->OPRAND2 = SETBITS(LShiftL(Rm,value),Oprand2,0,4);
                        break;
                    case lsr:
                        datapro->OPRAND2 = SETBITS(LShiftR(Rm,value),Oprand2,0,4);
                        break;
                    case asr:
                        break;
                    case ror:
                        break;
                }
            }

        }
    }
}



