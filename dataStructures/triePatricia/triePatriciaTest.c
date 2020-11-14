#include <stdio.h>
#include <stdlib.h>

#include "../hashTable/hashTable.h"
#include "./triePatricia.h"

int main() {
    // char *string = (char *)malloc(4 * sizeof(char));
    // free(string + 1);
    trieNode* Tree = createTrieNode();
    stringHashTable* hashTable = createHashTable(10, CLOSED_ADDRESS_CR, POLYNOMIAL_HASHING_FUNCTION);

    Tree = insertNode("BANANA", 12, Tree);
    // hashTable->add(hashTable, "BANANA");

    Tree = insertNode("DART", 12, Tree);
    // hashTable->add(hashTable, "BATMAN");

    Tree = insertNode("BANAL", 12, Tree);
    // hashTable->add(hashTable, "BANAL");

    Tree = insertNode("BANIDO", 12, Tree);
    // hashTable->add(hashTable, "BANIDO");

    Tree = insertNode("BAN", 12, Tree);
    // hashTable->add(hashTable, "BAN");

    printPatricia(Tree);
    ListNode* queryResult = createListNode();
    collectWithPrefix("BA", Tree, queryResult);
    // printf("\n");
    printList(queryResult);
    printf("\n");
    printf("\n");
    // printHashTable(hashTable, TRUE);
    return 0;
}