//
// Created by klc116 on 5/29/17.
//
#include "emulate.h"

DATAPROCESSING DecodeDataProcessing(u32 instruction) {
    DATAPROCESSING instr;
    instr.COND     = GET_COND(instruction);
    instr.I        = GET_IMMED_OP(instruction);
    instr.OPCODE   = GET_OP_CODE(instruction);
    instr.S        = GET_S(instruction);
    instr.REGN     = GET_FIRST_OP_REG(instruction);
    instr.REGD     = GET_DIS_REG(instruction);
    instr.OPRAND2  = GET_OPRAND2(instruction);
    return instr;
}

void printStruct(DATAPROCESSING dp) {
    printf("COND %x\n",dp.COND);
    printf("I %x\n",dp.I);
    printf("OPCODE %x\n",dp.OPCODE);
    printf("S %x\n",dp.S);
    printf("REGN %x\n",dp.REGN);
    printf("REGD %x\n",dp.REGD);
    printf("OPRAND2 %x\n",dp.OPRAND2);
}