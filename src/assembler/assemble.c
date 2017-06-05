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

/*
BST_Node* allocBST_Node(void){
    BST_Node *node = malloc(sizeof(BST_Node));
    if(node ==NULL){
        perror("allocBSTNode");
        exit(EXIT_FAILURE);
    }
    return node;
}

void freeBST_Node(BST_Node* node){
    free(node);
}

BST* BST_init(BST* tree, bst_compare_t compare){
    tree->compare = compare;
    tree->root = NULL;
    return tree;
}


BST* insert_Node(BST* tree,char* key, u32 value ){
    
}*/