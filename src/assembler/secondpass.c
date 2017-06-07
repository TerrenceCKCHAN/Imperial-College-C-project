//
// Created by klc116 on 6/7/17.
//

#include "assemble.h"
#include "tokenizer.h"

void secondpass(LINE_TOKEN* line_tokens[], u32* Memory,struct Linkedlist symbolTable, int numOfLines) {
    u32 memoryIndex = 0;
    for(int pos = 0; pos < numOfLines; pos++) {
        INSTRUCTION* instr = malloc(sizeof(INSTRUCTION));
        if(line_tokens[pos]->type == operands) {
            void (*assemble)(LINE_TOKEN*, INSTRUCTION*);
            assemble = lookUpfunction(line_tokens[pos]->str.opcode);
            assemble(line_tokens, instr);
            memoryIndex += 4;
        }
    }
}