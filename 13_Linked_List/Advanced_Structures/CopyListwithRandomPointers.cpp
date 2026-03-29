class Solution {
public:
  Node *copyRandomList(Node *head) {
    Node *dummy = new Node(0);
    Node *tail = dummy;
    while (head != nullptr) {
      tail->next = new Node(head->val);
      tail = tail->next;
      head = head->next;
    }
    return dummy->next;
  }
};