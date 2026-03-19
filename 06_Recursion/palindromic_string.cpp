class Solution {
public:
    // Helper function to handle indices without copying the string
    bool isPal(string& s, int left, int right) {
        // Base case: If indices meet or cross, we've checked everything
        if (left >= right) {
            return true;
        }

        // Check if outer characters match
        if (s[left] != s[right]) {
            return false;
        }

        // Shrink the window and recurse
        return isPal(s, left + 1, right - 1);
    }

    bool palindromeCheck(string& s) {
        if (s.empty()) return true;
        return isPal(s, 0, s.length() - 1);
    }
};

class Solution {
public:
    bool isPalindrome(string s) {
      int left =0,right=s.length()-1;

      while (left < right) {
    if (!isalnum(s[left])) left++;
    else if (!isalnum(s[right])) right--;
    else {
        if (tolower(s[left]) != tolower(s[right])) return false;
        left++;
        right--;
    }
}       
      return true;
    }
};