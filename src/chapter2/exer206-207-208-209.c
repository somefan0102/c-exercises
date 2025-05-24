#include <stdio.h>
#include <limits.h>
#include <math.h>

#define SIZE 35

int bitcount(unsigned int);
int fasterbitcount(int);
unsigned int setbits(unsigned int, int, int, unsigned int);
unsigned int invert(unsigned int, int, int);
unsigned int rightrot(unsigned int, int);

int main(void) {
    int x = 12;

    // This is the same as, obviously:
    // x = x & (x - 1)
    x &= (x - 1);

    // When subtracting by one, it replaces the last
    // one with a 0 and inverts the "garbage".

    // Eq 1
    // 1100 - 1 = 1011
    //  ^          ^

    // Eq 2
    // 1001 - 1 = 1000
    //    ^          ^

    // Eq 3
    // 1000 - 1 = 0111
    // ^          ^

    // The "garbage" affacted can be used with the 0
    // as an AND mask with the previous x to clear
    // any of the mismatched digits.

    // Using Eq 1
    //   1100
    // & 1011
    // ======
    //   1000

    // All of this knowing that x is an int,
    // necessary to the two's complement.

    // I know how it works, but this is the best explanation, I can give. :/

    printf("Init\tOld\tNew\n");
    for (int i = 0; i < 255; i++)
    {
        printf("0x%x\t0x%x\t0x%x\n", i, bitcount(i), fasterbitcount(i));
    }
    
    return 0;
}

int bitcount(unsigned int x) {
    int b;

    for (b = 0; x != 0; x >>= 1) {
        if (x & 1) {
            b++;
        }
    }

    return b;
}

int fasterbitcount(int x) {
    int b = 0;

    for (b = 0; x != 0; b++) {
        x &= (x - 1);
    }

    return b;
}

unsigned int setbits(unsigned int x, int p, int n, unsigned int y) {
    unsigned int a, b, c, d, e;

    // Shift targeted bits to rightmost.
    a = x >> (p + 1 - n);

    // (Making mask) Invert only targeted bit and set garbage to 1.
    b = (a ^ ~(a >> n << n));

    // (Making mask) Invert, shift targets back home, invert.
    b = ~(~b << (p + 1 - n));

    // Clears target bits using mask.
    c = ~(x ^ b);

    // Shift replacement bits in place of cleared target bits.
    d = y << (p + 1 - n);

    // Combine.
    e = c | d;

    return e;
}

unsigned int invert(unsigned int x, int p, int n) {
    unsigned int a, b, c;

    // Shift targeted bits to rightmost.
    a = x >> (p + 1 - n);

    // (Making mask) Shift built 1s to home of target bits.
    b = ~(~0 << n) << (p + 1 - n);

    // Invert selection.
    c = x ^ b;

    return c;
}

unsigned int rightrot(unsigned int x, int n) {
    unsigned int a, b, c;
    int max = (int)log2(UINT_MAX) + 1;

    // Get bits that would be lost during "shifting".
    a = x ^ (x >> n << n);

    // Then actually shift it.
    b = x >> n;

    // Shift lost bits to leftmost.
    a <<= (max - n);

    // Combine.
    c = a | b;

    return c;
}

/*
206: Write a function `setbits(x, p, n, y)` that returns `x` with the `n` bits that begin at
     position `p` set to the rightmost `n` bits of `y`, leaving the other bits unchanged.
207: Write a function `invert(x, p, n)` that returns `x` with the n bits that begin at
     position `p` inverted (i.e., `1` changed into `0` and vice versa), leaving the others unchanged.
208: Write a function `rightrot(x, n)` that returns the value of the integer `x` rotated
     to the right by `n` positions.
209: In a two's complement number system, `x &= (x-1)` deletes the rightmost 1-bit
     in `x`. Explain why. Use this observation to write a faster version of bitcount.
*/