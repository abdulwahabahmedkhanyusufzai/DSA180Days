You are given two integer arrays nums1 and nums2, sorted in non-decreasing order, and two integers m and n, representing the number of elements in nums1 and nums2 respectively.

Merge nums1 and nums2 into a single array sorted in non-decreasing order.

The final sorted array should not be returned by the function, but instead be stored inside the array nums1. To accommodate this, nums1 has a length of m + n, where the first m elements denote the elements that should be merged, and the last n elements are set to 0 and should be ignored. nums2 has a length of n.

   vector<int> newArray;

    for(int i = 0; i < m; i++) {
       newArray.push_back(nums1[i]);
    }
    for(int i=0;i<n;i++){
      newArray.push_back(nums2[i]);
    }
    sort(newArray.begin(),newArray.end());

Example 1:
 1.Nums1 can be lesser than nums2. 
 2.Nums1 can be greater than nums2.
 3.Nums1 can be equal to nums2.

Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
                    i                           j
                if(i<j){
                  push(i)
                }
                [1,2,2,3,5,6]
                1 step   if 1 is less than 2 push 1 
                 2 step  if 1 is less than 5 check if 1 exist so dont push
                 3 step  if 1 is less than 6 check if 1 exist dont push
                 4 step  if 2 is equal to 2 push first two and second 2
                 5 step  if 2 is less than 5 push and if exist dont push
                 6 step if 2 is less than 6 dont and if exist dont push
                 7 step if 3 is greater than 2 push  3
                 8 step if 3 is less than 5 and exist push  5
                 9 step if 3 is less than 6 and if exist push 6

Output: [1,2,2,3,5,6]
 [
Explanation: The arrays we are merging are [1,2,3] and [2,5,6].
The result of the merge is [1,2,2,3,5,6] with the underlined elements coming from nums1.
Example 2:

Input: nums1 = [1], m = 1, nums2 = [], n = 0
Output: [1]
Explanation: The arrays we are merging are [1] and [].
The result of the merge is [1].
Example 3:

Input: nums1 = [0], m = 0, nums2 = [1], n = 1
Output: [1]
Explanation: The arrays we are merging are [] and [1].
The result of the merge is [1].
Note that because m = 0, there are no elements in nums1. The 0 is only there to ensure the merge result can fit in nums1.
 

Constraints:

nums1.length == m + n
nums2.length == n
0 <= m, n <= 200
1 <= m + n <= 200
-109 <= nums1[i], nums2[j] <= 10