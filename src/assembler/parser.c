#include "assemble.h"

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
