#include "./binaryTree.h"

#include <stdio.h>
#include <stdlib.h>

bTree* createBTree() {
    return NULL;
}

bTree* insertBTreeNode(bTree* root, void* ID, void* load, int (*cmpr)(void*, void*)) {
    if (root != NULL) {
        int compareResult = cmpr(ID, root->ID);
        if (compareResult == 0) {
            return root;
        } else if (compareResult > 0) {
            root->rightChild = insertBTreeNode(root->rightChild, ID, load, cmpr);
            return root;
        }
        root->leftChild = insertBTreeNode(root->leftChild, ID, load, cmpr);
        return root;
    }
    bTree* newbTree = (bTree*)malloc(sizeof(bTree));
    newbTree->ID = ID;
    newbTree->load = load;
    newbTree->leftChild = NULL;
    newbTree->rightChild = NULL;
    return newbTree;
}

void* searchBTree(bTree* root, void* ID, int (*cmpr)(void*, void*)) {
    if (root != NULL) {
        int compareResult = cmpr(ID, root->ID);
        if (compareResult == 0) {
            return root;
        } else if (compareResult > 0) {
            return searchBTree(root->rightChild, ID, cmpr);
        }
        return searchBTree(root->leftChild, ID, cmpr);
    }
    return NULL;
}

void printBTree(bTree* root, void (*printCallBack)(bTree*)) {
    if (root != NULL) {
        printBTree(root->leftChild, printCallBack);
        printCallBack(root);
        printBTree(root->rightChild, printCallBack);
    }
}