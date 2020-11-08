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
    newTrie->parent = NULL;
    newTrie->isEndOfWord = FALSE;
    newTrie->childCounter = 0;
    return newTrie;
}

char *allocString(char *string)
{
    char *newString = (char *)malloc((strlen(string) + 1) * sizeof(char));
    strcpy(newString, string);
    newString[strlen(string)] = '\0';
    return newString;
}

trieNode *insertNode(char *string, trieNode *root)
{
    if (root->childCounter == 0 && root->string == NULL)
    {
        root->string = allocString(string);
        root->isEndOfWord = TRUE;
    }
    else
    {
        size_t i = 0;
        for (; string[i] != '\0' && root->string[i] != '\0' && string[i] == root->string[i]; i++)
            ;
        if (i == strlen(root->string))
        {
            if (i == strlen(string))
            {
                root->isEndOfWord = TRUE;
                return root;
            }
            else if (root->childs[string[i]] == NULL)
            {
                trieNode *newNode = createTrieNode();
                newNode->string = allocString(string);
                newNode->isEndOfWord = TRUE;
                newNode->parent = root;
                (root->childCounter)++;
                root->childs[string[i]];
                return root;
            }
            root->childs[string[i]] = insertNode(string + i, root->childs[string[i]]);
            return root;
        }
        else
        {
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

            newRoot->childs[newChild->string[0]] = newChild;
            newRoot->childs[root->string[0]] = root;
            (newRoot->childCounter) = 2;

            root->parent = newRoot;

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
        else
            return searchNode(string + i, root->childs[string[i]]);
    }
    return NULL;
}

void printPatricia(trieNode *root)
{
    if (root == NULL)
        ;
    else
    {
        if (root->isEndOfWord)
            printf("*");
        printf("%s", root->string);
        if (root->parent != NULL)
        {
            printf(", %s", root->parent->string);
        }
        printf(" Childs: %d\n", root->childCounter);
        for (size_t i = 0; i < ALPHABET_SIZE; i++)
        {
            printPatricia(root->childs[i]);
        }
    }
}

void deleteNode(char *string, trieNode *root)
{
    trieNode *aux = searchNode(string, root), *auxParent;
    if (aux != NULL)
    {
        if (aux->childCounter == 0)
        {
            auxParent = aux->parent;
            (auxParent->childCounter)--;
            auxParent->childs[aux->string[0]] = NULL;

            destroyTrieNodeLocally(aux);

            if (auxParent->childCounter == 1)
            {
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
        }
        else
            aux->isEndOfWord = FALSE;
    }
}

void destroyTrieNodeLocally(trieNode *node)
{
    free(node->string);
    for (size_t i = 0; i < ALPHABET_SIZE; i++)
        free(node->childs[i]);
    free(node);
}