
typedef struct ListNode {
    void* value;
    struct ListNode* nextNode;
} ListNode;

ListNode* createListNode();
ListNode* pushListNode(void* value, ListNode* head);
ListNode* popListNode(ListNode* head);
void destroyListNode(ListNode* head);
// implement a toString method