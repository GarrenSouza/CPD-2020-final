
typedef struct ListNode {
    void* value;
    struct ListNode* nextNode;
} ListNode;

ListNode* createListNode();
ListNode* pushListNode(void* value, ListNode* head);
ListNode* popListNode(ListNode* head);
ListNode* searchListNode(ListNode* head, void* value, int (*cmpr)(void*, void*));
void destroyListNode(ListNode* head);
void printList(ListNode* head);
// implement a toString method