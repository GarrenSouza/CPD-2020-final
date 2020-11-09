#include <stdio.h>
#include <stdlib.h>

#include "./dataStructures/triePatricia/triePatricia.h"

int main() {
    // char *string = (char *)malloc(4 * sizeof(char));
    // free(string + 1);
    trieNode *Tree = createTrieNode();

    Tree = insertNode("BANANA", Tree);
    Tree = insertNode("BATMAN", Tree);
    Tree = insertNode("BANAL", Tree);
    Tree = insertNode("BANIDO", Tree);
    Tree = insertNode("BAN", Tree);

    printPatricia(Tree);
    printf("\n");
    deleteNode("BAN", Tree);
    deleteNode("BANANA", Tree);
    printPatricia(Tree);
    return 0;
}