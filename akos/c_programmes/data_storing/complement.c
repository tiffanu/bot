#include <stdio.h>

int main() {
    int a;
    scanf("%d", &a);
    if (a < 0) {
        a += 256;
    }


    for (int mask = (1 << 7); mask != 0; mask >>= 1) {
        putchar((mask & a) ? '1' : '0');
    }
    putchar('\n');
}