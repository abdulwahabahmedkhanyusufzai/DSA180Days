
class Solution {
public:
  int maxArea(vector<int> &height) {
    int n = height.size();
    int maxArea = 0;
    int left = 0, right = n - 1;
    while (left < right) {
      int width = right - left;
      int height = min(height[left], height[right]);
      int currentArea = width * height;
      maxArea = max(maxArea, currentArea);

      if (height[left] < height[right]) {
        left++;
      } else {
        right--;
      }
    }
    return maxArea;
  }
};