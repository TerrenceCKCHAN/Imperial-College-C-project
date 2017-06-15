#include "assemble.h"

/////////////////////////////////////////////////////////////////////////////////////////
// Take in a register string (e.g."r12") and return the register number
/////////////////////////////////////////////////////////////////////////////////////////
u32 parseRegister(char* operand) {
    u32 val;
    val = (u32) strtol(operand + 1, NULL, 10);
    return val;
}

/////////////////////////////////////////////////////////////////////////////////////////
// Take in an expression string (e.g."#12") and return the number based on the base (hexadecimal or decimal)
/////////////////////////////////////////////////////////////////////////////////////////
u32 parseExpression(char* operand) {
    u32 val;
    if(operand[2] == 'x') {
        val = (u32) strtol(operand + 1, NULL, 16);
    } else {
        val = (u32) strtol(operand + 1, NULL, 10);
    }
    return val;
}




