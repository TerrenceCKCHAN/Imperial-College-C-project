/////////////////////////////////////////////////////////////////////////////////////////
//C Group Project - First Year (2016-2017)
//File: table.c
//Group: 6
//Member: Cheung, Ka (klc116), Mang, Hao (hxm16), Cheuk, Ki (kfc216), Chan, Chun (ckc116)
/////////////////////////////////////////////////////////////////////////////////////////
#include "assemble.h"

/////////////////////////////////////////////////////////////////////////////////////////
// table matching string opcodes to function for assembling dataprocessing and multiply
// instructions
/////////////////////////////////////////////////////////////////////////////////////////
struct table instrarray[] = {
        {"add", &assembleAdd},
        {"sub", &assembleSub},
        {"rsb", &assembleRsb},
        {"and", &assembleAnd},
        {"eor", &assembleEor},
        {"orr", &assembleOrr},
        {"mov", &assembleMov},
        {"tst", &assembleTst},
        {"teq", &assembleTeq},
        {"cmp", &assembleCmp},
        {"mul", &assembleMul},
        {"mla", &assembleMla},
        {"andeq", &assembleAndeq}
};

/////////////////////////////////////////////////////////////////////////////////////////
// table matching string opcodes to function for assembling branch instructions
/////////////////////////////////////////////////////////////////////////////////////////
struct branchelem brinstrarray[]={
        {"beq", &assembleBeq},
        {"bne", &assembleBne},
        {"bge", &assembleBge},
        {"blt", &assembleBlt},
        {"bgt", &assembleBgt},
        {"ble", &assembleBle},
        {"bal", &assembleB},
        {"b", &assembleB}
};

/////////////////////////////////////////////////////////////////////////////////////////
// table matching string opcodes to function for assembling single data transfer instructions
/////////////////////////////////////////////////////////////////////////////////////////
struct sdtelem sdtarray[]={
        {"ldr", &assembleLdr},
        {"str", &assembleStr}
};

/////////////////////////////////////////////////////////////////////////////////////////
// takes in a string opcode and return the function pointer to the function to assemble
// dataprocessing and multiply instructions
/////////////////////////////////////////////////////////////////////////////////////////
assemblefunction lookUpfunction(char* instr) {
    u32 index = 0;
    while(strcmp(instrarray[index].opcode, instr) != 0 && index < 12){
        index++;
    }
    return instrarray[index].func;
}

/////////////////////////////////////////////////////////////////////////////////////////
// takes in a string opcode and return the function pointer to the function to assemble
// branch instructions
/////////////////////////////////////////////////////////////////////////////////////////
assembleBranch lookUpBranch(char* instr) {
    u32 index = 0;
    while(strcmp(brinstrarray[index].opcode, instr) != 0 && index < 7){
        index++;
    }
    return brinstrarray[index].br;
}

/////////////////////////////////////////////////////////////////////////////////////////
// takes in a string opcode and return the function pointer to the function to assemble
// single data transfer instructions
/////////////////////////////////////////////////////////////////////////////////////////
assembleSdt lookUpSdt(char* instr) {
    u32 index = 0;
    while(strcmp(sdtarray[index].opcode, instr) != 0 && index < 2){
        index++;
    }
    return sdtarray[index].sdt;
}


