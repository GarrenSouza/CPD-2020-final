#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "../hashTable/hashTable.h"
#include "../dataStructures/triePatricia/triePatricia.h"
#include "../dataStructures/hashTable/hashTable.h"

int main(void) {
    FILE* file = fopen("movie.csv", "r");
    trieNode* tree = createTrieNode();
    stringHashTable* hashTable = createHashTable(30000, CLOSED_ADDRESS_CR, MURMUR_HASHING_FUNCTION);
    ListNode* genres = createListNode();

    char readBuffer[256];
    char movieTitle[256];
    char *genreBuffer;

    size_t id;
    if (file != NULL) {
        fgets(readBuffer, 256, file);
        while (!feof(file)) {
            // printf("%s", fgets(readBuffer, 256, file));
            fgets(readBuffer, 256, file);
            size_t i = 0;
            for (; readBuffer[i] != ','; i++)
                ;
            readBuffer[i] = '\0';
            id = atoi(readBuffer);
            size_t j = i;
            while (readBuffer[j] != '"' || readBuffer[j + 1] != ',' || readBuffer[j + 2] != '"') {
                j++;
            }
            movieTitle[j - i] = '\0';
            strncpy(movieTitle, readBuffer + i + 1, j - i);
            // printf("%ld %s", id, movieTitle);
            tree = insertNode(movieTitle, id, tree);
            // printf("%ld\n", wordCounter(tree));
            
            genreBuffer = strtok(readBuffer + j + 3, "|");
            while(genreBuffer != NULL){
                if(genreBuffer[strlen(genreBuffer) - 1] == '\n'){
                    genreBuffer[strlen(genreBuffer) - 2] = '\0';
                }
                genres = pushListNode((void*)allocString(genreBuffer), genres);
                // printf("%s\n", genre);
                genreBuffer = strtok(NULL, "|");
            }
            hashTable->add(hashTable, movieTitle, (size_t)id, genres);
            // destroyListNode(genres);
        }

        printHashTable(hashTable, TRUE);

    } else
        printf("Deu ruim man!");

    // printPatricia(tree);
    // printf("%ld", wordCounter(tree));
    return 0;
}