#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char T;
typedef struct node {
    T data;
    struct node* left;
    struct node* right;
} node;

node* createNode(char data) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int posicao(char* string, int start, int end, char value) {
    //recebe a string inteira, o intervalo e a letra que tá buscando
    for (int i = start; i <= end; i++) {
        if (string[i] == value)
            return i;
    }
    return -1;
}

node* buildTree(char* preorder, char* inorder, int comeco, int final, int* preIndex) {
    if (comeco > final)
        return NULL;

    node* newNode = createNode(preorder[*preIndex]);
    (*preIndex)++;

    if (comeco == final)
        return newNode;

    int inIndex = posicao(inorder, comeco, final, newNode->data); //acha nó atual

    //constroi os 2 lados da árvore
    newNode->left = buildTree(preorder, inorder, comeco, inIndex - 1, preIndex);
    newNode->right = buildTree(preorder, inorder, inIndex + 1, final, preIndex);

    return newNode;
}

void printPostOrder(node* root) {
    if (root == NULL)
        return;

    printPostOrder(root->left);
    printPostOrder(root->right);
    printf("%c", root->data);
}

void freeTree(node* root) { //liberar
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    int ncasos;
    scanf("%d", &ncasos);

    for (int i = 0; i < ncasos; i++) {
        int nNodes;
        scanf("%d", &nNodes);

        char preorder[53], inorder[53];
        scanf(" %s %s", preorder, inorder);

        int preIndex = 0;
        //primeiro constrói a arvore
        node* root = buildTree(preorder, inorder, 0, nNodes - 1, &preIndex);
        //depois chama o percurso pos ordem
        printPostOrder(root);
        printf("\n");

        freeTree(root);
    }

    return 0;
}
