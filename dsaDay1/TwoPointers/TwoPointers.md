Got it 👍 — let’s **add Backspace String Compare (LeetCode 844)** into your **Two Pointers Master Cheatsheet** under the correct variant (**Parallel Arrays / Two Sequences**).

Here’s the updated version with your requested addition 👇

---

## 🧩 Two Pointers Master Cheatsheet

---

### 1️⃣ Opposite Ends (Collision Pointers)

**Definition:** Two pointers start at opposite ends (left=0, right=n-1) and move inward based on conditions.
**Recognition:**

* Input is sorted or must be sorted first
* Problem asks about pairs/triplets that satisfy a condition
* Palindrome check (compare from both ends)

**Code Template:**

```cpp
int left = 0, right = n-1;
while (left < right) {
    if (nums[left] + nums[right] == target) return true;
    else if (nums[left] + nums[right] < target) left++;
    else right--;
}
```

**Example Problems:**

* 167\. Two Sum II (sorted array)
* Valid Palindrome
* Container With Most Water

---

### 2️⃣ Same Direction (Fast–Slow Pointers)

**Definition:** Both pointers move forward; fast expands, slow adjusts or shrinks. Often used as a sliding window.
**Recognition:**

* Problem mentions subarrays / substrings with constraints
* Need to track longest/shortest window
* In-place filtering like “remove duplicates” or “move zeros.”

**Code Template:**

```cpp
int slow = 0;
for (int fast = 0; fast < n; fast++) {
    // expand window with fast
    // condition? adjust with slow
}
```

**Example Problems:**

* 3\. Longest Substring Without Repeating Characters
* Remove Duplicates from Sorted Array
* Move Zeroes

---

### 3️⃣ Merging Style

**Definition:** Merge two sorted arrays/lists using pointers. Often done from the end to avoid overwriting.
**Recognition:**

* Given two sorted inputs, need to combine
* Target array has extra space at the end

**Code Template:**

```cpp
int i = m - 1, j = n - 1, k = m + n - 1;
while (i >= 0 && j >= 0) {
    if (nums1[i] > nums2[j]) nums1[k--] = nums1[i--];
    else nums1[k--] = nums2[j--];
}
while (j >= 0) nums1[k--] = nums2[j--];
```

**Example Problems:**

* 88\. Merge Sorted Array
* Merge Two Sorted Lists

---

### 4️⃣ Fast & Slow (Cycle Detection)

**Definition:** Move one pointer slowly, the other faster. If they meet → cycle exists.
**Recognition:**

* Linked list or graph cycle detection
* “Find cycle length” or “find start of cycle.”

**Code Template:**

```cpp
ListNode* slow = head;
ListNode* fast = head;
while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) return true;
}
return false;
```

**Example Problems:**

* 141\. Linked List Cycle
* Linked List Cycle II

---

### 5️⃣ Parallel Arrays (Two Sequences) ✅

**Definition:** Traverse two arrays/strings simultaneously with two pointers.
**Recognition:**

* “Find intersection of two arrays/lists.”
* “Merge intervals.”
* Compare two sequences element-by-element.

**Code Template:**

```cpp
int i = 0, j = 0;
while (i < n && j < m) {
    if (nums1[i] == nums2[j]) { /* handle */ i++; j++; }
    else if (nums1[i] < nums2[j]) i++;
    else j++;
}
```

**Example Problems:**

* 350\. Intersection of Two Arrays II
* Interval List Intersections
* **844. Backspace String Compare** ✅

---

### 6️⃣ Multiple Pointers (3+)

**Definition:** Use three or more pointers to partition into regions.
**Recognition:**

* Sorting with categories (e.g. 0s,1s,2s)
* Multi-partition problems

**Code Template (Dutch National Flag):**

```cpp
int low = 0, mid = 0, high = n-1;
while (mid <= high) {
    if (nums[mid] == 0) swap(nums[low++], nums[mid++]);
    else if (nums[mid] == 1) mid++;
    else swap(nums[mid], nums[high--]);
}
```

**Example Problems:**

* 75\. Sort Colors
* Partition Array

---

### 7️⃣ Sliding Window (Start–End)

**Definition:** A moving window bounded by start and end pointers.
**Recognition:**

* Problem involves subarray / substring lengths or sums
* “Find longest substring with condition…”
* “Smallest subarray with sum ≥ X.”

**Code Template:**

```cpp
int start = 0;
for (int end = 0; end < n; end++) {
    // include nums[end]
    while (window_invalid) {
        // shrink from start
        start++;
    }
    // update answer
}
```

**Example Problems:**

* 209\. Minimum Size Subarray Sum
* Minimum Window Substring
* Fruit Into Baskets

---

## ✅ Final Recap Table

| Variant         | Recognition Cue            | Example Problems                                                           |
| --------------- | -------------------------- | -------------------------------------------------------------------------- |
| Opposite Ends   | Sorted + pairs/triplets    | Two Sum II, Palindrome, Container With Most Water                          |
| Same Direction  | Subarrays / in-place ops   | Longest Substring, Remove Duplicates, Move Zeroes                          |
| Merging Style   | Two sorted arrays/lists    | Merge Sorted Array, Merge Lists                                            |
| Fast & Slow     | Linked list cycles         | Linked List Cycle I & II                                                   |
| Parallel Arrays | Compare two arrays/strings | Intersection, Interval Intersections, **Backspace String Compare (844)** ✅ |
| Multiple Ptrs   | Partitioning arrays        | Sort Colors, Partition Array                                               |
| Sliding Window  | Window problems            | Min Subarray Sum, Min Window Substring                                     |

---

👉 Now Backspace String Compare is officially added under **Parallel Arrays (Two Sequences)** ✅

Want me to also make a **mini-decision tree flowchart** (like: "Is it sorted? → Opposite Ends. Is it two sequences? → Parallel Arrays...") so you can instantly classify any problem?
