//
// Created by klc116 on 6/7/17.
//

#include "assemble.h"
#include "tokenizer.h"
#include "../emulator/decode.h"

u32 secondpass(LINE_TOKEN* line_tokens[], u32* instructions,struct Linkedlist **symbolTable, int numOfLines) {
    u32 memoryIndex = 0;
    for(int pos = 0; pos < numOfLines; pos++) {
        INSTRUCTION* instr = malloc(sizeof(INSTRUCTION));
        if(line_tokens[pos]->type == operands) {
            if(line_tokens[pos]->str.opcode[0] == 'b') {
                void (*assembleBr)(LINE_TOKEN*, INSTRUCTION*, struct Linkedlist*, u32);
                assembleBr = lookUpBranch(line_tokens[pos]->str.opcode);
                assembleBr(line_tokens[pos], instr, *symbolTable, memoryIndex * 4);
            } else if(strcmp(line_tokens[pos]->str.opcode,"str") == 0 || strcmp(line_tokens[pos]->str.opcode,"ldr") == 0){
                void (*assembleSdt)(LINE_TOKEN*, INSTRUCTION*, u32);
                assembleSdt = lookUpSdt(line_tokens[pos]->str.opcode);
                assembleSdt(line_tokens[pos], instr, memoryIndex * 4);
            } else{
                void (*assemble)(LINE_TOKEN*, INSTRUCTION*);
                assemble = lookUpfunction(line_tokens[pos]->str.opcode);
                assemble(line_tokens[pos], instr);
            }
//            printf("Type = %s\n", instr->type);
//            printDecodedInstruction(instr);
//            printf("hi4\n");
            instructions[memoryIndex] = assembleInstructions(instr);
//            printf("%x\n", assembleInstructions(instr));
            memoryIndex++;
        }
    }
    return memoryIndex;
}