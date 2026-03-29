class Solution {
public:
  ListNode *swapPairs(ListNode *head) {
    ListNode *dummy = new ListNode(0);
    dummy->next = head;
    ListNode *prev = dummy;
    while (head != nullptr && head->next != nullptr) {
      ListNode *first = head;
      ListNode *second = head->next;
      prev->next = second;
      first->next = second->next;
      second->next = first;
      prev = first;
      head = first->next;
    }
    return dummy->next;
  }
};