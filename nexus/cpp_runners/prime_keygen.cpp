/*
 * RUNNER: prime_keygen
 * SOURCE: 02_Math_and_Numbers/Primes/primeNumber.cpp  (included below)
 *
 * Repurposes the prime-checking algorithm for API key generation.
 * Given a seed number, finds the next N prime numbers above it.
 * These primes are used to build cryptographic API key material.
 *
 * Protocol (stdin):
 *   <seed> <count>
 *   e.g.  1000 8
 * Output (stdout JSON):
 *   {"ok":true,"primes":[1009,1013,1019,1021,1031,1033,1039,1049],"seed":1000}
 */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// ── The original primeNumber.cpp has main(); extract just the logic ──────────
// We replicate the O(sqrt(n)) primality test exactly as written in the source:
//   for(int i=2; i*i<=n; i++) { if(n % i == 0){ isPrime=false; break; } }
// This IS the code from 02_Math_and_Numbers/Primes/primeNumber.cpp.
// ─────────────────────────────────────────────────────────────────────────────

bool isPrime_fromFolder02(int n) {
    // EXACT algorithm from 02_Math_and_Numbers/Primes/primeNumber.cpp
    if (n <= 1) return false;
    bool isPrime = true;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            isPrime = false;
            break;
        }
    }
    return isPrime;
}

int main() {
    int seed, count;
    if (!(cin >> seed >> count)) {
        cout << "{\"ok\":false,\"error\":\"bad input\"}\n";
        return 1;
    }

    vector<int> primes;
    int candidate = max(seed + 1, 2);
    while ((int)primes.size() < count) {
        if (isPrime_fromFolder02(candidate))
            primes.push_back(candidate);
        candidate++;
    }

    // Output JSON
    cout << "{\"ok\":true,\"seed\":" << seed << ",\"primes\":[";
    for (int i = 0; i < (int)primes.size(); i++) {
        if (i) cout << ",";
        cout << primes[i];
    }
    cout << "]}\n";
    return 0;
}
