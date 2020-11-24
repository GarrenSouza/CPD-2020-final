#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>  //ioctl() and TIOCGWINSZ
#include <time.h>
#include <unistd.h>  // for STDOUT_FILENO

// #include "../hashTable/hashTable.h"
#include "../dataStructures/binaryTree/binaryTree.h"
#include "../dataStructures/hashTable/hashTable.h"
#include "../dataStructures/triePatricia/triePatricia.h"

#ifndef _WIN32
static char clearCommand[] = "clear";
#endif
#ifdef _WIN32
static char clearCommand[] = "cls";
#endif

void clearScreen() {
    system(clearCommand);
}

int strCmpr(void* strSource, void* strRef) {
    return strcmp(strSource, strRef);
}

int intCmpr(void* strSource, void* strRef) {
    return *((int*)strSource) - *((int*)strRef);
}

void printTagsBTree(bTree* node) {
    printf("\n%s\n", ((char*)node->ID));
    ListNode* movieIDs = ((ListNode*)node->load)->nextNode;
    while (movieIDs != NULL) {
        printf("%d ", *((int*)movieIDs->value));
        movieIDs = movieIDs->nextNode;
    }
    printf("\n");
}

typedef struct Movie {
    char* title;
    size_t ID, ratingCounter;
    float rating;
    ListNode* genres;
} Movie;

typedef struct User {
    size_t ID;
    ListNode* movies;
    ListNode* ratings;
} User;

void printMovie(void* movie) {
    printf("%ld     %s\n", ((Movie*)movie)->ID, ((Movie*)movie)->title);
}

void printGenres(ListNode* genresList) {
}

void printUser(void* user) {
    printf(">%ld", ((User*)user)->ID);
    ListNode *aux = ((User*)user)->movies->nextNode, *auxRating = ((User*)user)->ratings->nextNode;

    while (aux != NULL) {
        printf("\n-%ld    %.3f", *((size_t*)aux->value), *((float*)auxRating->value));
        aux = aux->nextNode;
        auxRating = auxRating->nextNode;
    }
    printf("\n");
    ;
}

trieNode* readMoviesCSV(char* fileName, trieNode* tree, hashTable* hashTable) {
    FILE* file = fopen(fileName, "r");
    ListNode* genres;

    char readBuffer[256];
    char* movieTitle = (char*)malloc(256 * sizeof(char));
    char* genreBuffer;

    size_t id;
    if (file != NULL) {
        fgets(readBuffer, 256, file);
        while (!feof(file)) {
            Movie* newMovie = (Movie*)malloc(sizeof(Movie));
            newMovie->rating = 0.0;
            newMovie->ratingCounter = 0;
            newMovie->genres = createListNode();  // transformar lista em stack
            fgets(readBuffer, 256, file);
            size_t i = 0;
            for (; readBuffer[i] != ','; i++)
                ;
            readBuffer[i] = '\0';
            newMovie->ID = atoi(readBuffer);
            size_t j = i + 2;
            while (!(readBuffer[j] == '"' && readBuffer[j + 1] == ',' && readBuffer[j + 2] == '"')) {
                j++;
            }

            readBuffer[j] = '\0';
            newMovie->title = allocString(readBuffer + i + 2);
            tree = insertNode(newMovie->title, newMovie->ID, tree);

            genreBuffer = strtok(readBuffer + j + 3, "|");
            while (genreBuffer != NULL) {
                if (genreBuffer[strlen(genreBuffer) - 1] == '\n') {
                    genreBuffer[strlen(genreBuffer) - 2] = '\0';
                }
                newMovie->genres = pushListNode((void*)allocString(genreBuffer), newMovie->genres);
                genreBuffer = strtok(NULL, "|");
            }
            hashTable->add(hashTable, newMovie->ID, newMovie);
        }
        return tree;
    } else {
        printf("Deu ruim man!");
        return NULL;
    }
}

void readRatingCSV(char* fileName, hashTable* userHashTable, hashTable* moviesTable) {
    FILE* file = fopen(fileName, "r");
    char copyBuffer[256];
    char readBuffer[256];
    char* movieTitle = (char*)malloc(256 * sizeof(char));
    char* genreBuffer;
    ListNode* testList = createListNode();
    size_t* integerPocket;
    float* floatPocket;
    size_t acum = 0;
    int a = 0;
    // system("clear");
    size_t i, j;
    User* newUser;
    int isNew = FALSE;
    if (file != NULL) {
        fgets(readBuffer, 256, file);
        while (fgets(readBuffer, 256, file) != NULL) {
            for (i = 0; readBuffer[i] != ','; i++) {
            }
            integerPocket = (size_t*)malloc(sizeof(size_t));
            *integerPocket = atoi(readBuffer);
            hashNode* retrievedEntry = userHashTable->getEntry(userHashTable, *integerPocket);

            if (retrievedEntry == NULL) {
                newUser = (User*)malloc(sizeof(User));
                newUser->ID = *integerPocket;
                newUser->movies = createListNode();
                newUser->ratings = createListNode();
                isNew = TRUE;
            } else {
                newUser = retrievedEntry->data;
            }
            i++;
            j = i;
            for (; readBuffer[i] != ','; i++) {
            }
            integerPocket = (size_t*)malloc(sizeof(size_t));
            *integerPocket = atoi(readBuffer + j);
            newUser->movies = pushListNode((void*)integerPocket, newUser->movies);

            i++;
            j = i;
            for (; readBuffer[i] != ','; i++) {
            }
            floatPocket = (float*)malloc(sizeof(float));
            *floatPocket = atof(readBuffer + j);
            newUser->ratings = pushListNode((void*)floatPocket, newUser->ratings);

            hashNode* movie = moviesTable->getEntry(moviesTable, *integerPocket);
            ((Movie*)movie->data)->rating = (((Movie*)movie->data)->rating * ((Movie*)movie->data)->ratingCounter + *floatPocket) / (((Movie*)movie->data)->ratingCounter + 1);
            (((Movie*)movie->data)->ratingCounter)++;
            if (isNew) {
                userHashTable->add(userHashTable, newUser->ID, newUser);
                isNew = FALSE;
            }
        }
    } else {
        printf("Deu ruim man\n");
    }
}

bTree* readTags(char* fileName, bTree* tagsBTree) {
    FILE* file = fopen(fileName, "r");
    char copyBuffer[256];
    char readBuffer[768];
    char* auxBuffer;
    ListNode* tagMovies;
    size_t* movieID;
    size_t i, j;
    if (file != NULL) {
        fgets(readBuffer, 256, file);
        while (fgets(readBuffer, 512, file) != NULL) {
            for (i = 0; readBuffer[i] != ','; i++) {
            }
            i++;
            j = i;
            for (; readBuffer[i] != ','; i++) {
            }
            movieID = (size_t*)malloc(sizeof(size_t));
            *movieID = atoi(readBuffer + j);

            i++;
            j = i;
            for (; readBuffer[i] != '"'; i++) {
            }
            i++;
            j = i;
            for (; readBuffer[i] != '"'; i++) {
            }
            readBuffer[i] = '\0';
            bTree* retrievedBTreeNode = searchBTree(tagsBTree, allocString(readBuffer + j), strCmpr);
            if (retrievedBTreeNode != NULL) {
                if (searchListNode(retrievedBTreeNode->load, movieID, intCmpr) == NULL) {
                    retrievedBTreeNode->load = pushListNode(movieID, retrievedBTreeNode->load);
                    // printf("\n%s - %ld\n", readBuffer + j, *movieID);
                }
            } else {
                tagMovies = createListNode();
                tagMovies = pushListNode(movieID, tagMovies);
                tagsBTree = insertBTreeNode(tagsBTree, allocString(readBuffer + j), tagMovies, strCmpr);
            }
        }
        return tagsBTree;
    } else {
        printf("Deu ruim man\n");
    }
}

int main(void) {
    // readRating("../Dados/rating.csv");
    char fileName[] = "movie.csv";
    FILE* file = fopen(fileName, "r");
    char* tagPtr;
    trieNode* tree = createTrieNode();
    bTree* tagsBTree = createBTree();
    hashTable* movieHashTable = createHashTable(30000, CLOSED_ADDRESS_CR, MURMUR_HASHING_FUNCTION);
    hashTable* userHashTable = createHashTable(3000000, CLOSED_ADDRESS_CR, MURMUR_HASHING_FUNCTION);
    hashTable* tagHashTable = createHashTable(3000000, CLOSED_ADDRESS_CR, MURMUR_HASHING_FUNCTION);
    clearScreen();

    tree = readMoviesCSV(fileName, tree, movieHashTable);
    readRatingCSV("../Dados/rating.csv", userHashTable, movieHashTable);
    tagsBTree = readTags("../Dados/tag.csv", tagsBTree);

    // clock_t start = clock();
    // clock_t end = clock();
    // float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    // printf("Time spent reading the ratings: %f\n", seconds);

    // printBTree(tagsBTree, printTagsBTree);
    // printHashTable(userHashTable, printUser, TRUE);

    char readBuffer[1024];
    printf("garren&Pedro@CPD2020:~/%s$ ", fileName);
    fgets(readBuffer, 1024, stdin);
    readBuffer[strlen(readBuffer) - 1] = '\0';
    hashNode* retrievedHashNode;
    while (strcmp(readBuffer, "exit")) {
        if (strcmp(readBuffer, clearCommand) == 0) {
            clearScreen();
        } else if (strncmp(readBuffer, "user ", 4) == 0 && strlen(readBuffer) > 4) {
            retrievedHashNode = (hashNode*)userHashTable->getEntry(userHashTable, (size_t)atoi(readBuffer + 5));

            if (retrievedHashNode != NULL) {
                User* user = (User*)retrievedHashNode->data;
                ListNode* auxUserMovies = user->movies->nextNode;
                ListNode* auxUserRatings = user->ratings->nextNode;
                while (auxUserRatings != NULL) {
                    Movie* retrievedMovie = (Movie*)((hashNode*)movieHashTable->getEntry(movieHashTable, *((size_t*)auxUserMovies->value)))->data;
                    printf("%.2f    %s    %.6f    %ld\n", *((float*)auxUserRatings->value), retrievedMovie->title, retrievedMovie->rating, retrievedMovie->ratingCounter);
                    auxUserMovies = auxUserMovies->nextNode;
                    auxUserRatings = auxUserRatings->nextNode;
                }
            } else {
                printf("UserID not found!\n");
            }
        } else if (strncmp(readBuffer, "movie ", 6) == 0 && strlen(readBuffer) > 6) {
            ListNode *queryIDs = createListNode(), *auxNode;

            collectIDsWithPrefix(readBuffer + 6, tree, queryIDs);
            if (queryIDs->nextNode != NULL) {
                auxNode = queryIDs->nextNode;
                printf("ID    title    genres    avgRating    ratingsRcvd\n");
                while (auxNode != NULL) {
                    Movie* movie = (Movie*)((hashNode*)movieHashTable->getEntry(movieHashTable, *((size_t*)auxNode->value)))->data;
                    printf("-%ld    %s    genres %f    %ld-\n", movie->ID, movie->title, movie->rating, movie->ratingCounter);
                    auxNode = auxNode->nextNode;
                }

            } else
                printf("No matches found!\n");
            // destroyListNode(queryIDs);
        } else if (strncmp(readBuffer, "help ", 4) == 0) {
            if (strncmp(readBuffer + 4, " pls ", 4)) {
                printf("Who do you think you are? Hur I want help 'help' hur dur!\n");
            } else {
                printf("Well, that's nice of you to ask so kindly!\n");
                printf("The available commands are:\n");
                printf("   %s - Clear the screen\n", clearCommand);
                printf("   movie [Movie title prefix] - Search the database for movies starting with the given prefix and print them in the screen \n");
                printf("   exit - Closes the application console\n");
                printf("   help - Print this magnificent manual\n");
            }
        } else if (strncmp(readBuffer, "tag ", 3) == 0) {
            tagPtr = strtok(readBuffer + 4, " ");
            bTree* searchResult = ((bTree*)searchBTree(tagsBTree, tagPtr, strCmpr));
            if (searchResult != NULL) {
                ListNode* movieIDs = (ListNode*)searchResult->load;
                ListNode* movieIDsList = createListNode();
                ListNode* referenceList = createListNode();
                ListNode* innerAuxListPtr = createListNode();
                if (movieIDs != NULL) {
                    movieIDsList = pushListNode(movieIDs, movieIDsList);
                }

                while ((tagPtr = strtok(NULL, " ")) != NULL) {
                    searchResult = (bTree*)searchBTree(tagsBTree, tagPtr, strCmpr);
                    if (searchResult != NULL) {
                        movieIDs = (ListNode*)searchResult->load;
                        if (movieIDs != NULL)
                            movieIDsList = pushListNode(movieIDs, movieIDsList);
                    }
                }
                movieIDs = createListNode();                           // resposta final
                referenceList = (ListNode*)popListNode(movieIDsList);  // popa uma lista, será referencia
                movieIDsList = pushListNode(referenceList->value, movieIDsList);
                referenceList = referenceList->nextNode;
                innerAuxListPtr = movieIDsList->nextNode;
                int hasAllTheTags = TRUE;
                while (referenceList != NULL) {
                    printf("%ld\n", *((size_t*)referenceList->value));
                    while (innerAuxListPtr != NULL && hasAllTheTags) {
                        if (searchListNode(innerAuxListPtr->value, (int*)referenceList->value, intCmpr) == NULL)
                            hasAllTheTags = FALSE;
                        innerAuxListPtr = innerAuxListPtr->nextNode;
                    }
                    if (hasAllTheTags) {
                        movieIDs = pushListNode(referenceList->value, movieIDs);
                    }
                    referenceList = referenceList->nextNode;
                }
                ListNode* auxID;
                while (movieIDs->nextNode != NULL) {
                    auxID = ((ListNode*)popListNode(movieIDs));
                    if (auxID != NULL) {
                        hashNode* retrievedMovie = movieHashTable->getEntry(movieHashTable, *((size_t*)auxID->value));
                        Movie* movie = retrievedMovie->data;
                        printf("%s    genres    %.6f    %ld\n", movie->title, movie->rating, movie->ratingCounter);
                    }
                }
            }
        } else if (readBuffer[0] != '\0') {
            printf("Are you having a stroke?\n");
        }
        memset((void*)readBuffer, 0, 256);
        printf("garren&Pedro@CPD2020:~/%s$ ", fileName);
        fgets(readBuffer, 1024, stdin);
        readBuffer[strlen(readBuffer) - 1] = '\0';
    }
    clearScreen();
    return 0;
}