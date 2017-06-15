#include "assemble.h"


struct table instrarray[] = {
        {"add",&assembleAdd},
        {"sub",&assembleSub},
        {"rsb",&assembleRsb},
        {"and",&assembleAnd},
        {"eor",&assembleEor},
        {"orr",&assembleOrr},
        {"mov",&assembleMov},
        {"tst",&assembleTst},
        {"teq",&assembleTeq},
        {"cmp",&assembleCmp},
        {"mul",&assembleMul},
        {"mla",&assembleMla},
        {"andeq", &assembleAndeq}
};


struct branchelem brinstrarray[]={
        {"beq",&assembleBeq},
        {"bne",&assembleBne},
        {"bge",&assembleBge},
        {"blt",&assembleBlt},
        {"bgt",&assembleBgt},
        {"ble",&assembleBle},
        {"bal",&assembleB},
        {"b",&assembleB}
};

struct sdtelem sdtarray[]={
        {"ldr", &assembleLdr},
        {"str", &assembleStr}
};

assemblefunction lookUpfunction(char* instr) {
    u32 index = 0;
    while(strcmp(instrarray[index].opcode, instr) != 0 && index < 12){
        index++;
    }
    return instrarray[index].func;
}

assembleBranch lookUpBranch(char* instr) {
    u32 index = 0;
    while(strcmp(brinstrarray[index].opcode, instr) != 0 && index < 7){
        index++;
    }
    return brinstrarray[index].br;
}

assembleSdt lookUpSdt(char* instr) {
    u32 index = 0;
    while(strcmp(sdtarray[index].opcode, instr) != 0 && index < 2){
        index++;
    }
    return sdtarray[index].sdt;
}


