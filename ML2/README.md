# Major Lab 2 (ML2)

You will complete **three small C files** inside the `ML2/` folder:

- `digits.c`
- `debounce.c`
- `filter.c`

## 1) Download + place the starter code (ML2.zip)

1. Download `ML2.zip` from A2L.
2. On the server, **from inside your `~/cs1xc3` repo**:

```bash
cd ~/cs1xc3
unzip -o ML2.zip
ls ML2
```

You should see:

- `ML2/digits.c`
- `ML2/debounce.c`
- `ML2/filter.c`

⚠️ If you end up with a nested folder like `ML2/ML2/digits.c`, ask a TA to fix it.

---

## 2) File specs

### File 1 — `digits.c`

**You implement:**

```c
const int* digits_ltr(unsigned int n);
```

**What it must do:**

- Return a pointer to a **STATIC** integer array.
- The array must contain the digits of `n` in **left-to-right order** (most significant to least significant).
- The final element **must be `-1`** (sentinel/terminator).
- Special case: if `n == 0`, return: `0, -1`.
- **Do not** convert to a string.

Local testing:
- Edit `TEST_N`.
- `main()` prints each digit on its own line until it sees `-1`.

---

### File 2 — `debounce.c`

**You implement:**

```c
const char* debounce_log(const char* in);
```

**What it must do:**

- Return a pointer to a **STATIC** char buffer (C string).
- Remove **ONLY consecutive duplicates**, preserving order.
  - Example: `"aaabcccdd" -> "abcd"`
  - Example: `"abca"` stays `"abca"` (the `a`s are not consecutive)
- Ensure the returned string is **null-terminated** (`'\0'`).

Program behavior:
- `main()` reads **one line from stdin** (using `fgets`) and prints the debounced result + newline.
- **Do not print prompts**.

Note: the autograder assumes the input line has **no spaces**.

---

### File 3 — `filter.c`

**You implement:**

```c
const int* filter_readings(const int in[], int n, int *ignored_out, int *stopped_out);
```

**What it must do (process left-to-right):**

- Return a pointer to a **STATIC** integer array containing only the accepted readings.
- The returned array must end with **`-1`** (sentinel/terminator).

Filtering rules:

1. **Range rule**: if `x` is outside `[-100, 100]`, ignore it and increment `*ignored_out`.
2. **Sentinel rule**: if `x == 9999`, stop immediately and set `*stopped_out = 1`.
3. **Glitch rule**:
   - Track the last **accepted** reading.
   - If `abs(x - last_accepted) > 30`, treat `x` as a glitch: ignore it and increment `*ignored_out`.
   - The first accepted reading has no glitch comparison.

Also:
- Always write final values into `*ignored_out` and `*stopped_out` (even if 0).

Local testing:
- Edit `TEST_READINGS`.
- `main()` prints `ignored=...`, `stopped=...`, then prints accepted readings until it sees `-1`.

---

## 3) Final checklist

- Only changed TODO areas (don’t rewrite `run_test_*()` or `main()` unless the file tells you to).
- Didn’t change function signatures.
- No extra prompts / extra output lines.
- `digits_ltr(...)` and `filter_readings(...)` return arrays ending with `-1`.
- Compiles cleanly with `-Wall -Wextra -Wpedantic -Werror`.

---

## 4) Final Submission (GitLab)

From your repo root (`~/cs1xc3`):

```bash
cd ~/cs1xc3

git add ML2
git commit -m "ml2 final submission"
git push
```

✅ The commit message must match **exactly**:

```
ml2 final submission
```

After pushing, check your GitLab repo to confirm your latest commit is there.
