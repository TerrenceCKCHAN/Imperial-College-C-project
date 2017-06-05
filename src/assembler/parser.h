#ifndef ARM11_06_PARSER_H
#define ARM11_06_PARSER_H

#include "assemble.h"

u32 parseRegister(char* operand);
u32 parseExpression(char* operand);

#endif //ARM11_06_PARSER_H
