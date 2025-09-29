Got it ✅ — I’ll prepare a **clear explanation document** covering all three solutions (`O(n³)`, `O(n²)`, `O(n)`) for the “remove duplicates from sorted array” problem.

---

# 📘 Remove Duplicates from Sorted Array – Three Approaches

We are solving the problem:
**Given a sorted array `nums`, remove duplicates in-place so that each element appears only once, and return the new length.**

---

## 🔹 1. Brute Force with Triple-Nested Behavior (`O(n³)`)

### Code

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j <= i + 1; j++) {
                if (nums[i] == nums[i + 1]) {
                    nums.erase(nums.begin() + j);
                    j--;
                }
            }
        }
        return nums.size();
    }
};
```

### How it Works

* Outer loop: Iterates through the array.
* Inner loop: Compares elements at positions `i` and `i+1`.
* If duplicate found → `erase` is used to remove the duplicate.

### Problems

* **`erase` is costly**: each call shifts all elements to the left → `O(n)` operation.
* Combined with nested loops, worst case = `O(n³)`.
* Works but is very **slow for large arrays**.

### Complexity

* **Time**: `O(n³)`
* **Space**: `O(1)` (in-place, no extra storage)

---

## 🔹 2. Improved Erase-Based (`O(n²)`)

### Code

```cpp
class Solution2 {
public:
    int removeDuplicates(vector<int>& nums) {
        for (int i = 0; i < nums.size() - 1; i++) {
            if (nums[i] == nums[i + 1]) {
                nums.erase(nums.begin() + (i + 1));
                i--; // step back since array shrinks
            }
        }
        return nums.size();
    }
};
```

### How it Works

* Traverse the array with a single loop.
* If two consecutive elements are equal → remove the duplicate using `erase`.
* Step back (`i--`) to re-check current position after shrinking.

### Improvements

* Removed inner loop → no triple nesting.
* Still uses `erase`, so each duplicate removal costs `O(n)`.
* Overall `O(n²)` in the worst case.

### Complexity

* **Time**: `O(n²)`
* **Space**: `O(1)`

---

## 🔹 3. Optimal Two-Pointer Approach (`O(n)`)

### Code

```cpp
class Solution3 {
public:
    int removeDuplicates(vector<int>& nums) {
        int j = 0; // write pointer
        for (int i = 1; i < nums.size(); i++) { // read pointer
            if (nums[i] != nums[j]) {  // found a unique element
                j++;
                nums[j] = nums[i];     // place it in correct position
            }
        }
        return j + 1; // number of unique elements
    }
};
```

### How it Works

* Use **two pointers**:

  * `i` = read pointer (scans every element).
  * `j` = write pointer (tracks last unique element).
* If `nums[i] != nums[j]`:

  * Move `j` forward,
  * Copy `nums[i]` to position `j`.
* At the end, first `j+1` elements are unique.

### Why This Works

* No shifting of elements like `erase`.
* Each element is visited only once.
* Perfectly fits the problem statement: modify array in-place, no extra memory.

### Example Walkthrough

Input: `{0,0,1,1,1,2,2,3,3,4}`
Output: `{0,1,2,3,4}` (unique part)

---

### Complexity

* **Time**: `O(n)`
* **Space**: `O(1)`

---

## 📊 Comparison Table

| Solution   | Method                | Time Complexity | Space Complexity | Efficient?               |
| ---------- | --------------------- | --------------- | ---------------- | ------------------------ |
| Solution 1 | Nested loops + erase  | `O(n³)`         | `O(1)`           | ❌ Very slow              |
| Solution 2 | Single loop + erase   | `O(n²)`         | `O(1)`           | ⚠️ Better but still slow |
| Solution 3 | Two-pointer overwrite | `O(n)`          | `O(1)`           | ✅ Optimal                |

---

✅ **Conclusion**:

* Use **Solution 3 (two pointers)** for real problems.
* Solutions 1 and 2 are good for **learning** why `erase` causes inefficiency.

---

Do you want me to also **add diagrams (pointer movement)** for Solution 3 in this document, so it looks like a study guide?
