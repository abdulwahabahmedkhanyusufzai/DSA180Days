class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        // If we don't need to plant any flowers, it's always possible
        if (n == 0) return true;
        
        int size = flowerbed.size();
        
        for (int i = 0; i < size; i++) {
            // Check if current plot is empty
            if (flowerbed[i] == 0) {
                // Check left and right dependencies (boundaries are considered empty)
                bool empty_left = (i == 0) || (flowerbed[i - 1] == 0);
                bool empty_right = (i == size - 1) || (flowerbed[i + 1] == 0);
                
                if (empty_left && empty_right) {
                    flowerbed[i] = 1; // Plant the flower
                    n--;              // Decrement the required flowers
                    
                    if (n == 0) return true; // Early exit if we planted enough
                }
            }
        }
        
        return n <= 0;
    }
};
