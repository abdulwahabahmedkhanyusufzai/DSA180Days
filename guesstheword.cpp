class Solution {
    int getMatches(const string& s1, const string& s2) {
        int matches = 0;
        for (int i = 0; i < 6; i++) {
            if (s1[i] == s2[i]) matches++;
        }
        return matches;
    }

public:
    void findSecretWord(vector<string>& words, Master& master) {
        for (int i = 0; i < 30; i++) {
            // Minimax: Find the word that minimizes the max possible group size
            string best_word = "";
            int min_max_group = 101; 

            for (const string& w1 : words) {
                vector<int> count(7, 0);
                for (const string& w2 : words) {
                    if (w1 != w2) {
                        count[getMatches(w1, w2)]++;
                    }
                }
                
                // Find the largest group this word could leave us with
                int max_group = 0;
                for (int c : count) max_group = max(max_group, c);
                
                if (max_group < min_max_group) {
                    min_max_group = max_group;
                    best_word = w1;
                }
            }

            int matches = master.guess(best_word);
            if (matches == 6) return;

            // Filter candidates
            vector<string> next_candidates;
            for (const string& w : words) {
                if (getMatches(best_word, w) == matches) {
                    next_candidates.push_back(w);
                }
            }
            words = next_candidates;
        }
    }
};
