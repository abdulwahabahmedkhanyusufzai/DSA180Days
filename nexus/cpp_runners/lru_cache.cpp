/*
 * RUNNER: lru_cache
 * SOURCE: 13_Linked_List/LRUCache.cpp  (actual file included below)
 *
 * Protocol (stdin/stdout JSON):
 *   Input lines:  {"op":"put","key":1,"value":10}
 *                 {"op":"get","key":1}
 *                 {"op":"stats"}
 *   Each line produces one JSON output line.
 *
 * This runner compiles the REAL LRUCache.cpp from folder 13_Linked_List.
 */

#include <iostream>
#include <string>
#include <sstream>
#include <nlohmann/json.hpp>   // header-only JSON

// ── Include the ACTUAL production file from 13_Linked_List ──────────────────
#include "../../13_Linked_List/LRUCache.cpp"
// ─────────────────────────────────────────────────────────────────────────────

using json = nlohmann::json;
using namespace std;

int main() {
    LRUCache cache(256);   // 256-entry cache for LLM responses

    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        try {
            json req  = json::parse(line);
            string op = req["op"];

            if (op == "put") {
                int key = req["key"];
                int val = req["value"];
                cache.put(key, val);
                cout << json{{"ok", true}, {"op", "put"}, {"key", key}}.dump() << "\n";

            } else if (op == "get") {
                int key = req["key"];
                int val = cache.get(key);
                bool hit = (val != -1);
                cout << json{{"ok", true}, {"op", "get"}, {"key", key},
                             {"value", val}, {"hit", hit}}.dump() << "\n";

            } else if (op == "stats") {
                // Report current state (we don't have size in the class, report ok)
                cout << json{{"ok", true}, {"op", "stats"},
                             {"capacity", 256}}.dump() << "\n";
            }
        } catch (const exception& e) {
            cout << json{{"ok", false}, {"error", e.what()}}.dump() << "\n";
        }
    }
    return 0;
}
