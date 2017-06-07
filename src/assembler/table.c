#include "assemble.h"
#include "parser.h"
#include "../emulator/emulate.h"
#include "tokenizer.h"

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
        {"mla",&assembleMla}/*,
            {"ldr",&assembleLdr},
            {"str",&assembleStr},
            {"lsl",&assembleLsl},
            {"andeq", &assembleAndeq}*/
};


struct branchelem brinstrarray[]={
        /*{"beq",&assembleBeq},
        {"bne",&assembleBne},
        {"bge",&assembleBge},
        {"blt",&assembleBlt},
        {"bgt",&assembleBgt},
        {"ble",&assembleBle},
        {"b",&assembleB},*/
};

assemblefunction lookUpfunction(char* instr) {
//    printf("Hi\n");
//    printf("Opcode: %s\n", instrarray->opcode);
    u32 index = 0;
    while(strcmp(instrarray[index].opcode, instr) != 0 && index < 12){
//        printf("%s\n", instrarray[index].opcode);
        index++;
    }
    return instrarray[index].func;
}

assembleBranch lookUpBranch(char* instr) {
    u32 index = 0;
    while(strcmp(brinstrarray[index].opcode, instr) != 0 && index < 7){
//        printf("%s\n", instrarray[index].opcode);
        index++;
    }
    return brinstrarray[index].func;
}




