#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./linkedList.h"

void printList(ListNode* head) {
    if (head != NULL) {
        ListNode* auxNode = head->nextNode;
        while (auxNode != NULL) {
            printf("%s", (char*)auxNode->value);
            auxNode = auxNode->nextNode;
        }
    }
}

int main(void) {
    // ListNode* head = createListNode();
    // head = pushListNode((void*)"Ba", head);
    // head = pushListNode((void*)"na", head);
    // head = pushListNode((void*)"na", head);
    // popListNode(head);
    // printList(head);
    char* str_a = (char*)malloc(8 * sizeof(char));
    str_a[0] = 'b';
    str_a[1] = 'a';
    str_a[2] = 'n';
    str_a[3] = 'k';
    str_a[4] = 's';
    str_a[5] = '\0';
    strcat(str_a + strlen(str_a), "y");  // it works just as expected!
    printf("%s", str_a);
    return 0;
}