#ifndef ARM11_06_PARSER_H
#define ARM11_06_PARSER_H

#include "assemble.h"

u32 parseRegister(char* operand);
u32 parseExpression(char* operand);

typedef struct{
    char *expinrect[2];
    char *expnotinrect[1];
}EXP_IN_RECT;

#endif //ARM11_06_PARSER_H
