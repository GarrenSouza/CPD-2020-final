#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>  //ioctl() and TIOCGWINSZ
#include <time.h>
#include <unistd.h>  // for STDOUT_FILENO

// #include "../hashTable/hashTable.h"
#include "../dataStructures/hashTable/hashTable.h"
#include "../dataStructures/triePatricia/triePatricia.h"

int main(void) {
    char fileName[] = "movie.csv";
    FILE* file = fopen(fileName, "r");
    trieNode* tree = createTrieNode();
    stringHashTable* hashTable = createHashTable(30000, CLOSED_ADDRESS_CR, MURMUR_HASHING_FUNCTION);
    ListNode* genres;

    char readBuffer[256];
    char* movieTitle = (char*)malloc(256 * sizeof(char));
    char* genreBuffer;

    size_t id;
    system("clear");
    if (file != NULL) {
        // time_t start, end;
        // time(&start);
        fgets(readBuffer, 256, file);
        while (!feof(file)) {
            genres = createListNode();
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
            *(movieTitle + j - i) = '\0';
            strncpy(movieTitle, readBuffer + i + 1, j - i);
            movieTitle[strlen(movieTitle) - 1] = '\0';
            tree = insertNode(movieTitle + 1, id, tree);

            genreBuffer = strtok(readBuffer + j + 3, "|");
            while (genreBuffer != NULL) {
                if (genreBuffer[strlen(genreBuffer) - 1] == '\n') {
                    genreBuffer[strlen(genreBuffer) - 2] = '\0';
                }
                genres = pushListNode((void*)allocString(genreBuffer), genres);
                genreBuffer = strtok(NULL, "|");
            }
            hashTable->add(hashTable, movieTitle + 1, (size_t)id, genres);
        }
        // time(&end);
        // float seconds = (float)(end - start) / CLOCKS_PER_SEC;
        // printf("|%s was processed in %f\n", fileName, difftime(end, start));
    } else
        printf("Deu ruim man!");

    printf("garren&Pedro@CPD2020:~/%s$ ", fileName);
    fgets(readBuffer, 256, stdin);
    readBuffer[strlen(readBuffer) - 1] = '\0';
    while (strcmp(readBuffer, "exit")) {
        if (strcmp(readBuffer, "clear") == 0) {
            system("clear");
        } else if (strncmp(readBuffer, "movie ", 6) == 0 && strlen(readBuffer) > 6) {
            ListNode* query = createListNode();

            collectWithPrefix(readBuffer + 6, tree, query);

            // ListNode* aux = query->nextNode;

            // while (aux != NULL) {
            //     printf("%s\n", (char*)aux->value);
            //     stringNode* entry = hashTable->getEntry(hashTable, ((char*)(popListNode(aux))->value));
            //     // printf("ID: %ld | Title: %s | Genres: ", entry->ID, entry->string);
            //     // printList(query);
            //     aux = aux->nextNode;
            // }
            if (query->nextNode != NULL) {
                printf("\n");
                printList(query);
            } else
                printf("No matches found!\n");
            destroyListNode(query);
        } else if (readBuffer[0] != '\0') {
            printf("Malformed Input!\n");
        }
        memset((void*)readBuffer, 0, 256);
        printf("garren&Pedro@CPD2020:~/%s$ ", fileName);
        fgets(readBuffer, 256, stdin);
        readBuffer[strlen(readBuffer) - 1] = '\0';
    }
    // ListNode* query = createListNode();
    // collectAllStrings(tree, query);
    // printList(query);

    // printf("\n\n");
    // printPatricia(tree);
    system("clear");
    return 0;
}