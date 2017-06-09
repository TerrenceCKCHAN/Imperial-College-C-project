/////////////////////////////////////////////////////////////////////////////////////////
//C Group Project - First Year (2016-2017)
//File:emu_io.c
//Group: 6
//Member: Cheung, Ka (klc116), Mang, Hao (hxm16), Cheuk, Ki (kfc216), Chan, Chun (ckc116)
/////////////////////////////////////////////////////////////////////////////////////////
#include "emulate.h"

/////////////////////////////////////////////////////////////////////////////////////////
// Load the binary file to machine memory
// Pre: valid binary file is provided
// Post: The binary code is loaded the the machine memory
/////////////////////////////////////////////////////////////////////////////////////////
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

    for(int i = 0; i < size; i++) {
        ARM->MEMORY[i] = combuffer[i];
    }

    fclose(ifp);
    free(combuffer);
}