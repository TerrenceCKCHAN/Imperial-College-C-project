#include "emulate.h"


void loadBinaryFile(MACHINE* ARM, char *address){
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

    for(int i = 0; i < size / 4; i++) {
        for(int byte = 0; byte < 4; byte++) {
            ARM->MEMORY[i] += combuffer[i * 4 + byte] << ((3 - byte) * 8);
        }
//        printf("%x ",combuffer[i]);
//        printBit(combuffer[i]);
//        printf("\n");
    }

    fclose(ifp);
    free(combuffer);
}