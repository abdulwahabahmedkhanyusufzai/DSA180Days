#include <string>
#include <vector>


using namespace std;

class Solution {
private:
  // Helper function to check if 'word' is a subsequence of 's'
  bool isSubsequence(const string &word, const string &s) {
    int i = 0; // Pointer for word
    int j = 0; // Pointer for s

    while (i < word.length() && j < s.length()) {
      if (word[i] == s[j]) {
        i++;
      }
      j++;
    }

    return i == word.length();
  }

public:
  string findLongestWord(string s, vector<string> &dictionary) {
    string best_word = "";

    for (const string &word : dictionary) {
      // Prune: Skip if the word cannot possibly be the new best answer.
      // It must either be longer than best_word, OR the same length but
      // lexicographically smaller.
      if (word.length() < best_word.length() ||
          (word.length() == best_word.length() && word > best_word)) {
        continue;
      }

      // If it qualifies as a better candidate, verify if it's actually a
      // subsequence
      if (isSubsequence(word, s)) {
        best_word = word;
      }
    }

    return best_word;
  }
};