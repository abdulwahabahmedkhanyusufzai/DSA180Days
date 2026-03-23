1) Read the problem for cues

Typical phrasing:

“Array is sorted.”

“Do it in-place.”

“Use O(1) extra space.”

“Return the new length; keep first part of array as the result.”

These four together scream: scan once and compact in place → that’s the fast–slow pattern.

2) Why fast–slow fits perfectly

Goal: keep one copy of each distinct value and overwrite duplicates in-place.

Because the array is sorted, all duplicates appear contiguously.

We can keep:

slow = index of the last unique element we’ve written,

fast = index we’re reading/scanning.

When nums[fast] != nums[slow], we’ve discovered a new unique value. Move slow++ and copy it: nums[slow] = nums[fast].

Invariant:
At any time, elements in nums[0..slow] are the unique elements seen so far (in order).
We never need extra memory, just overwrite duplicates as we go.

3) Why not other two-pointer variants?

Opposite Ends (collision): used when comparisons are monotonic (e.g., sum < target then move left++) or for symmetric checks (palindrome, container water). Here, equality isn’t monotonic from ends; meeting in the middle doesn’t help compaction.

Sliding Window (start–end): used for “longest/shortest subarray with condition” or sum/constraint windows. We’re not optimizing a window; we’re filtering and compacting.

Merging Style: for two sorted inputs. We have one array.

Fast & Slow (cycle detection): for linked lists/graphs to detect cycles—not relevant.

Parallel Arrays: again needs two sequences.

Multiple Pointers / Dutch Flag: for categorical partitioning (0/1/2). Our “categories” are arbitrary values; we only need unique compaction.

So the only natural fit is Same-Direction (fast–slow) filtering.

4) The template (what your code does)
int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;

    int slow = 0;                  // last unique write position
    for (int fast = 1; fast < nums.size(); fast++) {
        if (nums[fast] != nums[slow]) {
            slow++;                // open next write slot
            nums[slow] = nums[fast];
        }
    }
    return slow + 1;               // count = last index + 1
}

5) Tiny dry run (why it works)

nums = [1,1,2,2,3]

fast	nums[fast]	slow	nums[slow]	action	array after
1	1	0	1	equal → skip	[1,1,2,2,3]
2	2	0	1	new → slow=1, write 2	[1,2,2,2,3]
3	2	1	2	equal → skip	[1,2,2,2,3]
4	3	1	2	new → slow=2, write 3	[1,2,3,2,3]

Return slow+1 = 3. First 3 are [1,2,3].

6) Complexity & constraints

Time: O(n) single pass.

Space: O(1) in-place.

Requires sorted input (or you must sort first, which is O(n log n)).
If the array is unsorted and you must preserve order, two pointers won’t solve uniqueness without extra space; you’d use a hash set instead.

7) Common mistakes to avoid

Not handling empty array.

Returning slow instead of slow+1.

Starting fast at 0 (should start at 1 since slow=0 already holds first unique).

Trying to use nested loops (O(n²))—unnecessary given sorting.

8) How to spot close variations quickly

“Keep at most two duplicates” (LC 80): same pattern, tweak the check: write when fast < 2 || nums[fast] != nums[slow-1].

Remove a given value (LC 27): same compaction but predicate is nums[fast] != val.

Move Zeroes (LC 283): same idea; treat “non-zero” as the items to keep at the front.

TL;DR decision rule:
If the array is sorted, the task is in-place filtering/compaction with O(1) extra space, pick Same-Direction (fast–slow) two pointers.