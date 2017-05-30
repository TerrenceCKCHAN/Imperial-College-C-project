#include "decode.h"

/*This is the function to print bit*/
void printBit(uint32_t x){
    int i;
    uint32_t mask = (uint32_t) 1 << 31;
    for(i = 0;i < 32;++i){
        printf("%i", (x & mask) != 0);
        x<<=1;
    }
    printf("\n");
}

void loadBinaryFile(char *address){
    unsigned char *combuffer;
    u32 size;
    FILE *ifp;

    ifp = fopen(address, "rb");

    fseek(ifp, 0, SEEK_END);
    size = (u32) ftell(ifp);
    fseek(ifp, 0, SEEK_SET);
    combuffer = (unsigned char *) malloc(size);

    if(ifp == NULL){
        fprintf(stderr,"Unable to read file!");
        exit(EXIT_FAILURE);
    }

    fread(combuffer, 1,size,ifp);

    for(int i = 0; i < size; i++) {
        printf("%x ",combuffer[i]);
        printBit(combuffer[i]);
        printf("\n");
    }

    fclose(ifp);
    free(combuffer);
}

u32 generateDataFromHex(char hex[]){
    int length = strlen(hex);
    u32 data = 0;
    u32 shift = (length - 1) * 4;
    for(int pos = 0; pos < length; pos++) {
        u32 hexValue;
        if(hex[pos] >= '0' && hex[pos] <= '9') {
            hexValue = (hex[pos] - '0');
        } else if(hex[pos] >= 'a' && hex[pos] <= 'f') {
            hexValue = hex[pos] - 'a' + 10;
        }
        data += hexValue << shift;
        shift -= 4;
    }
    return data;
}

void DATAPROCESSING_INSTR(DATAPROCESSING *datapt){
    if((datapt->S)!=0){
        //TODO: change CPSR FLAG
    }
    //The CPSR register is unaffected

}


u32 generateMask(u32 start, u32 end){
    return (u32) ((1 << (end + 1)) - 1) - ((1 << start)-1);
}

void printRegisters() {
    for(int index = 1; index <= 12; index++) {
        printf("$%d\t:% 11d (0x%08x)\n", index, MACHINE.REGISTER[index], MACHINE.REGISTER[index]);
    }
    printf("$%d\t:% 11d (0x%08x)\n", index, MACHINE.PCREG, MACHINE.PCREG);
    printf("$%d\t:% 11d (0x%08x)\n", index, MACHINE.CPSRREG, MACHINE.CPSRREG);
}

void printMemory() {
    for(int index = 0; index < 65536; index++) {
        printf("0x%08x: 0x%08x\n", index * 4, MACHINE.MEMORY[index]);
    }
}

int main(int argc,  char **argv) {

/*    char hex[16];
    DATAPROCESSING dpstruct;
    printBit(0xFu<<11);
    scanf("%s", hex);
    printf("%x\n", generateDataFromHex(hex));
    u32 instruction = generateDataFromHex(hex);
    printBit(instruction);
    printDataProcessing(DecodeDataProcessing(instruction));


    printBit(GENERATEMASK(2,2));
    printBit(GETBIT(0xe3a01001,21,24));*/


    return EXIT_SUCCESS;
}


