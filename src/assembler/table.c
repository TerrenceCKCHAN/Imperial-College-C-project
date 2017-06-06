#include "assemble.h"
#include "parser.h"
#include "../emulator/emulate.h"
#include "tokenizer.h"

void createTable() {
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
            {"ldr",&assembleLdr},
            {"str",&assembleStr},
            {"beq",&assembleBeq},
            {"bne",&assembleBne},
            {"bge",&assembleBge},
            {"blt",&assembleBlt},
            {"bgt",&assembleBgt},
            {"ble",&assembleBle},
            {"b",&assembleB},
            {"lsl",&assembleLsl},
            {"andeq", &assembleAndeq}
    };

}




