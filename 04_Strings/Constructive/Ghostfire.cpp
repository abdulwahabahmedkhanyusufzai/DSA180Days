#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void solve() {
    int r, g, b;
    cin >> r >> g >> b;

    // Sort the available counts descending alongside their character label
    vector<pair<int, char>> counts = {
        {r, 'R'},
        {g, 'G'},
        {b, 'B'}
    };
    sort(counts.rbegin(), counts.rend());

    int cA = counts[0].first;  char A = counts[0].second;
    int cB = counts[1].first;  char B = counts[1].second;
    int cC = counts[2].first;  char C = counts[2].second;

    string ans;
    ans.reserve(r + g + b);

    // Case 1: One color is dominant
    if (cA >= cB + cC - 1) {
        int k = cB + cC;
        int useA = min(cA, k + 1);
        vector<char> others;
        for (int i = 0; i < cB; ++i) others.push_back(B);
        for (int i = 0; i < cC; ++i) others.push_back(C);

        if (useA == k + 1) {
            for (int i = 0; i < k; ++i) {
                ans += A;
                ans += others[i];
            }
            ans += A;
        } else if (useA == k) {
            for (int i = 0; i < k; ++i) {
                ans += A;
                ans += others[i];
            }
        } else if (useA == k - 1) {
            for (int i = 0; i < k - 1; ++i) {
                ans += others[i];
                ans += A;
            }
            if (k > 0) ans += others[k - 1];
        }
    } 
    // Case 2: Colors are balanced (Guaranteed to use all characters)
    else {
        int x = (cA + cB - cC) / 2;
        int y = (cB + cC - cA) / 2;
        int z = (cA + cC - cB) / 2;

        // Block 1: Alternating A and B
        for (int i = 0; i < x; ++i) {
            ans += A;
            ans += B;
        }
        // Block 2: Alternating C and B
        for (int i = 0; i < y; ++i) {
            ans += C;
            ans += B;
        }
        // Block 3: Alternating C and A
        for (int i = 0; i < z; ++i) {
            ans += C;
            ans += A;
        }

        // If the total sum is odd, one extra of each character remains 
        // to be beautifully glued at the end safely.
        if ((cA + cB + cC) % 2 != 0) {
            ans += C;
            ans += A;
            ans += B;
        }
    }

    cout << ans << "\n";
}

int main() {
    // Fast I/O for speed optimization
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
