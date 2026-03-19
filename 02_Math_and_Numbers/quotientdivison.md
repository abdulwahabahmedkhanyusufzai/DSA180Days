Perfect 🚀 Let’s **deconstruct this solution line by line**, explain every concept deeply, and then I’ll give you **a big set of practice questions** to master all of them.

---

## 🔑 Concepts Used in the Bitwise Division Solution

### 1. **Integer Ranges and Overflow**

* `int` range = `-2,147,483,648` to `2,147,483,647`.
* `INT_MIN` (`-2147483648`) cannot be negated directly → causes **overflow**.
* To avoid this, we **promote** to `long long` before taking absolute values.

👉 Practice:

* Why does `-INT_MIN` overflow in 32-bit?
* Show why `INT_MIN * -1` is undefined.

---

### 2. **Sign Calculation**

```cpp
int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;
```

* `^` = XOR bitwise operator.
* If signs are different → result is negative.
* If same → result is positive.

👉 Practice:

* What does `a ^ b` return when `a=0, b=1`?
* Write code that checks if two numbers have the same sign using XOR.

---

### 3. **Converting to Positive Safely**

```cpp
long long absDividend = dividend;
long long absDivisor = divisor;

if (absDividend < 0) absDividend = -absDividend;
if (absDivisor < 0) absDivisor = -absDivisor;
```

* Store in `long long` to avoid overflow.
* Manually negate negative numbers → avoids unsafe `abs()`.

👉 Practice:

* Implement your own `myAbs(int x)` without using `abs()`.
* Convert `-7` to `+7` using **bit manipulation**.

---

### 4. **Bit Shifting**

```cpp
for (int i = 31; i >= 0; i--) {
    if ((absDividend >> i) >= absDivisor) {
        absDividend -= (absDivisor << i);
        quotient += (1LL << i);
    }
}
```

* **Left Shift `<<`**: `x << i` = multiply by `2^i`.
* **Right Shift `>>`**: `x >> i` = divide by `2^i` (floor).

Example:

* `5 << 2 = 20` (5 * 4).
* `20 >> 2 = 5` (20 / 4).

👉 Practice:

* Compute `13 << 1`, `13 << 2`, `13 >> 1`, `13 >> 2`.
* Why does shifting left by `i` mean multiplying by `2^i`?

---

### 5. **Greedy Subtraction Using Shifts**

* `(absDividend >> i) >= absDivisor` checks if divisor * 2^i fits inside dividend.
* If yes: subtract that amount and add `2^i` to quotient.

👉 Example: `43 ÷ 5`

1. Highest power of 2 where `(5 << i) <= 43` is `i = 3` (`40`).
2. Subtract `40`, quotient += `8`.
3. Left with `3`, which is less than `5`.
4. Final quotient = `8`.

👉 Practice:

* Dry run `27 ÷ 3` with this method.
* Dry run `100 ÷ 7` with this method.

---

### 6. **Constant Time Loop**

* Loop runs **always 32 times** → O(1).
* No inner loop, unlike the previous solution.
* Super efficient.

👉 Practice:

* Why do we only loop 32 times, not `log(dividend)` times?
* What happens if we extend to 64-bit numbers?

---

---

## 📝 Practice Questions to Master These Concepts

### 🔹 Basics (Warm-up)

1. Implement a function to check if a number is **odd/even** using bitwise.
2. Write code to compute absolute value of an integer **without `abs()`**.
3. Find the sign of the product of two numbers without multiplying them.

---

### 🔹 Intermediate

4. Compute `a * b` using only `+` and bitwise shifts.
5. Compute `a / b` using repeated subtraction.
6. Implement fast exponentiation `a^b` using bit shifting.
7. Write code to check if a number is a power of 2 using bitwise.

---

### 🔹 Advanced (Directly Related to Division Problem)

8. Implement division without using `/`, `*`, `%` (the code we wrote).
9. Dry run `100 ÷ 9` and show each step of bit shifting.
10. Modify the code to also return the **remainder** (like `divmod`).
11. Implement floor division for **negative numbers** correctly.
12. Extend this solution to support **long long division** (`64-bit`).

---

### 🔹 Bonus (Deep Understanding)

13. Prove why `a << i` = `a * 2^i`.
14. Explain why right shifting a negative number in C++ gives implementation-defined results.
15. Write a function `divideBy2(int x)` without using `/`, `%`, or `>>`.

---

Would you like me to now **make a complete dry run example of 100 ÷ 7 with this method (step-by-step with binary shifts)** so you see exactly how quotient is built?
