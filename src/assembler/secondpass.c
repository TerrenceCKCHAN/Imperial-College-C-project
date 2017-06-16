/////////////////////////////////////////////////////////////////////////////////////////
//C Group Project - First Year (2016-2017)
//File: secondpass.c
//Group: 6
//Member: Cheung, Ka (klc116), Mang, Hao (hxm16), Cheuk, Ki (kfc216), Chan, Chun (ckc116)
/////////////////////////////////////////////////////////////////////////////////////////
#include "assemble.h"

/////////////////////////////////////////////////////////////////////////////////////////
// Carry out the second pass and assemble each instruction with the symbol table provided
// PRE: Tokens from the line,  the instructions, the symbol table, number of lines and the number of instructions
// that are not labels
// POST: The assembled instruction in type usigned integer
/////////////////////////////////////////////////////////////////////////////////////////
u32 secondpass(LINE_TOKEN *line_tokens[], u32 *instructions, struct Linkedlist **symbolTable, int numOfLines,
                u32 numOfInstructions) {
    u32 memoryIndex = 0;
    for(int pos = 0; pos < numOfLines; pos++) {
        INSTRUCTION* instr = malloc(sizeof(INSTRUCTION));
        if(line_tokens[pos]->type == operands) {
            if(line_tokens[pos]->str.opcode[0] == 'b') {
                //assembling branch instructions using the function table
                void (*assembleBr)(LINE_TOKEN*, INSTRUCTION*, struct Linkedlist*, u32);
                assembleBr = lookUpBranch(line_tokens[pos]->str.opcode);
                assembleBr(line_tokens[pos], instr, *symbolTable, memoryIndex * 4);
            } else if(strcmp(line_tokens[pos]->str.opcode,"str") == 0 || strcmp(line_tokens[pos]->str.opcode,"ldr") == 0){
                //assembling single data transfer instructions using the function table
                void (*assembleSdt)(LINE_TOKEN*, INSTRUCTION*, u32, u32);
                assembleSdt = lookUpSdt(line_tokens[pos]->str.opcode);
                assembleSdt(line_tokens[pos], instr, memoryIndex * 4, numOfInstructions);
            } else{
                //assembling data processing and multiply instructions using the function table
                void (*assemble)(LINE_TOKEN*, INSTRUCTION*);
                assemble = lookUpfunction(line_tokens[pos]->str.opcode);
                assemble(line_tokens[pos], instr);
            }
            instructions[memoryIndex] = assembleInstructions(instr);
            memoryIndex++;
        }
    }
    return memoryIndex;
}