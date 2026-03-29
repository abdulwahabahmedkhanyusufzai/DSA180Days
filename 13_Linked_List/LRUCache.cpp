#include <unordered_map>

using namespace std;

class LRUCache {
private:
  // Define Doubly Linked List Node structure
  struct Node {
    int key;
    int value;
    Node *prev;
    Node *next;
    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
  };

  int capacity;
  unordered_map<int, Node *> cache;
  Node *head;
  Node *tail;

  // Insert node right after dummy head
  void addNode(Node *node) {
    node->prev = head;
    node->next = head->next;
    head->next->prev = node;
    head->next = node;
  }

  // Remove an existing node from the list
  void removeNode(Node *node) {
    Node *prevNode = node->prev;
    Node *nextNode = node->next;
    prevNode->next = nextNode;
    nextNode->prev = prevNode;
  }

  // Move an accessed node to the head (most recently used position)
  void moveToHead(Node *node) {
    removeNode(node);
    addNode(node);
  }

  // Remove the node just before the dummy tail (least recently used)
  Node *popTail() {
    Node *res = tail->prev;
    removeNode(res);
    return res;
  }

public:
  LRUCache(int limit) {
    capacity = limit;
    head = new Node(-1, -1);
    tail = new Node(-1, -1);
    head->next = tail;
    tail->prev = head;
  }

  int get(int key) {
    if (cache.find(key) != cache.end()) {
      Node *node = cache[key];
      moveToHead(node); // Move to front since it's recently used
      return node->value;
    }
    return -1; // Specific problem typically demands -1 if not found
  }

  void put(int key, int value) {
    if (cache.find(key) != cache.end()) {
      // Update the node value and move to head
      Node *node = cache[key];
      node->value = value;
      moveToHead(node);
    } else {
      // Make a new node
      Node *newNode = new Node(key, value);

      // If cache is at full capacity, drop the least recently used element
      if (cache.size() >= capacity) {
        Node *LRUNode = popTail();
        cache.erase(LRUNode->key);
        delete LRUNode;
      }

      cache[key] = newNode;
      addNode(newNode);
    }
  }

  // Clean up memory
  ~LRUCache() {
    Node *curr = head;
    while (curr != nullptr) {
      Node *next = curr->next;
      delete curr;
      curr = next;
    }
  }
};