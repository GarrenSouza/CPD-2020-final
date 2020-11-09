
typedef struct ListNode {
    void* value;
    struct ListNode* nextNode;
} ListNode;

ListNode* createListNode();
ListNode* pushListNode(void* value, ListNode* head);
ListNode* popListNode(ListNode* head);
ListNode* deleteNode(ListNode* head);                   // Not available
ListNode* insertNode(ListNode* head);                   // Not available
ListNode* concatLists(ListNode* head, ListNode* tail);  // Not available
void destroyListNode(ListNode* head);