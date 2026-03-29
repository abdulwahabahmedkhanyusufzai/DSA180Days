class Solution {
public:
  ListNode *reverseKGroup(ListNode *head, int k) {
    ListNode *dummy = new ListNode(0);
    dummy->next = head;
    ListNode *prev = dummy;
    while (head != nullptr) {
      ListNode *tail = head;
      for (int i = 0; i < k - 1 && tail != nullptr; i++) {
        tail = tail->next;
      }
      if (tail == nullptr) {
        break;
      }
      ListNode *next = tail->next;
      tail->next = nullptr;
      prev->next = reverseList(head);
      head->next = next;
      prev = head;
      head = next;
    }
    return dummy->next;
  }
};