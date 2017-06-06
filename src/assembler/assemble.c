#include "assemble.h"
#include "tokenizer.h"
#include "firstpass.h"

void binaryFileWriter(u32 instr[], char ** argv){
    FILE *ofp = fopen(argv[1],"wb");
    if(ofp == NULL){
        fprintf(stderr,"Unable to write file");
        exit(EXIT_FAILURE);
    }

    fwrite(instr,sizeof(instr),1,ofp);
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

int main(int argc, char **argv){
    char* lines[100];
    LINE_TOKEN* line_tokens[100];
    u32 numOfLines;
    numOfLines = sourceFileReader(lines, "/homes/klc116/arm11_1617_testsuite/test_cases/add01.s");
    printf("%d\n", numOfLines);
    for(int i = 0; i < numOfLines; i++) {
        printf("%s\n",lines[i]);
    }
    fileToTokens(line_tokens, lines, numOfLines);
    printTokens(line_tokens, numOfLines);
    return EXIT_SUCCESS;
}


