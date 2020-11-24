#include <stdlib.h>

#ifndef LINKED_LIST
#define LINKED_LIST
#include "../linkedList/linkedList.h"
#endif

#ifndef _BOOLEANS_

#define TRUE 1
#define FALSE 0

#endif
typedef struct trieNode {
    char *string;
    char isEndOfWord;
    int childCounter;
    size_t ID;
    struct trieNode **childs, *parent;
} trieNode;

static char stringBuffer[512] = {'\0'};

trieNode *insertNode(char *string, size_t ID, trieNode *root);
void deleteNode(char *string, trieNode *root);
trieNode *createTrieNode();
void destroyTrieNodeLocally(trieNode *node);
trieNode *searchNode(char *string, trieNode *root);
void printPatricia(trieNode *root);
char *allocString(char *string);
void collectWithPrefix(char *string, trieNode *root, ListNode *queryResult);
void collectAllStrings(trieNode *root, ListNode *queryResult);

void collectAllIDs(trieNode *root, ListNode *queryResult);
void collectIDsWithPrefix(char *prefix, trieNode *root, ListNode *queryResult);

size_t wordCounter(trieNode *root);