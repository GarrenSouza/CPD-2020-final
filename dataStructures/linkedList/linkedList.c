#include "./linkedList.h"

#include <stdio.h>
#include <stdlib.h>

ListNode* createListNode() {
    ListNode* newListNode = (ListNode*)malloc(sizeof(ListNode));
    newListNode->nextNode = NULL;
    newListNode->value = NULL;
    return newListNode;
}
/**
 * Destroy the given Linked List
 * (Assumes that all values were allocated by malloc, other cases may cause undefined behvior)
 */
void destroyListNode(ListNode* head) {
    ListNode* auxNode;
    while (head != NULL) {
        auxNode = head->nextNode;
        if (head->value != NULL) free(head->value);
        free(head);
        head = auxNode;
    }
}

ListNode* pushListNode(void* value, ListNode* head) {
    ListNode* newNode = createListNode();
    newNode->value = value;
    ListNode* auxNode = head;
    if (auxNode != NULL) {
        while (auxNode->nextNode != NULL) {
            auxNode = auxNode->nextNode;
        }
        auxNode->nextNode = newNode;
        return head;
    }
    return newNode;
}

ListNode* popListNode(ListNode* head) {
    ListNode *auxNode = head, *prev = NULL;
    if (auxNode != NULL) {
        while (auxNode->nextNode != NULL) {
            prev = auxNode;
            auxNode = auxNode->nextNode;
        }
        if (prev != NULL)
            prev->nextNode = NULL;
        return auxNode;
    }
    return NULL;
}

void printList(ListNode* head) {
    ListNode* aux = head->nextNode;
    while (aux != NULL) {
        printf("%s\n", (char*)aux->value);
        aux = aux->nextNode;
    }
}