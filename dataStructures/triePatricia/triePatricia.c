#include "./triePatricia.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TRIE_CONFIG

// Revisar mais tarde
#define ALPHABET_SIZE 256

#endif

trieNode *createTrieNode() {
    trieNode *newTrie = (trieNode *)malloc(sizeof(trieNode));
    newTrie->childs = (trieNode **)malloc(ALPHABET_SIZE * sizeof(trieNode *));
    for (size_t i = 0; i < ALPHABET_SIZE; i++) {
        newTrie->childs[i] = NULL;
    }
    newTrie->string = NULL;
    newTrie->parent = NULL;
    newTrie->isEndOfWord = FALSE;
    newTrie->childCounter = 0;
    newTrie->ID = -1;
    return newTrie;
}

char *allocString(char *string) {
    char *newString = (char *)malloc((strlen(string) + 1) * sizeof(char));
    strcpy(newString, string);
    newString[strlen(string)] = '\0';
    return newString;
}

trieNode *insertNode(char *string, size_t ID, trieNode *root) {
    if (root->childCounter == 0 && root->string == NULL) {  // First node case
        root->string = allocString(string);
        root->ID = ID;
        root->isEndOfWord = TRUE;
        return root;
    } else {
        size_t i = 0;
        for (; string[i] != '\0' && root->string[i] != '\0' && string[i] == root->string[i]; i++)
            ;
        if (i == strlen(root->string)) {  // Root string was covered
            if (i == strlen(string)) {    // We have a match
                root->isEndOfWord = TRUE;
                root->ID = ID;
                return root;

            } else if (root->childs[string[i]] == NULL) {  // We got to a leaf and stll no match
                trieNode *newNode = createTrieNode();
                newNode->string = allocString(string);
                newNode->ID = ID;
                newNode->isEndOfWord = TRUE;
                newNode->parent = root;

                (root->childCounter)++;
                root->childs[string[i]] = newNode;
                return root;
            }
            root->childs[string[i]] = insertNode(string + i, ID, root->childs[string[i]]);  // No cover, not in a leaf, let's continue searching
            return root;
        } else {  // Node spliting case (Root string must be split to allocate the new Node)
            trieNode *newRoot = createTrieNode();
            newRoot->string = (char *)malloc((i + 1) * sizeof(char));
            strncpy(newRoot->string, string, i);
            newRoot->string[i] = '\0';
            root->string = allocString(root->string + i);
            newRoot->parent = root->parent;

            trieNode *newChild = createTrieNode();
            newChild->string = (char *)malloc((strlen(string) - i + 1) * sizeof(char));
            newChild->string = allocString(string + i);
            newChild->isEndOfWord = TRUE;
            newChild->parent = newRoot;
            newChild->ID = ID;

            newRoot->childs[newChild->string[0]] = newChild;
            newRoot->childs[root->string[0]] = root;
            (newRoot->childCounter) = 2;

            root->parent = newRoot;

            return newRoot;
        }
    }
}

trieNode *searchNode(char *string, trieNode *root) {
    if (root == NULL)
        return NULL;
    size_t i = 0;
    for (; string[i] != '\0' && root->string[i] != '\0' && string[i] == root->string[i]; i++)
        ;
    if (i == strlen(root->string)) {
        if (i == strlen(string)) {
            if (root->isEndOfWord)
                return root;
            else
                return NULL;
        } else {
            return searchNode(string + i, root->childs[string[i]]);
        }
    }
    return NULL;
}

void deleteNode(char *string, trieNode *root) {
    trieNode *aux = searchNode(string, root), *auxParent;
    if (aux != NULL) {
        if (aux->childCounter == 0) {
            auxParent = aux->parent;
            (auxParent->childCounter)--;
            auxParent->childs[aux->string[0]] = NULL;

            destroyTrieNodeLocally(aux);

            if (auxParent->childCounter == 1) {
                size_t i = 0;
                for (; i < ALPHABET_SIZE && auxParent->childs[i] == NULL; i++)
                    ;
                aux = auxParent->childs[i];

                auxParent->string = realloc(auxParent->string, (strlen(auxParent->string) + strlen(aux->string) + 1) * sizeof(char));
                strcat(auxParent->string, aux->string);
                auxParent->childs = aux->childs;
                auxParent->childCounter = aux->childCounter;
                auxParent->isEndOfWord = aux->isEndOfWord;

                for (size_t i = 0; i < ALPHABET_SIZE; i++)
                    free(auxParent->childs[i]);
            }
        } else
            aux->isEndOfWord = FALSE;
    }
}

void destroyTrieNodeLocally(trieNode *node) {
    free(node->string);
    for (size_t i = 0; i < ALPHABET_SIZE; i++)
        free(node->childs[i]);
    free(node);
}

void collectWithPrefix(char *string, trieNode *root, ListNode *queryResult) {
    if (root != NULL) {
        size_t i = 0;
        for (; string[i] != '\0' && root->string[i] != '\0' && root->string[i] == string[i]; i++)
            ;
        if (i) {
            if (strlen(string) == strlen(root->string)) {
                collectAllStrings(root, queryResult);
            } else if (i == strlen(root->string))
                collectWithPrefix(string + i, root->childs[string[i]], queryResult);
        }
    }
}

void collectAllStrings(trieNode *root, ListNode *queryResult) {
    if (root != NULL) {
        if (root->childCounter == 0) {
            strcat(stringBuffer, root->string);
            pushListNode((void *)allocString(stringBuffer), queryResult);
        } else {
            strcat(stringBuffer, root->string);
            int n = strlen(stringBuffer);
            if (root->isEndOfWord) {
                pushListNode((void *)allocString(stringBuffer), queryResult);
            }
            for (size_t i = 0; i < ALPHABET_SIZE; i++) {
                collectAllStrings(root->childs[i], queryResult);
                stringBuffer[n] = '\0';
            }
        }
    }
}

size_t wordCounter(trieNode *root) {
    if (root != NULL) {
        size_t words = 0;
        if (root->isEndOfWord)
            words = 1;
        for (size_t i = 0; i < ALPHABET_SIZE; i++) {
            words += wordCounter(root->childs[i]);
        }
        return words;
    }
    return 0;
}
