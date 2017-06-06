//
// Created by klc116 on 6/6/17.
//

#include "assemble.h"
#include "tokenizer.h"

void firstpass(LINE_TOKEN* line_tokens[], struct Linkedlist** symbolTable, int numOfLines) {
    u32 index = 0;
    for(int pos = 0; pos < numOfLines; pos++) {
        if(line_tokens[pos]->type == label) {
            u32 address = index * 4;
            //printf("%s %d\n", line_tokens[pos]->str.label, address);
            insertElement(symbolTable, line_tokens[pos]->str.label, address);
        } else {
            index++;
        }
    }
}