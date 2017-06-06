#include "assemble.h"
#include "tokenizer.h"

void binaryFileWriter(u32 instr[], char ** argv){
    FILE *ofp = fopen(argv[1],"wb");
    if(ofp == NULL){
        fprintf(stderr,"Unable to write file");
        exit(EXIT_FAILURE);
    }

    fwrite(instr,sizeof(instr),1,ofp);
}



int main(int argc, char **argv){
  return EXIT_SUCCESS;
}
