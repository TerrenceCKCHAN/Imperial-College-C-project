#include <hwloc.h>
#include "decode.h"
#include "emulate.h"

int main(int argc,  char **argv) {
    MACHINE* ARM = createMachine();
    loadBinaryFile(ARM, "/homes/klc116/arm11_1617_testsuite/test_cases/add01");
    printMachineState(ARM);
/*    char hex[16];
    DATAPROCESSING dpstruct;
    printBit(0xFu<<11);
    scanf("%s", hex);
    printf("%x\n", generateDataFromHex(hex));
    u32 instruction = generateDataFromHex(hex);
    printBit(instruction);
    printDataProcessing(DecodeDataProcessing(instruction));


    printBit(GENERATEMASK(2,2));
    printBit(GETBITS(0xe3a01001,21,24));*/
    printMachineState(ARM);
    return EXIT_SUCCESS;
}


