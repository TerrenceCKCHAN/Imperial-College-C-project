#include "assemble.h"
#include "parser.h"

u32 parseRegister(char* operand) {
    u32 val;
    val = (u32) strtol(operand + 1, NULL, 10);
    return val;
}

u32 parseExpression(char* operand) {
    u32 val;
    if(operand[2] == 'x') {
        val = (u32) strtol(operand + 1, NULL, 16);
    } else {
        val = (u32) strtol(operand + 1, NULL, 10);
    }
    return val;
}

EXP_IN_RECT* parseExpressioninrect(char* operand[]){
    EXP_IN_RECT* expinrect = malloc(sizeof(EXP_IN_RECT));
    int i = 0;
    int j = 0;
    int k = 0;
    while(operand[i] != null){
        if (*(operand+i)[0]=='[' | *(operand+i)[*(operand+i).length-1]==']'){
            expinrect->expinrect[j] = operand[i];
            j++;
        }
        else{
            expinrect->expinrect[k] = operand[k];
            k++;
        }
    }


    return expinrect;
}


