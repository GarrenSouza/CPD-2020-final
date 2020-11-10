#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./linkedList.h"

int main(void) {
    ListNode* head = createListNode();
    head = pushListNode((void*)"Ba", head);
    head = pushListNode((void*)"na", head);
    head = pushListNode((void*)"na", head);
    popListNode(head);
    printList(head);

    return 0;
}