Perfect 🔥 You want a **complete encyclopedia of bit manipulation** — from **basic concepts, built-in operators, all tricks, and advanced interview-level hacks**. I’ll make sure **NOTHING is left out**.

---

# ⚡ Bit Manipulation – Complete Guide (Beginner → Very Advanced)

---

## 🟢 1. Bitwise Operators (Built-in)

In **C++ / Java / Python / JavaScript** (all support these operators):

| Operator | Meaning                        | Example       | Effect                |        |                     |
| -------- | ------------------------------ | ------------- | --------------------- | ------ | ------------------- |
| `&`      | AND                            | `5 & 3 = 1`   | Bit set if both are 1 |        |                     |
| `        | `                              | OR            | `5                    | 3 = 7` | Bit set if any is 1 |
| `^`      | XOR                            | `5 ^ 3 = 6`   | Bit set if different  |        |                     |
| `~`      | NOT                            | `~5 = -6`     | Flip all bits         |        |                     |
| `<<`     | Left Shift                     | `5 << 1 = 10` | Multiply by 2         |        |                     |
| `>>`     | Right Shift                    | `5 >> 1 = 2`  | Divide by 2 (signed)  |        |                     |
| `>>>`    | Unsigned Right Shift (Java/JS) | `-5 >>> 1`    | Logical shift right   |        |                     |

⚡ **Properties of XOR**:

* `a ^ a = 0`
* `a ^ 0 = a`
* `a ^ b ^ a = b`

---

## 🟡 2. Basic Bit Tricks

### 2.1 Get i-th bit

```cpp
(n >> i) & 1
```

### 2.2 Set i-th bit

```cpp
n | (1 << i)
```

### 2.3 Clear i-th bit

```cpp
n & ~(1 << i)
```

### 2.4 Toggle i-th bit

```cpp
n ^ (1 << i)
```

### 2.5 Update i-th bit

```cpp
n = (n & ~(1 << i)) | (v << i); // set ith bit to v (0 or 1)
```

---

## 🟠 3. Built-in Functions (C++/Java/Python)

### C++ (GCC/Clang)

```cpp
__builtin_popcount(x);      // count set bits (int)
__builtin_popcountll(x);    // count set bits (long long)
__builtin_clz(x);           // count leading zeros
__builtin_ctz(x);           // count trailing zeros
__builtin_parity(x);        // parity (odd/even count of bits)
```

### Java

```java
Integer.bitCount(x);         // count set bits
Integer.numberOfLeadingZeros(x);
Integer.numberOfTrailingZeros(x);
Integer.highestOneBit(x);    // MSB
Integer.lowestOneBit(x);     // RSB
```

### Python

```python
bin(x).count("1")          # count set bits
(x).bit_length()           # position of MSB + 1
```

---

## 🔵 4. Intermediate Tricks

### 4.1 Odd/Even Check

```cpp
if (n & 1) cout << "Odd"; else cout << "Even";
```

### 4.2 Swap without temp

```cpp
a ^= b; b ^= a; a ^= b;
```

### 4.3 Count set bits (Brian Kernighan)

```cpp
while(n) { n &= (n-1); count++; }
```

### 4.4 Check power of 2

```cpp
n > 0 && (n & (n-1)) == 0;
```

### 4.5 Find Rightmost Set Bit

```cpp
n & -n
```

### 4.6 Remove Rightmost Set Bit

```cpp
n & (n-1)
```

### 4.7 Find MSB Position

```cpp
31 - __builtin_clz(n)
```

### 4.8 Reverse Bits

```cpp
unsigned int rev=0;
for(int i=0;i<32;i++) { rev<<=1; rev|=(n>>i)&1; }
```

### 4.9 Range AND [L, R]

```cpp
int shift=0;
while(L<R){ L>>=1; R>>=1; shift++; }
return L<<shift;
```

---

## 🔴 5. Advanced XOR Tricks

### 5.1 Find unique number (others appear twice)

```cpp
int ans=0;
for(int x: arr) ans^=x;
```

### 5.2 Find two uniques

```cpp
int xorsum=0; for(int x: arr) xorsum^=x;
int rsb = xorsum & -xorsum;
int a=0,b=0;
for(int x: arr){ if(x&rsb) a^=x; else b^=x; }
```

### 5.3 Find unique (others appear thrice)

```cpp
int ones=0, twos=0;
for(int x: arr){
    ones=(ones^x)&~twos;
    twos=(twos^x)&~ones;
}
```

### 5.4 XOR from 1..n

```cpp
if(n%4==0) return n;
if(n%4==1) return 1;
if(n%4==2) return n+1;
return 0;
```

### 5.5 XOR range [L..R]

```cpp
xor(0..R) ^ xor(0..L-1)
```

---

## 🟣 6. Subset & DP Tricks

### 6.1 Generate all subsets

```cpp
for(int mask=0; mask<(1<<n); mask++){
    for(int i=0;i<n;i++)
        if(mask & (1<<i)) cout<<arr[i]<<" ";
    cout<<endl;
}
```

### 6.2 SOS DP (Sum Over Subsets DP)

* Used in problems like “sum over all subsets”.
* Precompute dp[mask] for all subsets efficiently.

### 6.3 Travelling Salesman Problem (TSP)

* Use `dp[mask][i]` = min cost to visit subset `mask` ending at `i`.

---

## 🟤 7. Math with Bits

### 7.1 Fast Exponentiation

```cpp
long long res=1;
while(b){ if(b&1) res*=a; a*=a; b>>=1; }
```

### 7.2 Multiply/Divide by 2

```cpp
n << 1;   // *2
n >> 1;   // /2
```

### 7.3 Gray Code

```cpp
int gray = n ^ (n>>1);
```

### 7.4 Next Higher Number with Same Set Bits

```cpp
int c=n&-n;
int r=n+c;
return (((r^n)>>2)/c)|r;
```

---

## ⚫ 8. Super Advanced Tricks (MAANG-Level)

* **Binary Trie (Bitwise Trie)** → find max XOR pair in array.
* **Bitmask optimization** for **DP states**.
* **Fast Walsh–Hadamard Transform (FWHT)** → XOR convolution.
* **Bitboard tricks** → Chess programming, move generation.
* **Bitset in C++ STL** → store boolean arrays efficiently.
* **Parallel bit tricks** (divide integers into bit fields).
* **Population count hacks** → using masks & multiplications.

---

# 🚀 Roadmap for Mastery

1. **Basics** → get/set/clear/toggle, shifts, odd/even.
2. **Intermediate** → Kernighan’s algo, MSB, RSB, XOR range.
3. **Advanced** → Unique element problems, fast exponentiation, subset generation.
4. **Expert** → Bitmask DP, Gray code, tries, FWHT, SOS DP.

---

👉 This now includes:

* All **built-in operators**
* All **built-in functions**
* All **classic tricks**
* All **advanced hacks**

---

Do you want me to now build a **curated problem set (Easy → Hard)** from **LeetCode / Codeforces / HackerRank** so you can **practice each trick step-by-step**?
