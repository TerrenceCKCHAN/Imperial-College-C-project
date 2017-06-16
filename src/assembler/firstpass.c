/////////////////////////////////////////////////////////////////////////////////////////
//C Group Project - First Year (2016-2017)
//File: firstpass.c
//Group: 6
//Member: Cheung, Ka (klc116), Mang, Hao (hxm16), Cheuk, Ki (kfc216), Chan, Chun (ckc116)
/////////////////////////////////////////////////////////////////////////////////////////
#include "assemble.h"

/////////////////////////////////////////////////////////////////////////////////////////
// Carry out the first pass for the assembler: go through the lines and add the label-address
// pair to the symbolTable
// PRE: Tokens from the line,  the symbol table (empty at start) and the number of lines to be assembled
// POST: A complete list of pairs {label, address} in the symbol table. The number of instructions that
// are not labels is returned
/////////////////////////////////////////////////////////////////////////////////////////
u32 firstpass(LINE_TOKEN **line_tokens, struct Linkedlist **symbolTable, int numOfLines) {
    u32 index = 0;
    for(int pos = 0; pos < numOfLines; pos++) {
        if(line_tokens[pos]->type == label) {
            u32 address = index * 4;
            insertElement(symbolTable, line_tokens[pos]->str.label, address);
        } else {
            index++;
        }
    }
    return index;
}
