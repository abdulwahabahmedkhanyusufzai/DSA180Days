#include <vector>
#include <string>

using namespace std;

class TrieNode {
public:
    // 'a' through 'z' is 26 characters. '{' is exactly one ASCII character after 'z'.
    // Therefore, an array of size 27 Perfectly fits 'a'-'z' and '{'.
    TrieNode* children[27]; 
    int weight;
    
    TrieNode() : weight(0) {
        for (int i = 0; i < 27; ++i) {
            children[i] = nullptr;
        }
    }
};

class WordFilter {
private:
    TrieNode* root;

public:
    WordFilter(vector<string>& words) {
        root = new TrieNode();
        
        for (int i = 0; i < words.size(); i++) {
            string word = words[i];
            // Create the wrapped word
            string searchWord = word + "{" + word;
            int n = word.length();
            
            // Insert all suffix substrings of the wrapped word
            for (int j = 0; j <= n; j++) {
                TrieNode* current = root;
                current->weight = i; 
                
                for (int k = j; k < searchWord.length(); k++) {
                    int char_idx = searchWord[k] - 'a';
                    if (!current->children[char_idx]) {
                        current->children[char_idx] = new TrieNode();
                    }
                    current = current->children[char_idx];
                    current->weight = i; // Overwrites with the latest (largest) index
                }
            }
        }
    }
    
    int f(string pref, string suff) {
        TrieNode* current = root;
        string searchQuery = suff + "{" + pref;
        
        for (char c : searchQuery) {
            int char_idx = c - 'a';
            if (!current->children[char_idx]) {
                return -1; // Path doesn't exist
            }
            current = current->children[char_idx];
        }
        
        // Return the highest index recorded at the end of the matching path
        return current->weight;
    }
};
