class Solution {
public:
  ListNode *detectAndRemoveCycle(ListNode *head) {
    ListNode *slow = head;
    ListNode *fast = head;
    while (fast != nullptr && fast->next != nullptr) {
      slow = slow->next;
      fast = fast->next->next;
      if (slow == fast) {
        break;
      }
    }
    if (slow != fast) {
      return head;
    }
    slow = head;
    while (slow != fast) {
      slow = slow->next;
      fast = fast->next;
    }
    return slow;
  }
};