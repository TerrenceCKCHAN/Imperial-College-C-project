#include "assemble.h"
#include "../emulator/instruction.h"

//Return a 32bit instruction after getting the instruction structure pointer
u32 assembleInstructions(INSTRUCTION* instr) {
    u32 instruction = 0;
    if(strcmp(instr->type, "dataprocessing") == 0) {
        instruction += instr->instr.dp->OPERAND2;
        instruction += instr->instr.dp->DEST << 12;
        instruction += instr->instr.dp->SRC << 16;
        instruction += instr->instr.dp->S << 20;
        instruction += instr->instr.dp->OPCODEBIN << 21;
//        instruction = lookUpValue(table, instr->instr.dp->OPCODE) << 20;
        instruction += instr->instr.dp->I << 25;
        instruction += instr->instr.dp->COND << 28;
    } else if(strcmp(instr->type, "multiply") == 0) {
        instruction += instr->instr.mp->REGM;
        instruction += 9 << 4;
        instruction += instr->instr.mp->REGS << 8;
        instruction += instr->instr.mp->ACC << 12;
        instruction += instr->instr.mp->DEST << 16;
        instruction += instr->instr.mp->S << 20;
        instruction += instr->instr.mp->A << 21;
        instruction += instr->instr.mp->COND << 28;
    } else if(strcmp(instr->type, "singledatatransfer") == 0) {
        instruction += instr->instr.sdt->OFFSET;
        instruction += instr->instr.sdt->REGD << 11;
        instruction += instr->instr.sdt->REGN << 15;
        instruction += instr->instr.sdt->L << 19;
        instruction += instr->instr.sdt->U << 22;
        instruction += instr->instr.sdt->P << 23;
        instruction += instr->instr.sdt->I << 24;
        instruction += 1 << 25;
        instruction += instr->instr.sdt->COND << 27;
    } else if(strcmp(instr->type, "branch") == 0) {
        instruction += instr->instr.br->OFFSET;
        instruction += 10 << 23;
        instruction += instr->instr.br->COND << 27;
    } else if(strcmp(instr->type, "halt") == 0) {
        instruction = 0;
    }
    return instruction;
}