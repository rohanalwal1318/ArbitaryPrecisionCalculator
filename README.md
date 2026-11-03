# Arbitrary Precision Calculator (APC)

A command-line calculator written in **pure C** that performs `+`, `-`, `x` and `/` on integers of **any length** — far beyond the 64-bit limit of `long long`. No external libraries, no GMP: every digit is stored in a **doubly linked list** and every operation is implemented by hand, the same way you do it on paper.

```bash
$ ./a.out 123456789123456789 x 987654321987654321
121932631356500531347203169112635269
```

---

## Why this project stands out

| What | Why it matters |
|------|----------------|
| **Built from first principles** | No big-number library. Carry, borrow, shifting and long division are all coded manually on a linked list. |
| **Data structure driven** | One digit per node in a doubly linked list (`prev` / `data` / `next`), tracked by a `head` and `tail` pair. Operations walk from the least significant digit using `tail` and `prev`. |
| **Small and readable** | Each operation lives in its own file of about 40–70 lines, with a clear comment on every step. Easy to read, review and extend. |
| **Clean modular structure** | Public API in one header, helpers separated from operations, entry point separated from tests. |
| **Handles real-world edge cases** | Negative operands, zero results (no `-0`), different operand lengths, division by zero, invalid input and unknown operators. |
| **Memory conscious** | Every list is released with `freeList()`. |
| **Verified** | Checked against Python's big integers on 1,000+ random cases (operands up to 60 digits) with zero mismatches. |

---

## Features

- Addition, subtraction, multiplication and integer division
- Arbitrary-length integer operands
- Positive and negative numbers, with correct sign handling for every combination
- Input validation with clear error messages
- Simple CLI: `./a.out <operand1> <operator> <operand2>`

---

## Project structure

```
APC(Arbitary Precision Calculator)/
├── Include/
│   └── apc.h            # Node/list definitions and all function prototypes
├── Helper/
│   └── apcHelper.c      # createList, printList, printListHead, freeList
├── Operations/
│   ├── sum.c            # Addition
│   ├── sub.c            # Subtraction
│   ├── mul.c            # Multiplication
│   └── div.c            # Division
├── Src/
│   └── main.c           # CLI parsing, sign handling, operation dispatch
├── Tests/
│   └── test.c           # Quick sanity tests for each operation
├── Makefile
└── README.md
```

---

## How it works

### Data structure

```c
typedef struct node {
    struct node *prev;
    int data;                // a single digit, 0-9
    struct node *next;
} dnode;

typedef struct {
    dnode *head;             // first digit
    dnode *tail;             // last digit
} newList;
```

The number `1234` becomes: `NULL <- 1 <-> 2 <-> 3 <-> 4 -> NULL`, with `head` pointing at `1` and `tail` at `4`.

The doubly linked list is what makes the arithmetic natural: digit-by-digit math starts at the **tail** (units place) and moves toward the **head** using `prev`.

### The four operations

| Operation | Approach |
|-----------|----------|
| **Addition** | Walk both lists from the tail, add digits plus carry, store `sum % 10`, carry `sum / 10`. A final carry adds one more node. |
| **Subtraction** | Digit-wise subtraction with borrow (always larger minus smaller). Leading zeros are trimmed from the result. |
| **Multiplication** | School-book method. A result list of `len1 + len2` zero nodes is allocated up front. Each digit of the second number multiplies the whole first number and accumulates into the result at a shifting offset. Leading zeros are trimmed. |
| **Division** | Long division by walking the dividend digit by digit, keeping a running remainder and emitting one quotient digit per step. |

### Sign handling (in `main.c`)

The core routines only work on unsigned digit strings. `main.c` reduces every signed case to them:

| Expression | Reduced to |
|------------|------------|
| `a + b` (both positive) | `sum(a, b)` |
| `-a + b` | `b - a`, negated if `a > b` |
| `a + (-b)` | `a - b`, negated if `b > a` |
| `-a + (-b)` | `-(a + b)` |
| `a - b` | `a - b`, or `-(b - a)` if `b > a` |
| `-a - b` | `-(a + b)` |
| `a - (-b)` | `a + b` |
| `-a - (-b)` | `b - a` |
| `x`, `/` | Operate on absolute values, negative result only if exactly one operand is negative |

Numbers are compared with a small `cmpNum()` helper (length first, then lexicographic), because plain `strcmp` gives wrong answers when operands have different lengths.

---

## Build and run

```bash
make            # builds ./a.out (calculator) and ./test_apc (tests)
```

Usage:

```bash
./a.out <operand1> <operator> <operand2>
```

| Operator | Meaning |
|----------|---------|
| `+` | Addition |
| `-` | Subtraction |
| `x` or `'*'` | Multiplication (quote the `*` so the shell doesn't expand it) |
| `/` | Integer division (quotient) |

### Examples

```bash
$ ./a.out 99999999999999999999 + 1
100000000000000000000

$ ./a.out -500 - -1200
700

$ ./a.out 123456789 x 987654321
121932631112635269

$ ./a.out -1000000000000000000000 / 7
-142857142857142857142

$ ./a.out 5 / 0
Error : Division by zero
```

### Run the tests

```bash
./test_apc
```

---

## Complexity

With `n` and `m` as the digit counts of the two operands:

| Operation | Time | Extra space |
|-----------|------|-------------|
| Addition | O(max(n, m)) | O(max(n, m)) |
| Subtraction | O(max(n, m)) | O(max(n, m)) |
| Multiplication | O(n x m) | O(n + m) |
| Division (single machine-word divisor) | O(n) | O(n) |

---

## Current limitations

- Integers only. Division returns the quotient, with no remainder or decimals.
- The divisor must fit in a `long long`; the dividend can be any length.

## Possible improvements

- Return the remainder (modulo) alongside the quotient
- Support for decimal numbers
- Full big-number-by-big-number division
- Faster multiplication (Karatsuba)
- Automated test suite with assertions

---

## What this project demonstrates

- Pointer manipulation and dynamic memory management in C
- Designing a data structure around the algorithm that uses it
- Breaking a problem into small, testable, single-purpose modules
- Handling edge cases deliberately instead of by accident
- Writing code simple enough to explain line by line

---

*Built with C, a doubly linked list, and no shortcuts.*
