#include "../linkedList/linkedList.h"
typedef struct trieNode {
    char *string;
    char isEndOfWord;
    int childCounter;
    struct trieNode **childs, *parent;
} trieNode;

static char stringBuffer[512] = {'\0'};

trieNode *insertNode(char *string, trieNode *root);
void deleteNode(char *string, trieNode *root);
trieNode *createTrieNode();
void destroyTrieNodeLocally(trieNode *node);
trieNode *searchNode(char *string, trieNode *root);
void printPatricia(trieNode *root);
char *allocString(char *string);
void collectWithPrefix(char *string, trieNode *root, ListNode *queryResult);
void collectAllStrings(trieNode *root, ListNode *queryResult);