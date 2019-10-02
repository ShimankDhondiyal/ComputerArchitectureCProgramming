#include <stdio.h>
#include <stdlib.h>


typedef struct treeNode {
    int data;
    struct treeNode *left, *right;
} treeNode;

//method declarations
void insert(treeNode **root, int v);
treeNode *createTreeNode(int v);
void traverse(treeNode **root);
void freeTree(treeNode *root);


int main(int argc, char * argv[]) {
    //confirm number of arguments
    if(argc < 2) {
        printf("error\n");
        return 0;
    }
    FILE *f;
    f = fopen(argv[1], "r");

    //file DNE
    if(f == NULL) {
        printf("error\n");
        return 0;
    }
    //check if file blank

    treeNode *root;
    char c;
    int i;
    
    //input nodes from file to tree
    while (fscanf(f, "%c\t%d\n", &c, &i) == 2) {
        //insert current number
        insert(&root, i);
    }

    //in-order traversal and printing
    traverse(&root);
    printf("\n");
    freeTree(&(*root));
    fclose(f);
    return 0;
}

void insert(treeNode **root, int v) {
    //iterate through tree and find duplicates/insertion point
    if (*root == NULL) {
        //createNode
        *root = createTreeNode(v);
    } else if((*root)->data == v) {
        //duplicate found, do nothing
        return;
    } else if ((*root)->data > v) {
        //keep searching
        insert(&(*root)->left, v);
    } else {
        //keep searching
        insert(&(*root)->right, v);
    }
    
    //check for malloc() error
//    if((*root = (treeNode *) malloc(sizeof (treeNode))) == 0) {
//        return;
//    }
}

treeNode *createTreeNode(int v) {
    treeNode *temp = (treeNode *) malloc(sizeof(treeNode));
    temp->data = v;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

void traverse (treeNode **root) {
    if(*root == 0)
        return;
    traverse(&(*root)->left);
    printf("%d\t", (*root)->data);
    traverse(&(*root)->right);
}

void freeTree(treeNode *root) {
    if(root != NULL){
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
