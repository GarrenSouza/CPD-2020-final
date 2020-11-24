
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _BOOLEANS_
#define TRUE 1;
#define FALSE 0;
#endif

// Headers
#include "hashTable.h"

// External dependencies
#include "dependencies/murmur3.h"

char *_allocString(char *string) {
    char *newString = (char *)malloc((strlen(string) + 1) * sizeof(char));
    strcpy(newString, string);
    newString[strlen(string)] = '\0';
    return newString;
}

uint32_t murmurHashing(char *string, uint32_t seed) {
    uint32_t hash;
    MurmurHash3_x86_32((const void *)string, strlen(string),
                       MURMUR_SEED_COEFCIENT, &hash);
    return hash;
}

uint32_t polynomialHashing(char *string, uint32_t coeficient) {
    size_t acum = 0;
    for (size_t i = 0; i < strlen(string); i++) {
        acum = coeficient * acum + string[i];
    }
    return acum;
}

// // Closed Addressing (Chaining)

int ClosedAddressingInsert(hashTable *hashTable, size_t ID, void *data) {
    if ((hashTable->load) < (hashTable->size) && !(hashTable->searchKey(hashTable, ID))) {
        hashNode *newHashNode = (hashNode *)malloc(sizeof(hashNode));
        uint32_t hash = hashTable->mainHashingFunction(ID) % hashTable->size;
        newHashNode->nextNode = *(hashTable->dataArray + hash);
        *(hashTable->dataArray + hash) = newHashNode;
        (hashTable->load)++;
        newHashNode->data = data;
        newHashNode->ID = ID;
        if (newHashNode->nextNode != NULL) (hashTable->collisions)++;
        return TRUE;
    }
    return FALSE;
}

// int ClosedAddressingInsert(hashTable *hashTable, char *string, size_t ID, ListNode *genres) {
//     if ((hashTable->load) < (hashTable->size) && hashTable->searchKey(hashTable, string) == -1) {
//         hashNode *newString = (hashNode *)malloc(sizeof(hashNode));
//         uint32_t hash = hashTable->mainHashingFunction(string, hashTable->hashTableType & 1 ? MURMUR_SEED_COEFCIENT : POLYNOMIAL_COEFCIENT) % hashTable->size;
//         newString->string = _allocString(string);
//         newString->nextNode = *(hashTable->dataArray + hash);
//         newString->ID = ID;
//         newString->genres = genres;
//         *(hashTable->dataArray + hash) = newString;
//         (hashTable->load)++;
//         if (newString->nextNode != NULL) (hashTable->collisions)++;
//         return TRUE;
//     }
//     return FALSE;
// }

// int ClosedAddressingDelete(hashTable *hashTable, char *string) {
//     uint32_t hash = hashTable->mainHashingFunction(string, hashTable->hashTableType & 1 ? MURMUR_SEED_COEFCIENT : POLYNOMIAL_COEFCIENT) % hashTable->size;
//     hashNode *iterator = *(hashTable->dataArray + hash);
//     hashNode *aux = NULL;
//     while (iterator != NULL && strcmp(string, iterator->string)) {
//         aux = iterator;
//         iterator = iterator->nextNode;
//     }
//     if (iterator != NULL) {
//         if (aux == NULL)
//             *(hashTable->dataArray + hash) = iterator->nextNode;
//         else
//             aux->nextNode = iterator->nextNode;
//         free(iterator);
//         return TRUE;
//     }
//     return FALSE;
// }

int ClosedAddressingSearch(hashTable *hashTable, size_t ID) {
    hashNode *iterator = *(hashTable->dataArray + (hashTable->mainHashingFunction(ID) % hashTable->size));
    while (iterator != NULL) {
        if (ID == iterator->ID) {
            return TRUE;
        }
        iterator = iterator->nextNode;
    }
    return FALSE;
}

// int ClosedAddressingSearch(hashTable *hashTable, char *string) {
//     hashNode *iterator = *(hashTable->dataArray + (hashTable->mainHashingFunction(string, hashTable->hashTableType & 1 ? MURMUR_SEED_COEFCIENT : POLYNOMIAL_COEFCIENT) % hashTable->size));
//     int iterations = 0;
//     while (iterator != NULL) {
//         iterations++;
//         if (strcmp(string, iterator->string) == 0) {
//             hashTable->entriesCheckedSoFar += iterations;
//             return iterations;
//         }
//         iterator = iterator->nextNode;
//     }
//     hashTable->entriesCheckedSoFar += iterations;
//     return -1;
// }

hashNode *ClosedAddressingGetEntry(hashTable *hashTable, size_t ID) {
    hashNode *iterator = *(hashTable->dataArray + (hashTable->mainHashingFunction(ID) % hashTable->size));
    while (iterator != NULL) {
        if (ID == iterator->ID) {
            return iterator;
        }
        iterator = iterator->nextNode;
    }
    return NULL;
}

// hashNode *ClosedAddressingGetEntry(hashTable *hashTable, char *string) {
//     hashNode *iterator = *(hashTable->dataArray + (hashTable->mainHashingFunction(string, hashTable->hashTableType & 1 ? MURMUR_SEED_COEFCIENT : POLYNOMIAL_COEFCIENT) % hashTable->size));
//     int iterations = 0;
//     while (iterator != NULL) {
//         iterations++;
//         if (strcmp(string, iterator->string) == 0) {
//             hashTable->entriesCheckedSoFar += iterations;
//             return iterator;
//         }
//         iterator = iterator->nextNode;
//     }
//     hashTable->entriesCheckedSoFar += iterations;
//     return NULL;
// }

// // Open Addressing

// int OpenAddressingInsert(hashTable *hashTable, char *string, size_t ID, ListNode *genres) {
//     if ((hashTable->load) < (hashTable->size) && hashTable->searchKey(hashTable, string) == -1) {
//         uint32_t hash = hashTable->mainHashingFunction(string, hashTable->hashTableType & 1 ? MURMUR_SEED_COEFCIENT : POLYNOMIAL_COEFCIENT);
//         uint32_t hashTableSize = hashTable->size;
//         hashNode *aux = *(hashTable->dataArray + hash % hashTableSize);
//         if (aux != NULL) {
//             (hashTable->collisions)++;
//             if (aux->isActive) {
//                 uint32_t hash_b = hashTable->scndHashingFunction(string, hashTable->hashTableType & 1 ? POLYNOMIAL_COEFCIENT : MURMUR_SEED_COEFCIENT);
//                 for (int i = 1; aux != NULL && aux->isActive; i++) {
//                     hash += hash_b;
//                     aux = *(hashTable->dataArray + hash % hashTableSize);
//                 }
//             }
//         }
//         if (aux != NULL) {
//             aux->string = string;
//             aux->isActive = TRUE;
//         } else {
//             hashNode *newString = (hashNode *)malloc(sizeof(hashNode));
//             newString->string = _allocString(string);
//             newString->isActive = TRUE;
//             newString->ID = ID;
//             newString->genres = genres;
//             *(hashTable->dataArray + hash % hashTable->size) = newString;
//         }
//         (hashTable->load)++;
//         return TRUE;
//     }
//     return FALSE;
// }

// int OpenAddressingSearch(hashTable *hashTable, char *string) {
//     uint32_t hash = hashTable->mainHashingFunction(string, hashTable->hashTableType & 1 ? MURMUR_SEED_COEFCIENT : POLYNOMIAL_COEFCIENT);
//     uint32_t hashTableSize = hashTable->size;
//     hashNode *aux = *(hashTable->dataArray + hash % hashTableSize);
//     int i = 0;
//     if (aux != NULL) {
//         i++;
//         if (aux->isActive && strcmp(aux->string, string) == 0) {
//             (hashTable->entriesCheckedSoFar) += i;
//             return i;
//         }
//         uint32_t hash_b = hashTable->scndHashingFunction(string, hashTable->hashTableType & 1 ? POLYNOMIAL_COEFCIENT : MURMUR_SEED_COEFCIENT);

//         for (; aux != NULL && i < hashTable->size; i++) {
//             if (strcmp(aux->string, string) == 0) {
//                 (hashTable->entriesCheckedSoFar) += i + 1;
//                 return i + 1;
//             }
//             hash += hash_b;
//             aux = *(hashTable->dataArray + hash % hashTableSize);
//         }
//     }
//     (hashTable->entriesCheckedSoFar) += i + 1;
//     return -1;
// }

// int OpenAddressingDelete(hashTable *hashTable, char *string) {
//     uint32_t hash = hashTable->mainHashingFunction(string, hashTable->hashTableType & 1 ? MURMUR_SEED_COEFCIENT : POLYNOMIAL_COEFCIENT);
//     uint32_t hashTableSize = hashTable->size;
//     hashNode *aux = *(hashTable->dataArray + hash % hashTableSize);
//     if (aux != NULL) {
//         if (aux->isActive && strcmp(aux->string, string) == 0) {
//             aux->isActive = FALSE;
//             return TRUE
//         }
//         uint32_t hash_b = hashTable->scndHashingFunction(string, hashTable->hashTableType & 1 ? POLYNOMIAL_COEFCIENT : MURMUR_SEED_COEFCIENT);
//         for (int i = 1; aux != NULL && i < hashTable->size; i++) {
//             if (strcmp(aux->string, string) == 0) {
//                 if (aux->isActive) {
//                     aux->isActive = FALSE;
//                     return TRUE;
//                 }
//                 return FALSE;
//             }
//             hash += hash_b;
//             aux = *(hashTable->dataArray + hash % hashTableSize);
//         }
//     }
//     return FALSE;
// }

hashTable *createHashTable(size_t size, uint8_t addressingMode,
                           uint8_t hashingFunction) {
    if (size) {
        hashTable *newStringHashtable =
            (hashTable *)malloc(sizeof(hashTable));
        newStringHashtable->dataArray =
            (hashNode **)malloc(size * sizeof(hashNode *));
        newStringHashtable->load = 0;
        newStringHashtable->collisions = 0;
        newStringHashtable->size = size;
        newStringHashtable->hashTableType = addressingMode;
        newStringHashtable->hashTableType <<= 1;
        newStringHashtable->hashTableType |= hashingFunction;
        newStringHashtable->entriesCheckedSoFar = 0;
        for (size_t i = 0; i < size; i++)
            *(newStringHashtable->dataArray + i) = NULL;

        switch (hashingFunction) {
            case POLYNOMIAL_HASHING_FUNCTION:
                newStringHashtable->mainHashingFunction = knuthsIntegerHashing;
                newStringHashtable->scndHashingFunction = knuthsIntegerHashing;
                break;
            case MURMUR_HASHING_FUNCTION:
                newStringHashtable->mainHashingFunction = knuthsIntegerHashing;
                newStringHashtable->scndHashingFunction = knuthsIntegerHashing;
                break;
            default:
                return NULL;
        }
        switch (addressingMode) {
            case OPEN_ADDRESS_CR:
                // newStringHashtable->add = OpenAddressingInsert;
                // newStringHashtable->delete = OpenAddressingDelete;
                // newStringHashtable->searchKey = OpenAddressingSearch;
                // break;
            case CLOSED_ADDRESS_CR:
                newStringHashtable->add = ClosedAddressingInsert;
                // newStringHashtable->delete = ClosedAddressingDelete;
                newStringHashtable->searchKey = ClosedAddressingSearch;
                newStringHashtable->getEntry = ClosedAddressingGetEntry;
                break;
            default:
                return NULL;
        }
        return newStringHashtable;
    }
    return NULL;
}

void destroyHashTable(hashTable *hashTable) {
    hashNode *aux, *next;
    // chaining case
    if (hashTable->hashTableType & 2) {
        for (size_t i = 0; i < hashTable->size; i++) {
            aux = *(hashTable->dataArray + i);
            while (aux != NULL) {
                next = aux->nextNode;
                free(aux);
                aux = next;
            }
        }
    } else {
        for (size_t i = 0; i < hashTable->size; i++) {
            aux = *(hashTable->dataArray + i);
            if (aux != NULL && aux->isActive) {
                free(aux);
            }
        }
    }
    free(hashTable->dataArray);
    free(hashTable);
}

void printHashTable(hashTable *hashTable, void (*printCallBack)(void *), int printEntries) {
    hashNode *aux;
    // chaining case
    if (hashTable->hashTableType & 2) {
        if (printEntries) {
            printf("-----|Keys|-----\n");
            for (size_t i = 0; i < hashTable->size; i++) {
                aux = *(hashTable->dataArray + i);
                while (aux != NULL) {
                    printCallBack(aux->data);
                    aux = aux->nextNode;
                }
            }
            printf("----------------\n");
        }
        printf("Addressing: Closed (Chaining)\n");
    } else {
        if (printEntries) {
            printf("-----|Keys|-----\n");
            for (size_t i = 0; i < hashTable->size; i++) {
                aux = *(hashTable->dataArray + i);
                if (aux != NULL && aux->isActive) printf("> %s\n", aux->string);
            }
            printf("----------------\n");
        }
        printf("Addressing: Open (Double Hashing)\n");
    }
    printf("Size: %u\n", hashTable->size);
    printf("Load: %u\n", hashTable->load);
    printf("Collisions: %lu\n", hashTable->collisions);
    printf("Entries checked so far: %lu\n", hashTable->entriesCheckedSoFar);
    printf("Primary Hashing algorithm: %s\n", hashTable->hashTableType & 1 ? "Murmur3" : "Polynomial");
    printf("Secondary Hashing algorithm: %s\n", hashTable->hashTableType & 1 ? "Polynomial" : "Murmur3");
}
uint32_t knuthsIntegerHashing(uint32_t key) {
    int c2 = 0x27d4eb2d;  // a prime or an odd constant
    key = (key ^ 61) ^ (key >> 16);
    key = key + (key << 3);
    key = key ^ (key >> 4);
    key = key * c2;
    key = key ^ (key >> 15);
    return key;
}