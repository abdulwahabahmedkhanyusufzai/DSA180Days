/*
 * RUNNER: rbac_bitmask
 * SOURCE: 08_Bit_Manipulation/Basics/DividetheInteger.cpp  (bit-shift logic)
 *
 * Role-Based Access Control using bitmask operations.
 * The bit-shifting technique from DividetheInteger.cpp (count <<= 1, temp <<= 1)
 * is repurposed to encode/check permission bits.
 *
 * Permission bits:
 *   Bit 0 (1)  = READ
 *   Bit 1 (2)  = WRITE
 *   Bit 2 (4)  = EXECUTE
 *   Bit 3 (8)  = DELETE
 *   Bit 4 (16) = ADMIN
 *
 * Protocol (stdin):
 *   <op> <role_mask> [permission_bit]
 *   Ops: CHECK, GRANT, REVOKE, DESCRIBE
 *
 * Example:
 *   CHECK 7 4    → {"ok":true,"has_permission":true,"role":7,"bit":4}
 *   DESCRIBE 13  → {"ok":true,"permissions":["READ","WRITE","DELETE"]}
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ── Bit-shift pattern from 08_Bit_Manipulation/Basics/DividetheInteger.cpp ──
// Original: while(abs_dividend >= (temp<<1)){ temp<<=1; count<<=1; }
// We reuse the same << operator pattern for permission bit traversal.
// ─────────────────────────────────────────────────────────────────────────────

const int PERM_READ    = 1 << 0;  // 1
const int PERM_WRITE   = 1 << 1;  // 2
const int PERM_EXECUTE = 1 << 2;  // 4
const int PERM_DELETE  = 1 << 3;  // 8
const int PERM_ADMIN   = 1 << 4;  // 16

string permName(int bit) {
    switch(bit) {
        case PERM_READ:    return "READ";
        case PERM_WRITE:   return "WRITE";
        case PERM_EXECUTE: return "EXECUTE";
        case PERM_DELETE:  return "DELETE";
        case PERM_ADMIN:   return "ADMIN";
        default:           return "UNKNOWN";
    }
}

// DividetheInteger.cpp's bit-shift pattern: traverse bits using <<
vector<string> describePermissions(int mask) {
    vector<string> perms;
    int bit = 1;                           // start at bit 0
    while (bit <= PERM_ADMIN) {            // same loop structure as DividetheInteger
        if (mask & bit)                    // bitwise AND check
            perms.push_back(permName(bit));
        bit <<= 1;                         // << 1 shift — exact same as DividetheInteger.cpp
    }
    return perms;
}

int main() {
    string op;
    int role_mask;
    while (cin >> op >> role_mask) {
        if (op == "CHECK") {
            int perm_bit;
            cin >> perm_bit;
            bool has = (role_mask & perm_bit) != 0;
            cout << "{\"ok\":true,\"op\":\"CHECK\",\"role\":" << role_mask
                 << ",\"bit\":" << perm_bit
                 << ",\"has_permission\":" << (has ? "true" : "false") << "}\n";

        } else if (op == "GRANT") {
            int perm_bit;
            cin >> perm_bit;
            int new_mask = role_mask | perm_bit;  // bitwise OR — grant
            cout << "{\"ok\":true,\"op\":\"GRANT\",\"old_mask\":" << role_mask
                 << ",\"new_mask\":" << new_mask
                 << ",\"granted_bit\":" << perm_bit << "}\n";

        } else if (op == "REVOKE") {
            int perm_bit;
            cin >> perm_bit;
            int new_mask = role_mask & ~perm_bit;  // AND NOT — revoke
            cout << "{\"ok\":true,\"op\":\"REVOKE\",\"old_mask\":" << role_mask
                 << ",\"new_mask\":" << new_mask
                 << ",\"revoked_bit\":" << perm_bit << "}\n";

        } else if (op == "DESCRIBE") {
            auto perms = describePermissions(role_mask);
            cout << "{\"ok\":true,\"op\":\"DESCRIBE\",\"mask\":" << role_mask << ",\"permissions\":[";
            for (int i = 0; i < (int)perms.size(); i++) {
                if (i) cout << ",";
                cout << "\"" << perms[i] << "\"";
            }
            cout << "]}\n";
        } else {
            cout << "{\"ok\":false,\"error\":\"unknown op\"}\n";
        }
    }
    return 0;
}
