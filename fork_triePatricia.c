#include "./triePatricia.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef BOOLEANS

#define TRUE 1
#define FALSE 0

#endif

#ifndef TRIE_CONFIG

// Revisar mais tarde
#define ALPHABET_SIZE 256

#endif

trieNode *createTrieNode()
{
    trieNode *newTrie = (trieNode *)malloc(sizeof(trieNode));
    newTrie->childs = (trieNode **)malloc(ALPHABET_SIZE * sizeof(trieNode *));
    for (size_t i = 0; i < ALPHABET_SIZE; i++)
    {
        newTrie->childs[i] = NULL;
    }
    newTrie->string = NULL;
    newTrie->hasChild = FALSE;
    return newTrie;
}

trieNode *insertNode(char *string, trieNode *root)
{
    if (!root->hasChild && root->string == NULL)
    {
        root->string = string;
    }
    else
    {
        size_t i = 0;
        for (; string[i] != '\0' && root->string[i] != '\0' && string[i] == root->string[i]; i++)
            ;
        if (root->hasChild)
        {
            if (root->childs[string[i]] == NULL)
            {
                trieNode *newNode = createTrieNode();
                newNode->string = string + i;
                root->childs[string[i]] = newNode;
                return root;
            }
            else
            {
                root->childs[string[i]] = insertNode(string + i, root->childs[string[i]]);
                return root;
            }
        }
        if (i)
        {
            trieNode *newRoot = createTrieNode();
            newRoot->string = (char *)malloc((i + 1) * sizeof(char));
            strncpy(newRoot->string, string, i);
            newRoot->string[i] = '\0';
            root->string = root->string + i;

            trieNode *newChild = createTrieNode();
            newChild->string = (char *)malloc((strlen(string) - i + 1) * sizeof(char));
            newChild->string = string + i;

            newRoot->childs[newChild->string[0]] = newChild;
            newRoot->childs[root->string[0]] = root;
            newRoot->hasChild = TRUE;
            return newRoot;
        }
    }
}

trieNode *searchNode(char *string, trieNode *root)
{
    if (root == NULL)
        return NULL;
    size_t i = 0;
    for (; string[i] != '\0' && root->string[i] != '\0' && string[i] == root->string[i]; i++)
        ;
    if (i == strlen(root->string))
    {
        if (i == strlen(string))
            if (root->isEndOfWord)
                return root;
            else
                return NULL;
    }
    else
        return searchNode(string + i, root->childs[string[i]]);
}

void deleteNode(char *string, trieNode *root);

void printPatricia(trieNode *root)
{
    if (root == NULL)
        ;
    else
    {
        printf("%s\n", root->string);
        for (size_t i = 0; i < ALPHABET_SIZE; i++)
        {
            printPatricia(root->childs[i]);
        }
    }
}

void destroyTrieNode();