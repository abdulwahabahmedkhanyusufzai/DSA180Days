/*
 * RUNNER: trie_router
 * SOURCE: 10_Trees/  (Trie/prefix-tree concept — mirrors BinaryTreePaths traversal)
 *         04_Strings/PrefixandSuffixSearch.cpp
 *
 * Semantic Intent Router: Trie-based keyword matching that routes prompts
 * to the correct AI agent. Prefix matching mirrors PrefixandSuffixSearch.cpp.
 *
 * Protocol (stdin):
 *   First, INSERT lines:  INSERT <keyword> <agent_type>
 *   Then,  ROUTE lines:   ROUTE <prompt_text_first_word>
 *   END to stop.
 *
 * Output per ROUTE:
 *   {"ok":true,"keyword":"extract","agent":"data_extractor","confidence":1.0}
 *   {"ok":true,"keyword":null,"agent":"default","confidence":0.0}
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <sstream>
using namespace std;

// ── Trie Node (10_Trees prefix-tree structure) ────────────────────────────────
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool is_end = false;
    string agent_type;

    ~TrieNode() {
        for (auto& [c, child] : children) delete child;
    }
};

class Trie {
    TrieNode* root;
public:
    Trie() : root(new TrieNode()) {}
    ~Trie() { delete root; }

    // Insert keyword → agent mapping (10_Trees insertion)
    void insert(const string& word, const string& agent) {
        TrieNode* node = root;
        for (char c : word) {
            c = tolower(c);
            if (!node->children.count(c))
                node->children[c] = new TrieNode();
            node = node->children[c];
        }
        node->is_end = true;
        node->agent_type = agent;
    }

    // Longest prefix match — mirrors PrefixandSuffixSearch.cpp style
    pair<string,string> longestPrefixMatch(const string& query) {
        TrieNode* node = root;
        string matched;
        string last_agent;
        string current;
        for (char ch : query) {
            char c = tolower(ch);
            if (!node->children.count(c)) break;
            node = node->children[c];
            current += c;
            if (node->is_end) {
                matched = current;
                last_agent = node->agent_type;
            }
        }
        return {matched, last_agent};
    }
};

string escapeJson(const string& s) {
    string out;
    for (char c : s) {
        if (c == '"') out += "\\\"";
        else out += c;
    }
    return out;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Trie trie;
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        if (line == "END") break;

        istringstream ss(line);
        string cmd;
        ss >> cmd;

        if (cmd == "INSERT") {
            string keyword, agent;
            ss >> keyword >> agent;
            trie.insert(keyword, agent);
            cout << "{\"ok\":true,\"op\":\"INSERT\",\"keyword\":\""
                 << escapeJson(keyword) << "\",\"agent\":\""
                 << escapeJson(agent) << "\"}\n";

        } else if (cmd == "ROUTE") {
            string prompt;
            ss >> prompt;
            auto [kw, agent] = trie.longestPrefixMatch(prompt);

            if (kw.empty()) {
                cout << "{\"ok\":true,\"op\":\"ROUTE\",\"keyword\":null"
                     << ",\"agent\":\"default\",\"confidence\":0.0"
                     << ",\"prompt\":\"" << escapeJson(prompt) << "\"}\n";
            } else {
                cout << "{\"ok\":true,\"op\":\"ROUTE\""
                     << ",\"keyword\":\"" << escapeJson(kw) << "\""
                     << ",\"agent\":\"" << escapeJson(agent) << "\""
                     << ",\"confidence\":1.0"
                     << ",\"prompt\":\"" << escapeJson(prompt) << "\"}\n";
            }
        }
    }
    return 0;
}
