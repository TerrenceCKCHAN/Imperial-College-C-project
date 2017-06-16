/////////////////////////////////////////////////////////////////////////////////////////
//C Group Project - First Year (2016-2017)
//File: ass_io.c
//Group: 6
//Member: Cheung, Ka (klc116), Mang, Hao (hxm16), Cheuk, Ki (kfc216), Chan, Chun (ckc116)
/////////////////////////////////////////////////////////////////////////////////////////
#include "assemble.h"

/////////////////////////////////////////////////////////////////////////////////////////
// Write the instructions to a binary file
// Pre: valid output path is provided
// Post: The instrucitons are loaded to the binary file
/////////////////////////////////////////////////////////////////////////////////////////
void binaryFileWriter(u32 instr[], char *path, u32 numOfInstructions){
    FILE *ofp = fopen(path, "wb");
    if(ofp == NULL){
        fprintf(stderr,"Unable to write file");
        exit(EXIT_FAILURE);
    }

    fwrite(instr, sizeof(u32), numOfInstructions, ofp);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Load the source file to the line array
// Pre: valid assembly file is provided
// Post: The assembly lines is loaded the the line array
/////////////////////////////////////////////////////////////////////////////////////////
u32 sourceFileReader(char *lines[], char *filename){
    FILE *pFile;
    char buffer[512];
    u32 index = 0;

    pFile = fopen (filename , "r");
    if (pFile == NULL) {
        perror("Error opening file");
    } else {
        while (fgets(buffer, sizeof(buffer), pFile)) {
            int length = (int)strlen(buffer);
            buffer[length - 1] = '\0';
            lines[index] = malloc(sizeof(buffer));
            strcpy(lines[index], buffer);
            index++;
        }
        fclose (pFile);
    }
    return index;
}