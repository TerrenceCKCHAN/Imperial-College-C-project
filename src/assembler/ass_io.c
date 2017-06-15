#include "assemble.h"
#include "ass_io.h"

void binaryFileWriter(u32 instr[], char *path, u32 numOfInstructions){
    FILE *ofp = fopen(path, "wb");
    if(ofp == NULL){
        fprintf(stderr,"Unable to write file");
        exit(EXIT_FAILURE);
    }

    fwrite(instr, sizeof(u32), numOfInstructions, ofp);
}

u32 sourceFileReader(char* lines[], char* filename){
    FILE * pFile;
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