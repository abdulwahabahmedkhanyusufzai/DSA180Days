🧩 Two Pointers Master Cheatsheet
1️⃣ Opposite Ends (Collision Pointers)

Definition:
Two pointers start at opposite ends (left=0, right=n-1) and move inward based on conditions.

Recognition:

Input is sorted or must be sorted first.

Problem asks about pairs/triplets that satisfy a condition.

Palindrome check (compare from both ends).

Code Template:

int left = 0, right = n-1;
while (left < right) {
    if (nums[left] + nums[right] == target) return true;
    else if (nums[left] + nums[right] < target) left++;
    else right--;
}


Example Problems:

167. Two Sum II (sorted array)

Valid Palindrome

Container With Most Water

2️⃣ Same Direction (Fast–Slow Pointers)

Definition:
Both pointers move forward; fast expands, slow adjusts or shrinks. Often used as a sliding window.

Recognition:

Problem mentions subarrays / substrings with constraints.

Need to track longest/shortest window.

In-place filtering like “remove duplicates” or “move zeros.”

Code Template:

int slow = 0;
for (int fast = 0; fast < n; fast++) {
    // expand window with fast
    // condition? adjust with slow
}


Example Problems:

3. Longest Substring Without Repeating Characters

Remove Duplicates from Sorted Array

Move Zeroes

3️⃣ Merging Style

Definition:
Merge two sorted arrays/lists using pointers. Often done from the end to avoid overwriting.

Recognition:

Given two sorted inputs, need to combine.

Target array has extra space at the end.

Code Template:

int i = m - 1, j = n - 1, k = m + n - 1;
while (i >= 0 && j >= 0) {
    if (nums1[i] > nums2[j]) nums1[k--] = nums1[i--];
    else nums1[k--] = nums2[j--];
}
while (j >= 0) nums1[k--] = nums2[j--];


Example Problems:

88. Merge Sorted Array

Merge Two Sorted Lists

4️⃣ Fast & Slow (Cycle Detection)

Definition:
Move one pointer slowly, the other faster. If they meet → cycle exists.

Recognition:

Linked list or graph cycle detection.

“Find cycle length” or “find start of cycle.”

Code Template:

ListNode* slow = head;
ListNode* fast = head;
while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) return true;
}
return false;


Example Problems:

141. Linked List Cycle

Linked List Cycle II

5️⃣ Parallel Arrays (Two Sequences)

Definition:
Traverse two arrays simultaneously with two pointers.

Recognition:

“Find intersection of two arrays/lists.”

“Merge intervals.”

Both arrays are sorted.

Code Template:

int i = 0, j = 0;
while (i < n && j < m) {
    if (nums1[i] == nums2[j]) { /* handle */ i++; j++; }
    else if (nums1[i] < nums2[j]) i++;
    else j++;
}


Example Problems:

350. Intersection of Two Arrays II

Interval List Intersections

6️⃣ Multiple Pointers (3+)

Definition:
Use three or more pointers to partition into regions.

Recognition:

Sorting with categories (e.g. 0s,1s,2s).

Multi-partition problems.

Code Template (Dutch National Flag):

int low = 0, mid = 0, high = n-1;
while (mid <= high) {
    if (nums[mid] == 0) swap(nums[low++], nums[mid++]);
    else if (nums[mid] == 1) mid++;
    else swap(nums[mid], nums[high--]);
}


Example Problems:

75. Sort Colors

Partition Array

7️⃣ Sliding Window (Start–End)

Definition:
A moving window bounded by start and end pointers.

Recognition:

Problem involves subarray / substring lengths or sums.

“Find longest substring with condition…”

“Smallest subarray with sum ≥ X.”

Code Template:

int start = 0;
for (int end = 0; end < n; end++) {
    // include nums[end]
    while (window_invalid) {
        // shrink from start
        start++;
    }
    // update answer
}


Example Problems:

209. Minimum Size Subarray Sum

Minimum Window Substring

Fruit Into Baskets

✅ Final Recap
Variant	Recognition Cue	Example Problems
Opposite Ends	Sorted + pairs/triplets	Two Sum II, Palindrome, Container With Most Water
Same Direction	Subarrays / in-place ops	Longest Substring, Remove Duplicates, Move Zeroes
Merging Style	Two sorted arrays/lists	Merge Sorted Array, Merge Lists
Fast & Slow (Cycle)	Linked list cycles	Linked List Cycle I & II
Parallel Arrays	Compare two arrays	Intersection, Interval List Intersections
Multiple Pointers	Partitioning arrays	Sort Colors, Partition Array
Sliding Window	Window problems	Min Subarray Sum, Min Window Substring

👉 If you practice ~3 problems for each variant, you’ll master 95% of all two-pointer interview questions.

Absolutely! Let's build a comprehensive roadmap to master the **Two Pointers** technique, with a structured approach that includes:

* **Variants**: Different patterns within the Two Pointers technique.
* **Difficulty Levels**: Easy, Medium, and Hard problems for each variant.
* **LeetCode Problem Links**: Direct links to each problem for easy access.([LeetCode][1])

---

## 🧩 Two Pointers Mastery Roadmap

### 1️⃣ **Opposite Ends (Collision Pointers)**

**Concept**: Two pointers start at opposite ends and move towards each other based on a condition.

**Easy**:

* [Two Sum II - Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/)
* [Valid Palindrome](https://leetcode.com/problems/valid-palindrome/)
* [Squares of a Sorted Array](https://leetcode.com/problems/squares-of-a-sorted-array/)([LeetCode][2])

**Medium**:

* [Container With Most Water](https://leetcode.com/problems/container-with-most-water/)
* [3Sum](https://leetcode.com/problems/3sum/)
* [4Sum](https://leetcode.com/problems/4sum/)

**Hard**:

* [Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)
* [Trapping Rain Water II](https://leetcode.com/problems/trapping-rain-water-ii/)
* [Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)

---

### 2️⃣ **Same Direction (Fast–Slow Pointers / Sliding Window)**

**Concept**: Both pointers move forward; fast expands, slow adjusts or shrinks.

**Easy**:

* [Remove Duplicates from Sorted Array](https://leetcode.com/problems/remove-duplicates-from-sorted-array/)
* [Move Zeroes](https://leetcode.com/problems/move-zeroes/)
* [Valid Anagram](https://leetcode.com/problems/valid-anagram/)

**Medium**:

* [Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)
* [Substring with Concatenation of All Words](https://leetcode.com/problems/substring-with-concatenation-of-all-words/)
* [Permutation in String](https://leetcode.com/problems/permutation-in-string/)([LeetCode][3])

**Hard**:

* [Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/)
* [Longest Substring with At Most K Distinct Characters](https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/)
* [Substring with Largest Variance](https://leetcode.com/problems/substring-with-largest-variance/)

---

### 3️⃣ **Merging Style**

**Concept**: Merge two sorted arrays/lists using pointers. Often done from the end.([LeetCode][3])

**Easy**:

* [Merge Sorted Array](https://leetcode.com/problems/merge-sorted-array/)
* [Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/)
* [Intersection of Two Arrays II](https://leetcode.com/problems/intersection-of-two-arrays-ii/)

**Medium**:

* [Merge Intervals](https://leetcode.com/problems/merge-intervals/)
* [Insert Interval](https://leetcode.com/problems/insert-interval/)
* [Find the Distance Value Between Two Arrays](https://leetcode.com/problems/find-the-distance-value-between-two-arrays/)([LeetCode][1])

**Hard**:

* [Trapping Rain Water II](https://leetcode.com/problems/trapping-rain-water-ii/)
* [Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)
* [Maximal Rectangle](https://leetcode.com/problems/maximal-rectangle/)

---

### 4️⃣ **Fast & Slow (Cycle Detection / Middle Finder)**

**Concept**: Move one pointer slowly, the other faster. If they meet → cycle exists.

**Easy**:

* [Linked List Cycle](https://leetcode.com/problems/linked-list-cycle/)
* [Middle of the Linked List](https://leetcode.com/problems/middle-of-the-linked-list/)
* [Happy Number](https://leetcode.com/problems/happy-number/)([LeetCode][3])

**Medium**:

* [Linked List Cycle II](https://leetcode.com/problems/linked-list-cycle-ii/)
* [Remove Nth Node From End of List](https://leetcode.com/problems/remove-nth-node-from-end-of-list/)
* [Reorder List](https://leetcode.com/problems/reorder-list/)([LeetCode][1])

**Hard**:

* [Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/)
* [Circular Array Loop](https://leetcode.com/problems/circular-array-loop/)
* [Linked List Random Node](https://leetcode.com/problems/linked-list-random-node/)([LeetCode][1])

---

### 5️⃣ **Parallel Arrays / Two Sequences**

**Concept**: Traverse two arrays simultaneously with two pointers.

**Easy**:

* [Intersection of Two Arrays II](https://leetcode.com/problems/intersection-of-two-arrays-ii/)
* [Find Common Characters](https://leetcode.com/problems/find-common-characters/)
* [Merge Sorted Array](https://leetcode.com/problems/merge-sorted-array/)

**Medium**:

* [Interval List Intersections](https://leetcode.com/problems/interval-list-intersections/)
* [Find the Distance Value Between Two Arrays](https://leetcode.com/problems/find-the-distance-value-between-two-arrays/)
* [Find K-th Smallest Pair Distance](https://leetcode.com/problems/find-k-th-smallest-pair-distance/)([LeetCode][1])

**Hard**:

* [Trapping Rain Water II](https://leetcode.com/problems/trapping-rain-water-ii/)
* [Maximal Rectangle](https://leetcode.com/problems/maximal-rectangle/)
* [Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)

---

### 6️⃣ **Multiple Pointers (3+ / Partitioning)**

**Concept**: Use three or more pointers to partition array into regions.

**Easy**:

* [Sort Colors](https://leetcode.com/problems/sort-colors/)
* [Move Zeroes](https://leetcode.com/problems/move-zeroes/)
* [Reverse String](https://leetcode.com/problems/reverse-string/)

**Medium**:

* [Partition Labels](https://leetcode.com/problems/partition-labels/)
* [Remove Duplicates from Sorted Array II](https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/)
* [Reorder List](https://leetcode.com/problems/reorder-list/)([LeetCode][3])

**Hard**:

* [Maximal Rectangle](https://leetcode.com/problems/maximal-rectangle/)
* [Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)
* [Trapping Rain Water II](https://leetcode.com/problems/trapping-rain-water-ii/)

---

### 7️⃣ **Sliding Window (Start–End)**

**Concept**: A moving window bounded by start and end pointers.

**Easy**:

* [Valid Palindrome](https://leetcode.com/problems/valid-palindrome/)
* [Reverse String](https://leetcode.com/problems/reverse-string/)
* [Palindrome Linked List](https://leetcode.com/problems/palindrome-linked-list/)([LeetCode][1])

**Medium**:

* [Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)
* [Substring with Concatenation of All Words](https://leetcode.com/problems/substring-with-concatenation-of-all-words/)
* [Permutation in String](https://leetcode.com/problems/permutation-in-string/)([LeetCode][3])

**Hard**:

* [Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/)
* [Longest Substring with At Most K Distinct Characters](https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/)
* [Substring with Largest Variance](https://leetcode.com/problems/substring-with-largest-variance/)

---

## ✅ Final Recap Table

| Variant       | Recognition Cue         | Example Problems                                                                                                                                                    |
| ------------- | ----------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Opposite Ends | Sorted + pairs/triplets | [Two Sum II](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/), [Palindrome](https://leetcode.com/problems/valid-palindrome/), \[Container With Most |

[1]: https://leetcode.com/discuss/post/1688903/Solved-all-two-pointers-problems-in-100-days/?utm_source=chatgpt.com "Solved all two pointers problems in 100 days. - Discuss"
[2]: https://leetcode.com/discuss/post/1688903/solved-all-two-pointers-problems-in-100-z56cn/?utm_source=chatgpt.com "Solved all two pointers problems in 100 days. - Discuss - LeetCode"
[3]: https://leetcode.com/discuss/interview-question/4632259/Leetcode-most-liked-questions-101-200?utm_source=chatgpt.com "Leetcode most liked questions 101 - 200 - Discuss"
