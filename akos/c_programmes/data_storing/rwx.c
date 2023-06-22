#include <stdio.h>

int main() {
    char c;
    while ((c = getchar()) >= '0') {
        if ('0' <= c && c <= '9') {
            c -= '0';
        } else {
            c -= 'A' - 10;
        }

        int mask = (1 << 2);

        if (mask & c) {
            putchar('r');
        } else {
            putchar('-');
        }
        mask >>= 1;

        if (mask & c) {
            putchar('w');
        } else {
            putchar('-');
        }
        mask >>= 1;

        if (mask & c) {
            putchar('x');
        } else {
            putchar('-');
        }
        mask >>= 1;
    }
    putchar('\n');
}