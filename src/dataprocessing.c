#include "emulate.h"
#include "decode.h"


void dataprocessing(MACHINE* ARM, u32 instruction){
    DATAPROCESSING* dataproInstr = DecodeDataProcessing(instruction);
    if(satisfyCondition(ARM,instruction)){

        u32 I = dataproInstr->I;
        u32 OpCode = dataproInstr->OPCODE;
        u32 S   = dataproInstr->S;
        u32 Rn = dataproInstr->REGN;
        u32 Rd = dataproInstr->REGD;
        u32 Oprand2 = dataproInstr->OPRAND2;

        if(dataproInstr->S){
            //TODO: CPSR REG
        }
        if(dataproInstr->I){
            //If operand2 is a immediate value
            u32 rotate = GETBITS(dataproInstr->OPRAND2, 8, 11);
            u32 Imm = GETBITS(dataproInstr->OPRAND2,0,7);
            SETBITS(RotateR(GETBITS(dataproInstr->OPRAND2,0,7),rotate*2),dataproInstr->OPRAND2,0,8);
        }else{
            //If operand2 is a register
            u32 shiftType = GETBITS(dataproInstr->OPRAND2,5,6);
            if(GETBITS(dataproInstr->OPRAND2,4,4)){
                //shift specified by register
            } else{
                //shift by constant
                switch (shiftType){
                    case lsl:
                        break;
                    case lsr:
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

u32 OpcodeOperation(DATAPROCESSING* datapro){
    u32 Opcode = (datapro->OPCODE);
    u32 result=0;
    switch (Opcode){
        case and:
            result = (datapro->REGN & datapro->OPRAND2);
            break;
        case eor:
            result =(datapro->REGN ^ datapro->OPRAND2);
            break;
        case sub:
            result = (datapro->REGN - datapro->OPRAND2);
            break;
        case rsb:
            result = (datapro->OPRAND2 - datapro->REGN);
            break;
        case add:
            result = (datapro->REGN + datapro->OPRAND2);
            break;
        case tst:
            result = (datapro->REGN & datapro->OPRAND2);
            break;
        case teq:
            result = (datapro->REGN ^ datapro->OPRAND2);
            break;
        case cmp:
            result = (datapro->REGN - datapro->OPRAND2);
            break;
        case orr:
            result = (datapro->REGN | datapro->OPRAND2);
            break;
        case mov:
            result = (datapro->OPRAND2);
            break;
    }
    if(Opcode != tst | Opcode != teq | Opcode != cmp){
        datapro->REGD = result;
    }
    return result;
}

