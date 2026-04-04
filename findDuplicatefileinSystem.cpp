#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

class Solution {
public:
    vector<vector<string>> findDuplicate(vector<string>& paths) {
        unordered_map<string, vector<string>> content_map;
        vector<vector<string>> result;

        for (const string& path_info : paths) {
            stringstream ss(path_info);
            string directory;
            string file_info;
            
            // The first token is always the directory path
            getline(ss, directory, ' ');
            
            // The remaining tokens are files in the format: filename.txt(content)
            while (getline(ss, file_info, ' ')) {
                int open_paren = file_info.find('(');
                int close_paren = file_info.find(')');
                
                string filename = file_info.substr(0, open_paren);
                string content = file_info.substr(open_paren + 1, close_paren - open_paren - 1);
                
                // Map the content to its full file path
                content_map[content].push_back(directory + "/" + filename);
            }
        }

        // Collect all groups that have more than one file
        for (const auto& pair : content_map) {
            if (pair.second.size() > 1) {
                result.push_back(pair.second);
            }
        }

        return result;
    }
};
