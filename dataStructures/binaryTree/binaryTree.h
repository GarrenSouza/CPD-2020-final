

typedef struct bTree {
    void* ID;
    void* load;
    struct bTree *leftChild, *rightChild;
} bTree;

bTree* createBTree();
bTree* insertBTreeNode(bTree* root, void* ID, void* load, int (*cmpr)(void*, void*));
void* searchBTree(bTree* root, void* ID, int (*cmpr)(void*, void*));
void printBTree(bTree* root, void (*printCallBack)(bTree*));