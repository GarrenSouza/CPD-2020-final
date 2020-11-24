#include <stdio.h>
#include <stdlib.h>

#include "./binaryTree.h"

int cmpr(void* idSource, void* idReference) {
    return *((int*)idSource) - *((int*)idReference);
}
void printCallBack(bTree* node) {
    printf("%d\n", *((int*)node->ID));
}

int main() {
    bTree* newBTree = createBTree();
    int* ID = (int*)malloc(12 * sizeof(int));
    *ID = 12;
    *(ID + 1) = 2;
    *(ID + 2) = 72;
    *(ID + 3) = -2;
    *(ID + 4) = 0;
    *(ID + 5) = 123;
    newBTree = insertNode(newBTree, ID, ID, cmpr);
    newBTree = insertNode(newBTree, ID + 1, ID + 1, cmpr);
    newBTree = insertNode(newBTree, ID + 2, ID + 2, cmpr);
    newBTree = insertNode(newBTree, ID + 3, ID + 3, cmpr);
    newBTree = insertNode(newBTree, ID + 4, ID + 4, cmpr);
    bTree* aux = searchNode(newBTree, ID + 5, cmpr);
    if (aux != NULL) {
        printCallBack(aux);
    } else {
        printf("Não encontrado!\n");
    }
    return 0;
}