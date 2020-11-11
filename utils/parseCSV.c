#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "../hashTable/hashTable.h"
#include "../dataStructures/triePatricia/triePatricia.h"
#include "../dataStructures/hashTable/hashTable.h"

int main(void) {
    FILE* file = fopen("movie.csv", "r");
    trieNode* tree = createTrieNode();
    stringHashTable* hashTable = createHashTable(256, CLOSED_ADDRESS_CR, MURMUR_HASHING_FUNCTION);

    char readBuffer[256];
    char movieTitle[256];
    char *genre;

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
            
            genre = strtok(readBuffer + j + 3, "|");
            while(genre != NULL){
                if(genre[strlen(genre) - 1] == '\n'){
                    genre[strlen(genre) - 2] = '\0';
                }
                // printf("%s\n", genre);
                hashTable->add(hashTable, genre);
                genre = strtok(NULL, "|");
            }        
        }

        printHashTable(hashTable, TRUE);

    } else
        printf("Deu ruim man!");

    // printPatricia(tree);
    // printf("%ld", wordCounter(tree));
    return 0;
}