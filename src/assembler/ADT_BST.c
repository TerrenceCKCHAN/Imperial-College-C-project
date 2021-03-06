/////////////////////////////////////////////////////////////////////////////////////////
//C Group Project - First Year (2016-2017)
//File: ADT_BST.c
//Group: 6
//Member: Cheung, Ka (klc116), Mang, Hao (hxm16), Cheuk, Ki (kfc216), Chan, Chun (ckc116)
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
//  Binary Search Tree Abstract Data Type (Alternative implementation to Linkedlist)
//  (Faster insertion and searching comparing to linked list)
//  key = labels in the assembler program
//  value = address of the labels
//  compare = Function to compare labels alphabetically (using strcmp in  string.h)
//  PRE: Valid label and its corresponding address is inserted in BST
//  POST:labels can be searched and return its address using bst_lookUpValue Function
/////////////////////////////////////////////////////////////////////////////////////////
#include "assemble.h"

struct BST* getNewinitTree(bst_compare_t compare){
    struct BST* tree = malloc(sizeof(struct BST));
    if(tree == NULL){
        perror("getNewTree");
        exit(EXIT_FAILURE);
    }
    tree->root = NULL;
    tree->compare = compare;
    return tree;
}


/////////////////////////////////////////////////////////////////////////////////////////
//Helper function for insertElem
/////////////////////////////////////////////////////////////////////////////////////////
struct BST_node* insertToNode(BST_node* node, char* key, void* value, bst_compare_t compare){
    BST_node * newNode = malloc(sizeof(BST_node));
    newNode->key = key;
    newNode->value = value;
    newNode->right=newNode->left =NULL;
    if(node == NULL){
        return newNode;
    }else{
        int comparison = compare(key,node->key);
        if(comparison <= 0){
            //if the value insert is less than or equal to current node, insert to left
            node->left=insertToNode(node->left, key,value,compare);
            return node;
        }else{
            //if the value insert is larger to current node, insert to right
            node->right = insertToNode(node->right, key,value,compare);
            return node;
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////
//Insert new node into BST
//PRE: The BST to be inserted , the key and value to be insert and the compare function
//POST: A new node is inserted into the BST according to its key
/////////////////////////////////////////////////////////////////////////////////////////
void insertElem(struct BST* tree, char* key, void* value, bst_compare_t compare){
    tree->root = insertToNode(tree->root,key,value,compare);
}

void * getLeftmost(BST_node* node){
    if(node->left ==NULL){
        return node->value;
    } else{
        return getLeftmost(node->left);
    }

}
BST_node* deleteLeftMost(BST_node* node){
    if(node->left == NULL){
        return node->right;
    }else{
        BST_node* newchild = deleteLeftMost(node->left);
        node->left = newchild;
        return node;
    }
}

BST_node* deleteNode(BST_node* node){
    if(node->right == NULL && node->left == NULL){  //the node is a leaf
        return NULL;
    }else{
        if(node->right == NULL) {       //it has only left child
            return node->left;
        } else if(node->left == NULL){     //it has only right child
            return node->right;
        } else{
            void* tmpitem = getLeftmost(node->right);
            BST_node* newright = deleteLeftMost(node->right);
            node->value = tmpitem;
            node->right = newright;
            return node;
        }
    }
}

struct BST_node *deleteKey(BST_node * node,char* key, bst_compare_t compare){
    if(node == NULL){
        return node;
    }else{
        if(compare(node->key,key) == 0){
            node = deleteNode(node);
            return node;
        }else if(compare(node->key,key) <= 0){
            node->left = deleteKey(node->left,key,compare);
            return node;
        } else{
            node->right = deleteKey(node->right,key,compare);
            return node;
        }
    }
}



/////////////////////////////////////////////////////////////////////////////////////////
//Helper function for bst_lookUpValue
/////////////////////////////////////////////////////////////////////////////////////////
void* bst_lookUpValue_elem(BST_node* node, char* key, bst_compare_t compare){
    BST_node * current = node;
    if(current!= NULL) {
        if (compare(current->key, key) == 0) {
            return current->value;
        } else if (compare(current->key,key) > 0) {
            return bst_lookUpValue_elem(current->left, key, compare);
        } else if (compare(current->key, key) < 0) {
            return bst_lookUpValue_elem(current->right, key, compare);
        }
    }
    printf("No such key");
    return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////
//Look up the value in BST when key is provided
//PRE: The BST to be searched, the key and the compare function
//POST: return a value (u32 address) by its key
/////////////////////////////////////////////////////////////////////////////////////////
void* bst_lookUpValue(struct BST* tree, char* key,bst_compare_t compare){
    return bst_lookUpValue_elem(tree->root,key,compare);
}

/////////////////////////////////////////////////////////////////////////////////////////
//Compare function to compare string
/////////////////////////////////////////////////////////////////////////////////////////
int stringcmp(char* s1, char* s2){
    return strcmp(s1,s2);
}


/////////////////////////////////////////////////////////////////////////////////////////
//Helper function for printBST
/////////////////////////////////////////////////////////////////////////////////////////
void printBST_node(BST_node* node){
    if(node == NULL){
        return;
    }
    printBST_node(node->left);
    printBST_node(node->right);
    printf("key = %s, value = %u\n", node->key, (u32) node->value);
}
/////////////////////////////////////////////////////////////////////////////////////////
//Printing the post-order of BST
/////////////////////////////////////////////////////////////////////////////////////////
void printBST(struct BST* tree){
    if(tree->root ==NULL){
        return;
    }
    printBST_node(tree->root);
}

/////////////////////////////////////////////////////////////////////////////////////////
//Helper function for bst_destory
/////////////////////////////////////////////////////////////////////////////////////////
void bst_destroy_elem(struct BST_node * node){
    if(node==NULL){
        return;
    }
    bst_destroy_elem(node->left);
    bst_destroy_elem(node->right);
    free(node);
}

/////////////////////////////////////////////////////////////////////////////////////////
//Function to free the memory used by BST's pointer
/////////////////////////////////////////////////////////////////////////////////////////
void bst_destroy(struct BST* tree){
    bst_destroy_elem(tree->root);
}




