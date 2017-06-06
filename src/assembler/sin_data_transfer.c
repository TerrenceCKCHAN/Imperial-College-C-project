//
// Created by Timothy Cheuk on 06/06/2017.
//
#include "assemble.h"

u32 sin_data_transfer(LINE_TOKEN* token ){
    u32 temp;
    u32 cond;
    u32 i;
    u32 P;
    u32 U;
    u32 L;
    u32 Rn;
    u32 Rd;
    u32 Offset;
    if( token->opcode == ){
        L = 1;
        if (token->operands[1]<= 0xff){
            printf("shdnt end up here in sdt, shd go to mov instead");
        }
        else{
            Rd = loouptabler(token->operands[0]);
            i = 1;
            p = 1;
            U = 1;
            Rn = 0xf;
            Rd = 0;
            Offset =
        }
    }
    else{
        L = 0;
    }












    temp = cond<<27 + 1<<25 + I << 24 + P << 23 + U << 22 + Rn << 15 + Rd << 11 + Offset;
    return u32;

}
