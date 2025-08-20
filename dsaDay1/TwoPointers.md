1. What is Two Pointers?

👉 Technique where we use two indices (left and right) to traverse an array/string, instead of brute-forcing all pairs.
👉 Often reduces O(n²) → O(n).

When to use it?

Input is sorted or needs ordering logic.

Need to find pairs/triplets/subarrays with certain properties.

Problems with reversals, palindromes, merging, partitioning.

2. Key Templates
(a) Opposite Ends
int left = 0, right = n-1;
while(left < right) {
    if(nums[left] + nums[right] == target) return true;
    else if(nums[left] + nums[right] < target) left++;
    else right--;
}

(b) Same Direction (Fast-Slow)
int slow = 0, fast = 0;
while(fast < n) {
    // expand window with fast
    // shrink or check with slow
    fast++;
}