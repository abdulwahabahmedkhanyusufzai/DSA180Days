#include <string>

class Solution {
public:
  std::string decodeCiphertext(std::string encodedText, int rows) {
    int n = encodedText.length();
    int cols = n / rows;
    std::string res = "";

    // Pre-allocate memory to avoid multiple reallocations
    res.reserve(n);

    for (int start_col = 0; start_col < cols; ++start_col) {
      int r = 0;
      int c = start_col;

      while (r < rows && c < cols) {
        res += encodedText[r * cols + c];
        r++;
        c++;
      }
    }

    // Remove trailing spaces
    while (!res.empty() && res.back() == ' ') {
      res.pop_back();
    }

    return res;
  }
};