#include <stdint.h>
#include <stdio.h>

#ifndef LINKED_LIST
#define LINKED_LIST
#include "../linkedList/linkedList.h"
#endif

#ifndef _HASH_CONFIG
#define OPEN_ADDRESS_CR 0
#define CLOSED_ADDRESS_CR 1

#define POLYNOMIAL_HASHING_FUNCTION 0
#define MURMUR_HASHING_FUNCTION 1

#define HASH_TABLE_SIZE 20011

#define POLYNOMIAL_COEFCIENT 7
#define MURMUR_SEED_COEFCIENT 0x0855e30d  //random number
#endif

typedef struct hashNode {
    uint8_t isActive;
    char *string;
    size_t ratingCounter;
    double averageRating;
    ListNode *genres;
    struct hashNode *nextNode;

    size_t ID;
    void *data;
} hashNode;

typedef struct hashTable {
    uint32_t load, size;
    size_t collisions, entriesCheckedSoFar;
    uint32_t (*mainHashingFunction)(uint32_t coeficient),
        (*scndHashingFunction)(uint32_t coeficient);
    hashNode **dataArray;
    uint8_t hashTableType;
    int (*delete)(struct hashTable *, size_t ID),
        (*searchKey)(struct hashTable *, size_t ID),
        (*add)(struct hashTable *hashTable, size_t ID, void *data);

    hashNode *(*getEntry)(struct hashTable *hashTable, size_t ID);  // needs clarification
} hashTable;

// HashTable Methods
hashTable *createHashTable(size_t size, uint8_t addressingMode, uint8_t hashingFunction);
void destroyHashTable(hashTable *hashTable);
void printHashTable(hashTable *hashTable, void (*printCallBack)(void *), int printEntries);

// // Addressing Methods

// Closed Addressing Methods
int ClosedAddressingInsert(hashTable *hashTable, size_t ID, void *data);
// int ClosedAddressingDelete(hashTable *hashTable, size_t ID);
int ClosedAddressingSearch(hashTable *hashTable, size_t ID);
hashNode *ClosedAddressingGetEntry(hashTable *hashTable, size_t ID);

// Open Address Methods
// int OpenAddressingInsert(hashTable *hashTable, char *string, size_t ID, ListNode *genres);
// int OpenAddressingDelete(hashTable *hashTable, char *string);
// int OpenAddressingSearch(hashTable *hashTable, char *string);
// hashNode *OpenAddressingGetEntry(hashTable *hashTable, char *string);  // Needs implementation

// Available Hashing Functions
uint32_t polynomialHashing(char *string, uint32_t coeficient);
uint32_t murmurHashing(char *string, uint32_t seed);
// uint32_t knuthsIntegerHashing(char *string, uint32_t seed);  // Needs implementation

uint32_t polynomialHashing(char *string, uint32_t coeficient);
uint32_t murmurHashing(char *string, uint32_t seed);
uint32_t knuthsIntegerHashing(uint32_t key);